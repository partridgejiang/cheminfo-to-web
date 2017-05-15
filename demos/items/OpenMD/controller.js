var predefinedDataFileNames = [
	'', 'ar864', 'argonNVT', 'butane', 'ClH2O', 'ewald_z4', 'graphene'
];
var predefinedDataCache = {};
function fillPredefinedInputDataList(selElem)
{
    selElem.innerHTMl = '';
	for (var i = 0, l = predefinedDataFileNames.length; i < l; ++i)
	{
		var caption = predefinedDataFileNames[i];		
		var url = caption? 'predefines/' + caption + '.omd.json': '';
		var elemItem = document.createElement('option');
		elemItem.setAttribute('value', url);		
		elemItem.innerHTML = caption;        
		selElem.appendChild(elemItem);
	}
}

function predefinedInputDataListChange()
{	
	var url = this.value;	
	if (!url)  // empty item, clear all data
	{
		clearIncFiles();
		$('textInputOmd').value = '';
		updateIncFileList();
	}
	else
	{
		var loadPredefinedData = function(data)
		{
			$('textInputOmd').value = data.omd;
			clearIncFiles();
			data.incFiles.forEach(function(item){
				incFileData.push({'fileId': item.id, 'content': item.content})
			});
			updateIncFileList();
		}
		if (predefinedDataCache[url])
		{
			loadPredefinedData(predefinedDataCache[url]);
		}
		else
		{
			DemoUtils.loadUrl(url, function(success, content)
			{
				if (!success)
					console.error('Load URL resource failed: ', url);
				else
				{
					var detail = JSON.parse(content);
					loadPredefinedData(detail);
					predefinedDataCache[url] = detail;
				}
			});
		}
	}	
}

var incFileData = [];

function addIncFiles(files)
{
	for (var i = 0, l = files.length; i < l; ++i)
	{				
		(function(){
			var file = files[i];
			DemoUtils.loadFile(file, function(success, content){
				var fileName = file.name;
				if (success)
					incFileData.push({'fileId': fileName, 'content': content});
					updateIncFileList();
			});
		})();
	}
}
function clearIncFiles()
{
	incFileData = [];
	updateIncFileList();
}
function updateIncFileList()
{
	var fileInfos = [];
	incFileData.forEach(function(item){
		fileInfos.push('[' + item.fileId + ']');
		//fileInfos.push(item.content);
		//fileInfos.push(' ');
	});
	$('textIncFiles').value = fileInfos.join('\n');
}

var openMdWorker;		
function execute()
{
	executeJob();
}
function executeJob()
{
	var srcData = $('textInputOmd').value;
	
	var resultObj = {};
	
	// now in web worker
	var msg = 'Run calculation in web worker, this may take quite a while...';
	setStatus(msg);
	openMdWorker = new Worker('worker.js');
	openMdWorker.onmessage = function(e) {								
		var data = e.data;
		if (data)
		{
			if (data.msgType === 'calculationResult')
			{
				if (data.successful)
				{
					resultObj.omd = srcData;
					resultObj.report = data.report;
					resultObj.eor = data.eor
					resultObj.stat = data.stat;
					resultObj.dump = data.dump;
					resultObj.execTime = data.duration / 1000;
					
					$('textReport').value = data.report;
					$('textStat').value = data.stat;
					$('textEor').value = data.eor;
					
					var msg = 'Calculation done in ' + data.duration / 1000 + ' sec.';
					setStatus(msg);
				}
				else
				{
					var msg = 'Calculation failed! Please change browser console for the details.';
					setStatus(msg);
				}
			}
			else if (data.msgType === 'progress')
			{
				var percent = Math.round(data.percentage);
				var remainingTime = data.remainingTime;  // in sec
				var endTime = new Date(Date.now() + remainingTime * 1000);						
				var sStatus = 'Calculating: ' + percent + '% done, estimate ending in ' + endTime.toLocaleString();
				setStatus(sStatus);
			}
			else if (data.msgType === 'log')
			{
				console.log(data.msg);
			}
			else if (data.msgType === 'error')
			{
				console.error(data.msg);
			}
		}
	}
	// set inc files
	openMdWorker.postMessage({'msgType': 'incData', 'incData': JSON.stringify(incFileData)});
	// set main data, begin calculation
	openMdWorker.postMessage({'msgType': 'calculate', 'omdData': srcData});
}
function terminate()
{
	if (openMdWorker)
	{
		openMdWorker.terminate();
		var msg = 'Calculation terminated by user';
		setStatus(msg);
	}
}

function setStatus(status)
{
	$('labelStatus').innerHTML = status;
}