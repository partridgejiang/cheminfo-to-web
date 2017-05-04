TestUtils.loadScript('Inchi/inchi-js/bin/inchiConv.js', null, function(){

//console.log(typeof InChI);
var Module;

TestUtils.registerEmccTestRunner(function runTest()
{	
	var TU = TestUtils;
	
	describe('Test of creating InChI from mol data', function()
	{
		it('Compare InChI results between native program and JS', function(done){
			TU.loadTestData('inchi/molsInChI.json', function(data, success){			
				expect(data).not.toBeNull();
				var contentObj = JSON.parse(data);
				var testItems = contentObj.data;
				
				molToInchiJson = Module.cwrap('molToInchiJson', 'string', ['string', 'string']);
				var options = '';
							
				for (var i = 0, l = testItems.length; i < l; ++i)
				{
					var item = testItems[i];
					var molData = item.molData;
					var nativeResult = JSON.parse(item.inchiResult);  // result given by native C code			
					// do my own conversion
					var jsResult = JSON.parse(molToInchiJson(molData, options));
					expect(jsResult.inchi).toEqual(nativeResult.inchi);
					expect(jsResult.auxInfo).toEqual(nativeResult.auxInfo);
					expect(jsResult.success).toEqual(nativeResult.success);
					expect(jsResult.message).toEqual(nativeResult.message);				
					console.log('Inchi test done on ', i);
				}
				done();			
			});
		});
	});	
}, 'InChIModule');

Module = InChIModule();

});