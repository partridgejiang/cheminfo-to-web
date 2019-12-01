if (typeof(Module) === 'undefined')
{
  Module = {};  
}

Module.onRuntimeInitialized = function() { 
	if (typeof(document) !== 'undefined' && document.dispatchEvent)
	{
		var event = new CustomEvent('InChI.Initialized', { 'detail': {'module': Module} });
		document.dispatchEvent(event);		
	}
	if (typeof(__$inChIInitialized$__) === 'function')
	{
		__$inChIInitialized$__({'module': Module});
	}
};