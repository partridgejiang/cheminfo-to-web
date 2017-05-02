var Module = {
	onRuntimeInitialized: function() {
      //console.log('I am ready!');
	  moduleReady = true;
	  if (suspendRun)
	  {
		execRunner();
	  }
	},
	locateFile: function(url)
	{
		return '../../bin/' + url;
	}
	//logReadFiles: true
};
var moduleReady = false;
var suspendRun = false;

importScripts('../../bin/openMD.js');

var omdData, incData;
onmessage = function(e)
{
	//console.log('Message received from main script', e);
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
	if (!moduleReady)  // wait util EMSCRIPTEN environment is ready
	{
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
		var sReport = runner.getReportData();
		var sEor = runner.getEorData();
		var sStat = runner.getStatData();
		var sDump = runner.getDumpData();
		result.report = sReport;
		result.eor = sEor;
		result.stat = sStat;
		result.dump = sDump;
	}
	postMessage(result);
	runner['delete']();
	close();
}