// Set essetial enviroment vars for OpenBabel
if (typeof(Module) === 'undefined')
{
  Module = {};
  Module.preRun = [function() {ENV.BABEL_DATADIR = "data";}];  
}
else
{
  Module.preRun.push(function() {ENV.BABEL_DATADIR = "data";})  
}
Module.logReadFiles = true;

// special file loader to handle big data files of OpenBabel
Module.locateFile = function(path, prefix)
{	
	var scriptPath = (typeof(scriptDirectory) !== 'undefined')? scriptDirectory: null;
	if (!scriptPath && _scriptDir)
	{
		scriptPath = _scriptDir.substr(0, _scriptDir.lastIndexOf('/')+1);
	}
	if (scriptPath)
	{
		if (path.indexOf('.data') >= 0)  // external data file
		{
			return scriptPath + path;
		}
	}
	
	return prefix + path;
}
Module.onRuntimeInitialized = function() { 
	if (typeof(document) !== 'undefined' && document.dispatchEvent)
	{
		var event = new CustomEvent('OpenBabel.Initialized', { 'detail': {'module': Module} });
		document.dispatchEvent(event);		
	}
	if (typeof(__$openBabelInitialized$__) === 'function')
	{
		__$openBabelInitialized$__({'module': Module});
	}
};