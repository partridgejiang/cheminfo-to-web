TestUtils.loadScript('Indigo/Indigo-js/bin/indigo.js', null, function(){
	TestUtils.loadScript('Indigo/Indigo-js/bin/indigoAdapter.js', null, function(){
		run();
	});
});
//TestUtils.loadScript('_unitTest/_kekule/kekule.js?modules=io,algorithm,html,openbabel');

var run = function()
{
var Indigo;
TestUtils.registerEmccTestRunner(function runTest()
{			
	var TU = TestUtils;	
	// Extract ctab part of mol file data for comparison. Other part (e.g. name, creating time may change during output)
	function extractCtabData(data, format)  
	{
		var fmt = format.toLowerCase();
		if (fmt === 'mol')
		{
			var a = data.split('\n');
			// discard first two lines
			a.splice(0, 2);
			return a.join('\n');
		}
		else if (fmt === 'pdb')
		{
			var a = data.split('\n');			
			a.splice(0, 3);
			var str = a.join('\n');
			//var s = str.replace(/\s/g, '');
			//console.log(str, s);
			return str;
		}
		else
			return data;
	}
	function compareData(src, dest)
	{
		var a1 = src.split('\n');
		var a2 = dest.split('\n');
		if (a1.length !== a2.length)
		{
			console.log('Length different');
			console.log(a1);
			console.log(a2);
			return false;
		}
		else
		{
			for (var i = 0, l = a1.length; i < l; ++i)
			{
				var s1 = a1[i];
				var s2 = a2[i];
				if (s1 !== s2)
				{
					console.log('Different in line ' + i, '"' + s1 + '"', ' : ', '"' + s2 + '"');
					return false;
				}
			}
		}
		return true;
	}
	
	function findTautomers(mol)
	{
		var result = [];
		var iterator = Indigo.iterateTautomers(mol);
		
		var tautomerItem, index = 0;		
		while (Indigo.hasNext(iterator))
		{
			tautomerItem = Indigo.next(iterator);
			if (tautomerItem >= 0)
			{
				var mol2 = Indigo.clone(tautomerItem);
				var tautomerSmiles = Indigo.canonicalSmiles(mol2);
				result.push(tautomerSmiles);
				Indigo.free(mol2);
				//Indigo.free(tautomerSmiles);
			}
		}
		Indigo.free(iterator);			
		
		return result.join('\n') + '\n';  // additional return is returned by native also
	}
	
	function layoutMol(mol)
	{
		var result;				
		var smiles = Indigo.canonicalSmiles(mol);
		Indigo.setOption("smart-layout", "true");
		var mol2 = Indigo.loadMoleculeFromString(smiles);
		result = Indigo.layout(mol2);
		//return result;
		return mol2;
	}
	
	var testFiles = [
			'1293.mol.indigo.json',
			'aw00196.mol.indigo.json',
			'big_semicube.mol.indigo.json',
			'cd00846.mol.indigo.json',
			'complexring1.mol.indigo.json',
			'complexring3.mol.indigo.json',
			'complexring4.mol.indigo.json',
			'complexring5.mol.indigo.json',
			'complexring6.mol.indigo.json',
			'complexring7.mol.indigo.json',
			'highvalence.mol.indigo.json',
			'krabe2.mol.indigo.json',
			'krabe.mol.indigo.json',
			'legio_intr_mon.mol.indigo.json',
			'legio_modes_mon_2.mol.indigo.json',
			'legio_mult_accl.mol.indigo.json',
			'legio_mult_glucose.mol.indigo.json',
			'legio_peps_glycine.mol.indigo.json',
			'legio_peps_lysine.mol.indigo.json',
			'legio_ugi_amac.mol.indigo.json',
			'legio_ugi_iso.mol.indigo.json',
			'legio_ugi_ketone.mol.indigo.json',
			's13133.mol.indigo.json',
			'test1.mol.indigo.json',
			'test2.mol.indigo.json'
		];
	
	describe('Test of reading and writing moleclue data of different formats', function()
	{
		testFiles.forEach(function(fileName) {
			it('Compare I/O result of ' + fileName, function(done){
				TU.loadTestData('indigo/' + fileName, function(data, success){			
					expect(data).not.toBeNull();					
					var nativeResult = JSON.parse(data);
					
					// read by JS
					var mol = Indigo.loadMoleculeFromString(nativeResult.input.data);
					expect(mol).not.toBeNull;
					
					// compare output
					var nativeOutputs = nativeResult.output;
					// mol
					var sMol = Indigo.molfile(mol);					
					var passed = compareData(extractCtabData(sMol, 'mol'), extractCtabData(nativeOutputs.mol, 'mol'));
					expect(passed).toEqual(true);
					
					// cml
					var sCml = Indigo.cml(mol);
					var passed = compareData(extractCtabData(sCml, 'cml'), extractCtabData(nativeOutputs.cml, 'cml'));
					expect(passed).toEqual(true);
					// smiles
					var sSmiles = Indigo.canonicalSmiles(mol);
					var passed = compareData(extractCtabData(sSmiles, 'smi'), extractCtabData(nativeOutputs.smiles, 'smi'));
					expect(passed).toEqual(true);
					
					/*
					nativeOutputs.forEach(function(nativeOutputItem){					
						var format = nativeOutputItem.format;
						var jsData = saveMol(obMol, nativeOutputItem.mimeType, nativeOutputItem.format);
						var passed = compareData(extractCtabData(jsData, format), extractCtabData(nativeOutputItem.data, format));
						if (!passed)  // output data different, maybe molecule structure is same?
						{
							var obMolNative = loadMol(nativeOutputItem.data, nativeOutputItem.mimeType, nativeOutputItem.format);
							var obMolJs = loadMol(jsData, nativeOutputItem.mimeType, nativeOutputItem.format);
							compareStructure(obMolNative, obMolJs);
						}
						else
							expect(passed).toEqual(true);
						//expect(extractCtabData(jsData, format)).toEqual(extractCtabData(nativeOutputItem.data, format));
					});
					*/
					done();			
				});
			}, 100000);
		});
		testFiles.forEach(function(fileName) {	
			it('Compare algorithm result of ' + fileName, function(done){
				TU.loadTestData('indigo/' + fileName, function(data, success){			
					expect(data).not.toBeNull();					
					var nativeResult = JSON.parse(data);
					
					// read mol by JS
					var mol = Indigo.loadMoleculeFromString(nativeResult.input.data);
					expect(mol).not.toBeNull();
					
					// sssr count
					var sssrCount = Indigo.countSSSR(mol);
					expect(sssrCount).toEqual(parseInt(nativeResult.output.sssrCount));
					
					// tautomers
					var tautomers = findTautomers(mol);
					expect(tautomers).toEqual(nativeResult.output.tautomers);
					//console.log('tautomers', tautomers);
										
					// layout
					var mol2 = layoutMol(mol);
					expect(mol2).not.toBeNull();
					var sMol2 = Indigo.molfile(mol2);
					//console.log('layout', sMol2, Indigo.smiles(mol2));
					var passed = compareData(extractCtabData(sMol2, 'mol'), extractCtabData(nativeResult.output.layoutMol, 'mol'));					
					expect(passed).toEqual(true);
					
					done();
				});
			}, 100000);
		});
	});
}, 'IndigoModule');

Indigo = CreateIndigo(IndigoModule());

}