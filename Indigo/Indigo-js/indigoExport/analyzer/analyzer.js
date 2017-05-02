function $(id)
{
	return document.getElementById(id);
}

function analysis(srcCode)
{
	var funcInfo = [];
	var lines = srcCode.split('\n');
	// analysis each line of code, all exported functions stays in one single line
	var prevLine = '';
	lines.forEach(function(line){
		var lineInfo = analysisLine(prevLine + ' ' + line);
		if (lineInfo === -1)  // unfinished line
			prevLine += line;
		else  // line already finished
		{
			prevLine = '';
			if (lineInfo)
			{
				funcInfo.push(lineInfo);
				//console.log(lineInfo);
			}
		}
	});
	return funcInfo;
}

function analysisLine(code)
{
	var str = code;
	// strip out leading and tailing blanks
	str = str.trim();
	// check if starts with 'CEXPORT', if so, this line is a exported function
	if (!str.startsWith('CEXPORT'))
	{
		return null;
	}
	else  // analysis function
	{
		// remove inline comments
		var regComment = /\/\*.*\*\//g;
		str = str.replace(regComment, '');
		// remove unessential chars
		var regBlanks = /[\t]/g;
		str = str.replace(regBlanks, ' ');
		// check if this line ends with ';'
		str = str.trim();
		if (!str.endsWith(';'))
			return -1;  // special mark, means line not ends
		// extract paramters inside '()' and type/name before ()
		var regParams = /(.*)\((.*)\)/;
		var matchResult = str.match(regParams);
		if (matchResult && matchResult.length)
		{
			var sParams = matchResult[2];
			var paramInfos = analysisParams(sParams, code);
			var sNameType = matchResult[1];
			var nameTypeInfo = analysisFuncNameType(sNameType, code);
			return {
				'funcName': nameTypeInfo.funcName,
				'funcType': nameTypeInfo.funcType,
				'params': paramInfos
			}
		}
		else
		{
			reportError('Param not found', code);
		}
	}
	return null;
}

function analysisFuncNameType(sNameType, code)
{
	/*
	const PART_DELIMITER = /\s+/;
	var parts = sNameType.split(PART_DELIMITER);
	if ((parts.length || 0) < 2)
		reportError('Function name/type illegal', code);
	else
	{
		console.log(parts);
		var funcName = parts.pop().trim();
		parts.shift();  // remove leading 'CEXPORT'
		var funcType = parts.join(' ').trim();
		// if funcName starts with '*', put pointer mark to type
		if (funcName.startsWith('*'))
		{
			funcName = funcName.substr(1);
			funcType += '*';
		}
		return {'funcName': funcName, 'funcType': funcType};
	}
	*/
	var info = _getVarTypeAndName(sNameType, true);
	return {'funcName': info.varName, 'funcType': info.varType};
}

function analysisParams(sParams, lineCode)
{
	const PARAM_DELIMITER = ',';
	const TYPE_DELIMITER = /\s+/;
	var params = sParams.split(PARAM_DELIMITER);
	var paramInfos = [];
	params.forEach(function(sParam){
		if (!sParam.trim())
			return;
		var info = _getVarTypeAndName(sParam, false);
		//console.log(sParam, info);
		paramInfos.push({'paramName': info.varName, 'paramType': info.varType});
		/*
		var parts = sParam.split(TYPE_DELIMITER);
		if (!params.length)
			reportError('Illegal param', lineCode);
		else
		{
			// the last part is variable name
			var paramName = params.pop().trim();
			// the rest is type name
			var paramType = params.join(' ').trim();
			// if paramName starts with '*', put pointer mark to type
			if (paramName.startsWith('*'))
			{
				paramName = paramName.substr(1);
				paramType += '*';
			}
			paramInfos.push({'paramName': paramName, 'paramType': paramType});
		}
		*/
	});
	return paramInfos;
}

function _getVarTypeAndName(code, removeExportTag)
{
	const PART_DELIMITER = /\s+/;
	var parts = code.split(PART_DELIMITER);
	if (removeExportTag)  // remove leading 'CEXPORT' tag
		parts.shift();
	if (!parts.length)
		reportError('Illegal code', code);
	var sName, sType;
	// get last unempty part as name
	var sName = parts.pop().trim();
	while (!sName && parts.length)
	{
		sName = parts.pop().trim();
	}
	var sType = parts.join(' ').trim();
	if (!sType)  // type empty, name may should be type (e.g. param list of func(void))
	{
		sType = sName;
		sName = null;
	}
	// if sName starts with '*', put pointer mark to type
	while (sName && sType && sName.startsWith('*'))
	{
		sName = sName.substr(1);
		sType += '*';
	}
	return {'varName': sName, 'varType': sType};
}

function reportError(msg, srcCode)
{
	var errMsg = msg;
	if (srcCode)
		errMsg += ' ( in: ' + srcCode + ' )';
	throw errMsg;
}

function summaryTypes(funcInfos)
{
	var typeInfos = {};

	var addFuncOfType = function(funcName, funcOrParamType)
	{
		var funcList = typeInfos[funcOrParamType];
		if (!funcList)
		{
			funcList = [];
			typeInfos[funcOrParamType] = funcList;
		}
		if (funcList.indexOf(funcName) < 0)
			funcList.push(funcName);
	};

	funcInfos.forEach(function(funcInfo){
		var fType = funcInfo.funcType;
		var fName = funcInfo.funcName;
		addFuncOfType(fName, fType);
		var params = funcInfo.params;
		params.forEach(function(paramInfo){
			if (paramInfo.paramName && paramInfo.paramName.indexOf('file') >= 0)  // filename, handle it
				addFuncOfType(fName, '__FILENAME__');
			else
				addFuncOfType(fName, paramInfo.paramType);
		})
	});

	return typeInfos;
}