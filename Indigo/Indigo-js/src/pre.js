if (typeof(Module) === 'undefined')
{
  Module = {};  
}

Module.onRuntimeInitialized = function() { 
	if (typeof(document) !== 'undefined' && document.dispatchEvent)
	{
		var event = new CustomEvent('Indigo.Initialized', { 'detail': {'module': Module} });
		document.dispatchEvent(event);		
	}
	if (typeof(__$indigoInitialized$__) === 'function')
	{
		__$indigoInitialized$__({'module': Module});
	}
};