var OpenMdModule = {
	onRuntimeInitialized: function() {
      console.log('I am ready!');
	  moduleReady = true;
	  if (suspendRun)
	  {
		execRunner();
	  }
	}
	//logReadFiles: true
};
var moduleReady = false;
var suspendRun = false;

importScripts('../../../libs/compiled/openMD.js');

var Module = OpenMdModule();

var omdData, incData;
onmessage = function(e)
{
	var data = e.data;
	if (data)
	{
		if (data.msgType === 'incData')  // set include file data
		{
			incData = JSON.parse(data.incData);			
		}
		if (data.msgType === 'calculate')	// set main data, begin calculation
		{
			omdData = data.omdData;
			execRunner();
		}
	}
}

function execRunner()
{
	if (!Module && !moduleReady)  // wait util EMSCRIPTEN environment is ready
	{
		//console.log('suspend run');
		suspendRun = true;
		return;
	}
	else
		suspendRun = false;	
		
	var srcData = omdData;
	var runner = new Module.OpenMdRunner();
			
	if (incData && incData.length)
	{
		incData.forEach(function(item){
			runner.addIncludeData(item.content, item.fileId);
		});
	}
	var tStart = (performance || Date).now();
	var success = false;
	try{
		var success = !!runner.runOmdJob(srcData);
	}
	catch(e)
	{
		console.error(e);
	}
	//console.log('run result', success);
	var tEnd = (performance || Date).now();
	
	//console.log('Posting message back to main script');
	var result = {'msgType': 'calculationResult', 'successful': success, 'duration': tEnd - tStart};
	if (success)
	{
		result.report = runner.getReportData();
		result.eor = runner.getEorData();
		result.stat = runner.getStatData();
		result.dump = runner.getDumpData();
	}
	postMessage(result);
	runner['delete']();
	close();
}