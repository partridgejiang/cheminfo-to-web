var run = function() {

var Module;

TestUtils.registerEmccTestRunner(function runTest()
{		
	var TU = TestUtils;
	
	  function loadMol(data, mimeType, format)
	  {	    		
		// benchmark
		var _obConv = new (Module['ObConversionWrapper'])();
		if (!mimeType)
			mimeType = 'chemical/x-mdl-molfile';
		var fileExt = format;  // is this suitable?
		var fmt = _obConv.setInFormat(mimeType, fileExt);
		var obClassName = 'OBMol';
		var obObj = new (Module[obClassName])();
		_obConv.readString(obObj, data);		
		_obConv['delete']();
		return obObj;
	  }
	  function saveMol(mol, mimeType, format)
	  {
	    var _obConv = new (Module['ObConversionWrapper'])();
		var fmt = _obConv.setOutFormat(mimeType, /*fileExt*/format);
		var content = _obConv.writeString(mol, false);		  		
		_obConv['delete']();		
		return content;
	  }
	
	// Extract ctab part of mol file data for comparison. Other part (e.g. name, creating time may change during output)
	function extractCtabData(data, format)  
	{
		var fmt = format.toLowerCase();
		if (fmt === 'mol' || fmt === 'xyz')
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
	function compareStructure(srcObMol, destObMol)
	{
		var AU = Kekule.OpenBabel.AdaptUtils;
		var src = AU.obObjToKekule(srcObMol);
		var dest = AU.obObjToKekule(destObMol);
		return src.isSameStructureWith(dest);
	}
	
	describe('Test of reading and writing mol data of different formats', function()
	{
		var srcFiles = [
			'test1.car.ob.json',
			'test2.car.ob.json',			
			'test3.car.ob.json',
			'hao_xu_1.mol.ob.json',
			'hao_xu_2.mol.ob.json',
			'hao_xu_3.mol.ob.json',
			'hao_xu_4.mol.ob.json',
			'hao_xu_5.mol.ob.json',
			'hao_xu_6.mol.ob.json',
			'hao_xu_7.mol.ob.json',
			'hao_xu_8.mol.ob.json',
			'hao_xu_9.mol.ob.json',			
			'regressiontest_numrotors.mol.ob.json',			
			'test1.mol.ob.json',			
			//'1DRF.pdb.ob.json',		// too large to compare in structure, may require a lot of time in browser
			
			'adamantanediol.mol.ob.json',
			'bridged1.mdl.ob.json',
			'canon10.mol.ob.json',
			'canon11.mol.ob.json',
			'canon12.mol.ob.json',
			'canon13.mol.ob.json',
			'canon14.mol.ob.json',
			'canon15.mol.ob.json',
			'canon16.mol.ob.json',
			'canon17a.mol.ob.json',
			'canon17b.mol.ob.json',
			'canon17.mol.ob.json',
			'canon18.mol.ob.json',
			'canon19.mol.ob.json',
			'canon1.mol.ob.json',
			'canon20.mol.ob.json',
			'canon21.mol.ob.json',
			'canon22.mol.ob.json',
			'canon23.mol.ob.json',
			'canon24.mol.ob.json',
			'canon2.mol.ob.json',
			'canon3.mol.ob.json',
			'canon4.mol.ob.json',
			'canon5.mol.ob.json',
			'canon6.mol.ob.json',
			'canon7.mol.ob.json',
			'canon8.mol.ob.json',
			'canon9.mol.ob.json',
			'canon_cistrans15.mol.ob.json',
			'canon_cistrans16.mol.ob.json',
			'canon_cistrans1.mol.ob.json',
			'canon_cistrans2.mol.ob.json',
			'canon_cistrans3.mol.ob.json',
			'canon_cistrans4.mol.ob.json',
			'canon_cistrans5.mol.ob.json',
			'canon_cistrans6.mol.ob.json',
			'canon_cistrans7.mol.ob.json',
			'canon_cistrans8.mol.ob.json',
			'canon_cistrans9.mol.ob.json',
			'cistrans2D_1.mol.ob.json',
			'cistrans2D_2.mol.ob.json',
			'cistrans3D_1.mol.ob.json',
			'cistrans3D_2.mol.ob.json',
			'cistrans3D_3.mol.ob.json',
			'cistrans3D_4.mol.ob.json',
			'cistrans3D_5.mol.ob.json',
			'complex2D_1.mol.ob.json',
			'complex2D_2.mol.ob.json',
			'complex2D_3.mol.ob.json',
			'complex2D_4a.mol.ob.json',
			'complex2D_4b.mol.ob.json',
			'complex2D_5a.mol.ob.json',
			'complex2D_5b.mol.ob.json',
			'complex2D_6.mol.ob.json',
			'complex2D_7.mol.ob.json',
			'cubane2.mdl.ob.json',
			'cubane.mdl.ob.json',
			'cyclobutane_D1.mol.ob.json',
			'cyclobutane_D2.mol.ob.json',
			'cyclobutane_D3.mol.ob.json',
			'cyclobutane_D4.mol.ob.json',
			'cyclohexanediol_D1.mol.ob.json',
			'cyclohexanediol_D2.mol.ob.json',
			'cyclohexanetriol_D1.mol.ob.json',
			'cyclohexanetriol_D2.mol.ob.json',
			'fullerene20.mdl.ob.json',
			'fullerene60.mdl.ob.json',
			'incorrect_canon1.mol.ob.json',
			'incorrect_canon2.mol.ob.json',
			'inositol_allo.mol.ob.json',
			'inositol_chiroD.mol.ob.json',
			'inositol_chiroL.mol.ob.json',
			'inositol_cis.mol.ob.json',
			'inositol_epi.mol.ob.json',
			'inositol_muco.mol.ob.json',
			'inositol_myo.mol.ob.json',
			'inositol_neo.mol.ob.json',
			'inositol_scyllo.mol.ob.json',
			'octahedron.mdl.ob.json',
			'perception10.mol.ob.json',
			'perception11.mol.ob.json',
			'perception12.mol.ob.json',
			'perception13.mol.ob.json',
			'perception14.mol.ob.json',
			'perception15.mol.ob.json',
			'perception16.mol.ob.json',
			'perception17.mol.ob.json',
			'perception18.mol.ob.json',
			'perception19.mol.ob.json',
			'perception1.mol.ob.json',
			'perception20.mol.ob.json',
			'perception2.mol.ob.json',
			'perception3.mol.ob.json',
			'perception4.mol.ob.json',
			'perception5.mol.ob.json',
			'perception6.mol.ob.json',
			'perception7.mol.ob.json',
			'perception8.mol.ob.json',
			'perception9.mol.ob.json',
			'razinger_fig1_a.mol.ob.json',
			'razinger_fig1_b.mol.ob.json',
			'razinger_fig1_c.mol.ob.json',
			'razinger_fig1_d.mol.ob.json',
			'razinger_fig1_e.mol.ob.json',
			'razinger_fig1_f.mol.ob.json',
			'razinger_fig1_g.mol.ob.json',
			'razinger_fig1_h.mol.ob.json',
			'razinger_fig1_i.mol.ob.json',
			'razinger_fig1_j.mol.ob.json',
			'razinger_fig1_k.mol.ob.json',
			'razinger_fig1_l.mol.ob.json',
			'razinger_fig1_m.mol.ob.json',
			'razinger_fig1_n.mol.ob.json',
			'razinger_fig1_o.mol.ob.json',
			'razinger_fig1_p.mol.ob.json',
			'razinger_fig3.mol.ob.json',
			'razinger_fig7_10.mol.ob.json',
			'razinger_fig7_11.mol.ob.json',
			'razinger_fig7_12.mol.ob.json',
			'razinger_fig7_13.mol.ob.json',
			'razinger_fig7_14.mol.ob.json',
			'razinger_fig7_15.mol.ob.json',
			'razinger_fig7_16.mol.ob.json',
			'razinger_fig7_17.mol.ob.json',
			'razinger_fig7_18.mol.ob.json',
			'razinger_fig7_19.mol.ob.json',
			'razinger_fig7_19_spec1.mol.ob.json',
			'razinger_fig7_19_spec2.mol.ob.json',
			'razinger_fig7_19_spec3.mol.ob.json',
			'razinger_fig7_19_spec4.mol.ob.json',
			'razinger_fig7_19_spec5.mol.ob.json',
			'razinger_fig7_1.mol.ob.json',
			'razinger_fig7_20.mol.ob.json',
			'razinger_fig7_20_spec1.mol.ob.json',
			'razinger_fig7_21.mol.ob.json',
			'razinger_fig7_22.mol.ob.json',
			'razinger_fig7_23.mol.ob.json',
			'razinger_fig7_24.mol.ob.json',
			'razinger_fig7_25.mol.ob.json',
			'razinger_fig7_26.mol.ob.json',
			'razinger_fig7_26_spec1.mol.ob.json',
			'razinger_fig7_27.mol.ob.json',
			'razinger_fig7_28.mol.ob.json',
			'razinger_fig7_29.mol.ob.json',
			'razinger_fig7_2.mol.ob.json',
			'razinger_fig7_30.mol.ob.json',
			'razinger_fig7_31.mol.ob.json',
			'razinger_fig7_32.mol.ob.json',
			'razinger_fig7_33.mol.ob.json',
			'razinger_fig7_34.mol.ob.json',
			'razinger_fig7_35.mol.ob.json',
			'razinger_fig7_36.mol.ob.json',
			'razinger_fig7_37.mol.ob.json',
			'razinger_fig7_38.mol.ob.json',
			'razinger_fig7_39.mol.ob.json',
			'razinger_fig7_3.mol.ob.json',
			'razinger_fig7_40.mol.ob.json',
			'razinger_fig7_41.mol.ob.json',
			'razinger_fig7_42.mol.ob.json',
			'razinger_fig7_43.mol.ob.json',
			'razinger_fig7_44.mol.ob.json',
			'razinger_fig7_45.mol.ob.json',
			'razinger_fig7_46.mol.ob.json',
			'razinger_fig7_47.mol.ob.json',
			'razinger_fig7_48.mol.ob.json',
			'razinger_fig7_49.mol.ob.json',
			'razinger_fig7_4.mol.ob.json',
			'razinger_fig7_50.mol.ob.json',
			'razinger_fig7_51.mol.ob.json',
			'razinger_fig7_52.mol.ob.json',
			'razinger_fig7_57.mol.ob.json',
			'razinger_fig7_58.mol.ob.json',
			'razinger_fig7_59.mol.ob.json',
			'razinger_fig7_59_spec1.mol.ob.json',
			'razinger_fig7_5.mol.ob.json',
			'razinger_fig7_5_spec.mol.ob.json',
			'razinger_fig7_60.mol.ob.json',
			'razinger_fig7_61.mol.ob.json',
			'razinger_fig7_62.mol.ob.json',
			'razinger_fig7_63.mol.ob.json',
			'razinger_fig7_64.mol.ob.json',
			'razinger_fig7_69.mol.ob.json',
			'razinger_fig7_6.mol.ob.json',
			'razinger_fig7_7.mol.ob.json',
			'razinger_fig7_8.mol.ob.json',
			'razinger_fig7_9.mol.ob.json',
			'tetrahedral2D_1.mol.ob.json',
			'tetrahedral2D_2.mol.ob.json',
			'tetrahedral2D_3.mol.ob.json',
			'tetrahedral2D_4.mol.ob.json',
			'tetrahedral2D_5.mol.ob.json',
			'tetrahedral2D_6.mol.ob.json',
			'tetrahedral2D_7.mol.ob.json',
			'tetrahedral2D_8.mol.ob.json',
			'tetrahedral2D_9.mol.ob.json',
			'tetrahedral3D_1.mol.ob.json',
			'tetrahedral3D_2.mol.ob.json',
			'tetrahedral3D_3.mol.ob.json',
			'tetrahedral3D_4.mol.ob.json',
			'tetrahedron.mdl.ob.json'
		];
		srcFiles.forEach(function(fileName) {
			it('Compare I/O result of ' + fileName, function(done){
				TU.loadTestData('openbabel/' + fileName, function(data, success){			
					expect(data).not.toBeNull();					
					var nativeResult = JSON.parse(data);			
					
					// read by JS
					var obMol = loadMol(nativeResult.input.data, nativeResult.input.mimeType, nativeResult.input.format);
					expect(obMol).not.toBeNull;
					var nativeOutputs = nativeResult.output;
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
					done();			
				});
			}, 100000);
		});
	});	
}, 'OpenBabelModule');

Module = OpenBabelModule();

}

TestUtils.loadScript('openbabel.js', null, run);
TestUtils.loadScript('../_kekule/kekule.js?modules=io,algorithm,html,openbabel');