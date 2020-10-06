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