function $(id)
{
	return document.getElementById(id);
}

var indigoExportConfigs = {
	typeMapping: {
		"void": null,
		"const char *": "string",
		"const char*": "string",
		"char*": "string",
		"char *": "string",
		"qword": "number",
		"int": "number",
		"float": "number",
		"double": "number",
		"long long": "number",
		"float*": "array",
		"float *": "array",
		"byte*": "array",
		"byte *": "array",
		//"byte**": "array",
		//"char**": "array",
		"const byte*": "array",
		"int*": "number",
		"const int*": "number",
		"const int *": "number"
	}
};

function isFuncTypesAvailable(funcInfo)
{
	var typeMapping = indigoExportConfigs.typeMapping;
	var varTypes = [];
	var varNames = [];
	var funcType = funcInfo.funcType;
	varTypes.push(funcType);
	funcInfo.params.forEach(function(paramInfo){
		varTypes.push(paramInfo.paramType);
		varNames.push(paramInfo.paramName);
	});
	for (var i = 0, l = varTypes.length; i < l; ++i)
	{
		if (typeMapping[varTypes[i]] === undefined)
			return false;
	}
	for (var i = 0, l = varNames.length; i < l; ++i)
	{
		var name = varNames[i];
		if (name && name.indexOf('file') >= 0)  // param of fileName
			return false;
	}
	return true;
}
function getFuncLabel(funcInfo)
{
	var result = funcInfo.funcType || '';
	result = _rtfLabel(result, 'CType');
	if (result)
		result += ' ';
	result += _rtfLabel(funcInfo.funcName, 'CFuncName') + _rtfLabel('(', 'CSymbol');
	var paramStrs = [];
	funcInfo.params.forEach(function(paramInfo){
		var sParam = _rtfLabel(paramInfo.paramType, 'CType');
		if (paramInfo.paramName)
		{
			sParam += ' ' + _rtfLabel(paramInfo.paramName, 'CName');
		}
		paramStrs.push(sParam);
	});
	result += paramStrs.join(_rtfLabel(', ', 'CSymbol'));
	result += _rtfLabel(')', 'CSymbol');
	return result;
}
function _rtfLabel(text, textClass)
{
	return '<span class="' + textClass + '">' + text + "</span>";
}

function fillFuncList(doc, selElem)
{
	var funcs = indigoApiData.funcs;
	funcs.forEach(function(funcInfo){
		if (isFuncTypesAvailable(funcInfo))
		{
			var funcLabel = getFuncLabel(funcInfo);
			var optElem = document.createElement('option');
			optElem.value = funcInfo.funcName;
			optElem.innerHTML = funcLabel;
			selElem.appendChild(optElem);
		}
	});
}
function getSelectedFuncs(selElem)
{
	var result = [];
	var optElems = selElem.selectedOptions;
	for (var i = 0, l = optElems.length; i < l; ++i)
	{
		result.push(optElems[i].value);
	}
	return result;
}
function selectFuncs(selElem, funcs)
{
	var optElems = selElem.getElementsByTagName('option');
	for (var i = 0, l = optElems.length; i < l; ++i)
	{
		var elem = optElems[i];
		if (funcs.indexOf(elem.value) >= 0)
			elem.selected = true;
	}
}
function saveSelectedFuncs(funcs)  // save selected function info to local storage
{
	localStorage.setItem('indigoExportFuncs', JSON.stringify(funcs));
}
function loadSelectedFuncs()
{
	var s = localStorage.getItem('indigoExportFuncs');
	if (s)
		return JSON.parse(s);
	else
		return null;
}

////////////////////////////////////////////////

function getEmccExportCmd(funcNames)   // return export command line param for emcc
{
	var cFuncNames = [];
	funcNames.forEach(function(fname){
		cFuncNames.push('\'_' + fname + '\'');
	});
	var result = cFuncNames.join(',');
	result = '-s EXPORTED_FUNCTIONS="[' + result + ']"';
	return result;
}

function getJsWrapperForFuncs(funcNames, options)  // generate JS wrapper for c function
{
	if (!options)
		options = {};
	var jsCodes = [];
	// enums
	jsCodes.push(wrapIndigoEnums(options.rootNamespace, options.moduleName) + ',');
	// functions
	var allFuncs = indigoApiData.funcs;	
	allFuncs.forEach(function(funcInfo){
		var funcName = funcInfo.funcName;
		if (funcNames.indexOf(funcName) >= 0)  // need to export this function
		{
			var jsFuncName = funcInfo.funcName;
			if (options.removePrefix)  // remove prefix "indigo"
			{
				if (jsFuncName.startsWith('indigo'))
					jsFuncName = jsFuncName.substr(6);
			}
			if (options.lowerCaseFirst)
				jsFuncName = jsFuncName.charAt(0).toLowerCase() + jsFuncName.substr(1);
			jsCodes.push(getJsWrapperForFunc(funcInfo, jsFuncName, options.rootNamespace, options.moduleName));
		}
	});
	var result = jsCodes.join('\n');	
	if (options.rootNamespace)  // wrap with namespace
	{
		var sCode = '{\n' + result + '\n}';
		if (options.wrapInFunc)
		{
			sCode = 'function () {\nreturn {\n' + result + '}\n};';
		}
		result = 'var ' + options.rootNamespace + ' = ' + sCode;
	}
	return result;
}
function getJsWrapperForFunc(funcInfo, jsFuncName, rootNamespace, moduleName)
{
	if (!moduleName)
		moduleName = 'Module';
	if (!jsFuncName)
		jsFuncName = funcInfo.funcName;
	var cFuncName = funcInfo.funcName;

	// whether namespace is used
	var sConnector = rootNamespace? ': ': ' = ';
	var sLeadingBlanks = rootNamespace? '\t': '';
	var sTailingMark = rootNamespace? ',': ';';
	// func names
	var result = sLeadingBlanks + jsFuncName + sConnector + moduleName + '.cwrap(\'' + cFuncName + '\', ';

	// func type
	var typeMapping = indigoExportConfigs.typeMapping;
	var cType = funcInfo.funcType;
	var jsType = typeMapping[cType];
	if (!jsType)  // null type
	  result += 'null, ';
	else
		result += '\'' + jsType + '\', ';

	// param types
	var jsParamTypes = [];
	funcInfo.params.forEach(function(paramInfo){
		var cType = paramInfo.paramType;
		var jsType = typeMapping[cType];
		if (jsType)
			jsParamTypes.push("'" + jsType + "'");
	});
	result += '[' + jsParamTypes.join(', ') + ']';

	result += ')' + sTailingMark;

	return result;
}

function wrapIndigoEnums(rootNamespace, moduleName)
{	
	// whether namespace is used
	var sConnector = rootNamespace? ': ': ' = ';
	var sLeadingBlanks = rootNamespace? '\t': '';
	var sTailingMark = rootNamespace? ',': ';';
	// func names
	var sIndentLeading = sLeadingBlanks + '\t';
	var enumStrs = [];	
	enumStrs.push(wrapIndigoEnum(null, {
		// Reaction centers
		INDIGO_RC_NOT_CENTER: -1,
		INDIGO_RC_UNMARKED: 0,
		INDIGO_RC_CENTER: 1,
		INDIGO_RC_UNCHANGED: 2,
		INDIGO_RC_MADE_OR_BROKEN: 4,
		INDIGO_RC_ORDER_CHANGED: 8,
		
		// Molecule accessing
		INDIGO_ABS: 1,
		INDIGO_OR: 2,
		INDIGO_AND: 3,
		INDIGO_EITHER: 4,
		INDIGO_UP: 5,
		INDIGO_DOWN: 6,
		INDIGO_CIS: 7,
		INDIGO_TRANS: 8,
		INDIGO_CHAIN: 9,
		INDIGO_RING: 10,
		INDIGO_ALLENE: 11,
		INDIGO_SINGLET: 101,
		INDIGO_DOUBLET: 102,
		INDIGO_TRIPLET: 103		
	}, sLeadingBlanks, sTailingMark, sConnector));
		
	return enumStrs.join(',\n');
}

function wrapIndigoEnum(enumName, enumValues, sLeadingBlanks, sTailingMark, sConnector)
{
	var result = '';	
	var sIndentLeading = sLeadingBlanks;
	var lines = [];
	// Reaction cneters
	if (enumName)
	{
		sIndentLeading = sLeadingBlanks + '\t';
		lines.push(sLeadingBlanks + enumName + sConnector + '{');
	}
	var propNames = Object.getOwnPropertyNames(enumValues);	
	propNames.forEach(function(name){
		var value = enumValues[name];
		lines.push(sIndentLeading + name + sConnector + JSON.stringify(value));
	});	
	if (enumName)
	{
		lines.push(sLeadingBlanks + '}' + sTailingMark);
	}
	result = lines.join(',\n');
	return result;
}