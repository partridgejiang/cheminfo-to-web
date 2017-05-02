if (typeof(Module) === 'undefined')
{
	Module = {};
	Module.preRun = [];
}

(function(Module) {

	//Module.logReadFiles = true;
	//'filePackagePrefixURL': 'data/',
	
	Module._getEnvironment = function()
	{
		if (typeof window === 'object')
			return 'browser';
		else if (typeof importScripts === 'function')
			return 'worker';		
		else if (typeof process === 'object' && typeof require === 'function')
			return 'node';
		else
			return shell;
	};
	Module._isInWorker = function()
	{
		return Module._getEnvironment() === 'worker';
	};
	Module._isInBrowser = function()
	{
		return Module._getEnvironment() === 'browser';
	};
	
	Module.print = function(text) 
	{
		if (Module._isInWorker())
			postMessage({'msgType': 'log', 'msg': text});
		else
			console.log(text) 
	};
	Module.printErr = function(text) 
	{
		if (Module._isInWorker())
			postMessage({'msgType': 'error', 'msg': text});
		else
			console.error(text) 
	};
	/*
	Module.locateFile = function(var1, var2, var3)
	{
		console.log('locateFile', var1, var2, var3);
		return '../../bin/' + var1;
	};
	Module.locateFilePackage = function(var1, var2, var3)
	{
		console.log('locateFilePackage', var1, var2, var3);
		return '../../bin/' + var1;
	};
	*/
	Module.preRun.push(function() {
		// init file system
		FS.mkdir('/current');  // current working directory
		FS.chdir('/current');
		//FS.mkdir('/FRC_ROOT');  // for forcefield data files			
	});	
})(Module);