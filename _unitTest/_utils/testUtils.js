var TestUtils = {
	loadScript: function(url, doc)  // url based on project root dir
	{
		if (!doc)
			doc = document;
		var src = '../' + url;
		doc.write('<script type="text/javascript" src="'+src+'"><\/script>');
	},
	loadFile: function(url, callback)
	{
		var req = new XMLHttpRequest();
		req.onreadystatechange = function ()
		{
			if (req.readyState != 4) return;
			if (req.status != 200 && req.status != 304)
			{
				callback(null, false);  // XHR failed
				throw 'HTTP error ' + req.status;
				return;
			}			
			callback(req.responseText || req.response, true);  // call successfule
		};

		req.open("GET", url);
		req.send();
	},
	loadTestData: function(relUrl, callback)	
	{
		return TestUtils.loadFile('data/' + relUrl, callback);
	}	
};

(function(root, TestUtils){	
	TestUtils.registerEmccTestRunner = function(runner, moduleName)
	{
		if (!moduleName)
			moduleName = 'Module';
		var module = root[moduleName];
		if (!root[moduleName])  // module object not created
		{
			module = {};			
			module.onRuntimeInitialized = (function() {
				return function() {
				  console.log('Ready to run test!');			  
				  runner();
				};
			})();
			root[moduleName] = module;
		}
		else  // already created, can run test now
			runner();
	}

})(this, TestUtils);