# The compiler
ifdef EMCC
	#EMCC = 1	
	MAIN_DIR = ../src
	INCHI_FIXER_DIR = $(MAIN_DIR)/inchiFix
	C_COMPILER = emcc
	CPP_COMPILER = emcc
	LINKER = emcc -s
	EXE_NAME = indigo
	#EXE_EXT = .html
	EXE_EXT = .js
	
	ifndef NO_MODULARIZE
		EMCC_MODULARIZE_OPTION = -s MODULARIZE=1 -s EXPORT_NAME="'IndigoModule'"
	endif
	
	EMCC_MEM_FILE_OPTION = --memory-init-file 0
	# Must build with DISABLE_EXCEPTION_CATCHING=0 to enable exception handling, as many functions of Indigo relies on it
	EMCC_MISC_OPTION = -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=0 $(EMCC_MODULARIZE_OPTION)
	#-s EXCEPTION_CATCHING_WHITELIST="['_indigoLoadMolecule', '_indigoLoadMoleculeFromString', '_indigoLoadMoleculeFromBuffer']"
	#-s DEMANGLE_SUPPORT=1 -s ASSERTIONS=1 
	#-s USE_PTHREADS=2 --bind
	EMCC_EXPORT_FUNCS = -s EXPORTED_FUNCTIONS="['_indigoVersion','_indigoAllocSessionId','_indigoSetSessionId','_indigoReleaseSessionId','_indigoGetLastError','_indigoFree','_indigoClone','_indigoCountReferences','_indigoFreeAllObjects','_indigoSetOption','_indigoSetOptionInt','_indigoSetOptionBool','_indigoSetOptionFloat','_indigoSetOptionColor','_indigoSetOptionXY','_indigoResetOptions','_indigoReadString','_indigoLoadString','_indigoReadBuffer','_indigoLoadBuffer','_indigoWriteBuffer','_indigoClose','_indigoNext','_indigoHasNext','_indigoIndex','_indigoRemove','_indigoCreateMolecule','_indigoCreateQueryMolecule','_indigoLoadMolecule','_indigoLoadMoleculeFromString','_indigoLoadMoleculeFromBuffer','_indigoLoadQueryMolecule','_indigoLoadQueryMoleculeFromString','_indigoLoadQueryMoleculeFromBuffer','_indigoLoadSmarts','_indigoLoadSmartsFromString','_indigoLoadSmartsFromBuffer','_indigoSaveMolfile','_indigoMolfile','_indigoSaveCml','_indigoCml','_indigoSaveCdxml','_indigoCdxml','_indigoSaveMDLCT','_indigoNameToStructure','_indigoLoadReaction','_indigoLoadReactionFromString','_indigoLoadReactionFromBuffer','_indigoLoadQueryReaction','_indigoLoadQueryReactionFromString','_indigoLoadQueryReactionFromBuffer','_indigoLoadReactionSmarts','_indigoLoadReactionSmartsFromString','_indigoLoadReactionSmartsFromBuffer','_indigoCreateReaction','_indigoCreateQueryReaction','_indigoAddReactant','_indigoAddProduct','_indigoAddCatalyst','_indigoCountReactants','_indigoCountProducts','_indigoCountCatalysts','_indigoCountMolecules','_indigoGetMolecule','_indigoIterateReactants','_indigoIterateProducts','_indigoIterateCatalysts','_indigoIterateMolecules','_indigoSaveRxnfile','_indigoRxnfile','_indigoOptimize','_indigoNormalize','_indigoStandardize','_indigoIonize','_indigoGetAcidPkaValue','_indigoGetBasicPkaValue','_indigoAutomap','_indigoGetAtomMappingNumber','_indigoSetAtomMappingNumber','_indigoGetReactingCenter','_indigoSetReactingCenter','_indigoClearAAM','_indigoCorrectReactingCenters','_indigoIterateAtoms','_indigoIteratePseudoatoms','_indigoIterateRSites','_indigoIterateStereocenters','_indigoIterateAlleneCenters','_indigoIterateRGroups','_indigoCountRGroups','_indigoIsPseudoatom','_indigoIsRSite','_indigoStereocenterType','_indigoChangeStereocenterType','_indigoStereocenterGroup','_indigoSetStereocenterGroup','_indigoStereocenterPyramid','_indigoSingleAllowedRGroup','_indigoAddStereocenter','_indigoIterateRGroupFragments','_indigoCountAttachmentPoints','_indigoIterateAttachmentPoints','_indigoSymbol','_indigoDegree','_indigoGetCharge','_indigoGetExplicitValence','_indigoSetExplicitValence','_indigoAtomicNumber','_indigoIsotope','_indigoValence','_indigoCheckValence','_indigoCheckQuery','_indigoCheckRGroups','_indigoCountHydrogens','_indigoCountImplicitHydrogens','_indigoXYZ','_indigoSetXYZ','_indigoCountSuperatoms','_indigoCountDataSGroups','_indigoCountRepeatingUnits','_indigoCountMultipleGroups','_indigoCountGenericSGroups','_indigoIterateDataSGroups','_indigoIterateSuperatoms','_indigoIterateGenericSGroups','_indigoIterateRepeatingUnits','_indigoIterateMultipleGroups','_indigoIterateSGroups','_indigoGetSuperatom','_indigoGetDataSGroup','_indigoGetGenericSGroup','_indigoGetMultipleGroup','_indigoGetRepeatingUnit','_indigoDescription','_indigoData','_indigoAddDataSGroup','_indigoAddSuperatom','_indigoSetDataSGroupXY','_indigoSetSGroupData','_indigoSetSGroupCoords','_indigoSetSGroupDescription','_indigoSetSGroupFieldName','_indigoSetSGroupQueryCode','_indigoSetSGroupQueryOper','_indigoSetSGroupDisplay','_indigoSetSGroupLocation','_indigoSetSGroupTag','_indigoSetSGroupTagAlign','_indigoSetSGroupDataType','_indigoSetSGroupXCoord','_indigoSetSGroupYCoord','_indigoCreateSGroup','_indigoGetSGroupClass','_indigoGetSGroupName','_indigoSetSGroupClass','_indigoSetSGroupName','_indigoGetSGroupNumCrossBonds','_indigoAddSGroupAttachmentPoint','_indigoDeleteSGroupAttachmentPoint','_indigoGetSGroupDisplayOption','_indigoSetSGroupDisplayOption','_indigoGetSGroupSeqId','_indigoGetSGroupMultiplier','_indigoSetSGroupMultiplier','_indigoGetRepeatingUnitSubscript','_indigoGetRepeatingUnitConnectivity','_indigoSetSGroupBrackets','_indigoFindSGroups','_indigoGetSGroupType','_indigoGetSGroupIndex','_indigoGetSGroupOriginalId','_indigoSetSGroupOriginalId','_indigoGetSGroupParentId','_indigoSetSGroupParentId','_indigoTransformSCSRtoCTAB','_indigoTransformCTABtoSCSR','_indigoResetCharge','_indigoResetExplicitValence','_indigoResetIsotope','_indigoSetAttachmentPoint','_indigoClearAttachmentPoints','_indigoRemoveConstraints','_indigoAddConstraint','_indigoAddConstraintNot','_indigoAddConstraintOr','_indigoResetStereo','_indigoInvertStereo','_indigoCountAtoms','_indigoCountBonds','_indigoCountPseudoatoms','_indigoCountRSites','_indigoIterateBonds','_indigoBondOrder','_indigoBondStereo','_indigoTopology','_indigoIterateNeighbors','_indigoBond','_indigoGetAtom','_indigoGetBond','_indigoSource','_indigoDestination','_indigoClearCisTrans','_indigoClearStereocenters','_indigoCountStereocenters','_indigoClearAlleneCenters','_indigoCountAlleneCenters','_indigoResetSymmetricCisTrans','_indigoResetSymmetricStereocenters','_indigoMarkEitherCisTrans','_indigoMarkStereobonds','_indigoValidateChirality','_indigoAddAtom','_indigoResetAtom','_indigoAddRSite','_indigoSetRSite','_indigoSetCharge','_indigoSetIsotope','_indigoGetRadicalElectrons','_indigoGetRadical','_indigoSetRadical','_indigoResetRadical','_indigoSetImplicitHCount','_indigoAddBond','_indigoSetBondOrder','_indigoMerge','_indigoHighlight','_indigoUnhighlight','_indigoIsHighlighted','_indigoCountComponents','_indigoComponentIndex','_indigoIterateComponents','_indigoComponent','_indigoCountSSSR','_indigoIterateSSSR','_indigoIterateSubtrees','_indigoIterateRings','_indigoIterateEdgeSubmolecules','_indigoCountHeavyAtoms','_indigoGrossFormula','_indigoMolecularWeight','_indigoMostAbundantMass','_indigoMonoisotopicMass','_indigoMassComposition','_indigoCanonicalSmiles','_indigoLayeredCode','_indigoSymmetryClasses','_indigoHasCoord','_indigoHasZCoord','_indigoIsChiral','_indigoIsPossibleFischerProjection','_indigoCreateSubmolecule','_indigoCreateEdgeSubmolecule','_indigoGetSubmolecule','_indigoRemoveAtoms','_indigoRemoveBonds','_indigoAlignAtoms','_indigoAromatize','_indigoDearomatize','_indigoFoldHydrogens','_indigoUnfoldHydrogens','_indigoLayout','_indigoClean2d','_indigoSmiles','_indigoSmarts','_indigoCanonicalSmarts','_indigoExactMatch','_indigoSetTautomerRule','_indigoRemoveTautomerRule','_indigoClearTautomerRules','_indigoName','_indigoSetName','_indigoUnserialize','_indigoHasProperty','_indigoGetProperty','_indigoSetProperty','_indigoRemoveProperty','_indigoIterateProperties','_indigoClearProperties','_indigoCheckBadValence','_indigoCheckAmbiguousH','_indigoFingerprint','_indigoCountBits','_indigoCommonBits','_indigoOneBitsList','_indigoSimilarity','_indigoIterateSDF','_indigoIterateRDF','_indigoIterateSmiles','_indigoIterateCML','_indigoIterateCDX','_indigoRawData','_indigoTell','_indigoTell64','_indigoSdfAppend','_indigoSmilesAppend','_indigoRdfHeader','_indigoRdfAppend','_indigoCmlHeader','_indigoCmlAppend','_indigoCmlFooter','_indigoCreateSaver','_indigoAppend','_indigoCreateArray','_indigoArrayAdd','_indigoAt','_indigoCount','_indigoClear','_indigoIterateArray','_indigoSubstructureMatcher','_indigoIgnoreAtom','_indigoUnignoreAtom','_indigoUnignoreAllAtoms','_indigoMatch','_indigoCountMatches','_indigoCountMatchesWithLimit','_indigoIterateMatches','_indigoHighlightedTarget','_indigoMapAtom','_indigoMapBond','_indigoMapMolecule','_indigoIterateTautomers','_indigoExtractCommonScaffold','_indigoAllScaffolds','_indigoDecomposeMolecules','_indigoDecomposedMoleculeScaffold','_indigoIterateDecomposedMolecules','_indigoDecomposedMoleculeHighlighted','_indigoDecomposedMoleculeWithRGroups','_indigoCreateDecomposer','_indigoDecomposeMolecule','_indigoIterateDecompositions','_indigoAddDecomposition','_indigoGetFragmentedMolecule','_indigoRGroupComposition','_indigoExpandAbbreviations','_indigoToString','_indigoReactionProductEnumerate','_indigoTransform','_indigoTransformHELMtoSCSR','_indigoDbgInternalType','_indigoDbgBreakpoint','_indigoDbgProfiling','_indigoDbgResetProfiling','_indigoDbgProfilingGetCounter']"
else
	NATIVE = 1
	C_COMPILER = gcc
	CPP_COMPILER = g++
	LINKER = g++ -s
	EXE_NAME = indigo
	EXE_NAME_ALGORITHM = indigoAlgorithm
	EXE_NAME_NAMETOMOL = indigoNameToMol
	EXE_NAME_TESTBUILDER = indigoTestDataBuilder
	EXE_EXT = 
	MAIN_DIR = ../benchmark/src_cpp
	TEST_BUILDER_SRC_DIR = ../testDataBuilder
endif

OPTIMIZE = -O3
LINKER_OPTIONS = -pthread $(OPTIMIZE) $(EMCC_MEM_FILE_OPTION) $(EMCC_MISC_OPTION) $(EMCC_EXPORT_FUNCS)
CPP_COMPILER_OPTIONS = $(P_INCLUDE) $(OPTIMIZE) -DTARGET_API_LIB -c -pthread -std=c++11
C_COMPILER_OPTIONS = $(P_INCLUDE) $(OPTIMIZE) -DTARGET_API_LIB -c -pthread  -Wno-implicit-function-declaration

INDIGO_BASE_DIR = ../../Indigo-src/Indigo

INDIGO_3RDPARTY_DIR = $(INDIGO_BASE_DIR)/third_party
INDIGO_ZLIB_DIR = $(INDIGO_3RDPARTY_DIR)/zlib-src
INDIGO_ZLIB_SRC_DIR = $(INDIGO_ZLIB_DIR)/src
INDIGO_TINYXML_DIR = $(INDIGO_3RDPARTY_DIR)/tinyxml
INDIGO_TINYXML_SRC_DIR = $(INDIGO_TINYXML_DIR)/src
INDIGO_INCHI_DIR = $(INDIGO_3RDPARTY_DIR)/inchi
#INDIGO_INCHI_DIR = ../../../Inchi/inchi-src/INCHI-1-SRC
INDIGO_INCHI_BASE_DIR = $(INDIGO_INCHI_DIR)/INCHI_BASE/src
INDIGO_INCHI_API_DIR = $(INDIGO_INCHI_DIR)/INCHI_API/libinchi/src

INDIGO_COMMON_DIR = $(INDIGO_BASE_DIR)/common
INDIGO_COMMON_BASEC_DIR = $(INDIGO_COMMON_DIR)/base_c
INDIGO_COMMON_BASECPP_DIR = $(INDIGO_COMMON_DIR)/base_cpp
INDIGO_COMMON_MATH_DIR = $(INDIGO_COMMON_DIR)/math
INDIGO_COMMON_LZW_DIR = $(INDIGO_COMMON_DIR)/lzw
INDIGO_COMMON_GZIP_DIR = $(INDIGO_COMMON_DIR)/gzip

INDIGO_MOLECULE_DIR = $(INDIGO_BASE_DIR)/molecule
INDIGO_MOLECULE_SRC_DIR = $(INDIGO_MOLECULE_DIR)/src

INDIGO_LAYOUT_DIR = $(INDIGO_BASE_DIR)/layout
INDIGO_LAYOUT_SRC_DIR = $(INDIGO_LAYOUT_DIR)/src

INDIGO_REACTION_DIR = $(INDIGO_BASE_DIR)/reaction
INDIGO_REACTION_SRC_DIR = $(INDIGO_REACTION_DIR)/src

INDIGO_GRAPH_DIR = $(INDIGO_BASE_DIR)/graph
INDIGO_GRAPH_SRC_DIR = $(INDIGO_GRAPH_DIR)/src

INDIGO_API_DIR = $(INDIGO_BASE_DIR)/api
INDIGO_API_SRC_DIR = $(INDIGO_API_DIR)/src

BIN_DIR = ../bin

ifdef EMCC
	BIN_OBJ_DIR = $(BIN_DIR)/obj_emcc
else
	BIN_OBJ_DIR = $(BIN_DIR)/obj_native
endif
BIN_3RD_OBJ_DIR = $(BIN_OBJ_DIR)/3rdParty

EXE_PATHNAME = $(BIN_DIR)/$(EXE_NAME)$(EXE_EXT)
EXE_ALGORITHM_PATHNAME = $(BIN_DIR)/$(EXE_NAME_ALGORITHM)$(EXE_EXT)
EXE_NAMETOMOL_PATHNAME = $(BIN_DIR)/$(EXE_NAME_NAMETOMOL)$(EXE_EXT)
EXE_TESTBUILDER_PATHNAME = $(BIN_DIR)/$(EXE_NAME_TESTBUILDER)$(EXE_EXT)

P_INCLUDE =

ifdef INCHI_FIXER_DIR
	P_INCLUDE += -I$(INCHI_FIXER_DIR)
endif

P_INCLUDE += -I$(INDIGO_ZLIB_DIR)/include -I$(INDIGO_TINYXML_DIR)/include -I$(INDIGO_INCHI_BASE_DIR) -I$(INDIGO_BASE_DIR) -I$(INDIGO_COMMON_DIR) -I$(INDIGO_COMMON_BASEC_DIR) -I$(INDIGO_COMMON_BASECPP_DIR) -I$(INDIGO_COMMON_MATH_DIR) -I$(INDIGO_COMMON_LZW_DIR) -I$(INDIGO_COMMON_GZIP_DIR) -I$(INDIGO_GRAPH_DIR) -I$(INDIGO_MOLECULE_DIR) -I$(INDIGO_REACTION_DIR) -I$(INDIGO_LAYOUT_DIR) -I$(INDIGO_API_DIR) -I$(INDIGO_API_SRC_DIR)


INDIGO_COMMON_BASEC_SRCS =	\
$(INDIGO_COMMON_BASEC_DIR)/bitarray.c	\
$(INDIGO_COMMON_BASEC_DIR)/nano_posix.c	\
$(INDIGO_COMMON_BASEC_DIR)/os_dir_posix.c	\
$(INDIGO_COMMON_BASEC_DIR)/os_sync_posix.c	\
$(INDIGO_COMMON_BASEC_DIR)/os_thread_posix.c	\
$(INDIGO_COMMON_BASEC_DIR)/os_tls_posix.c
#$(INDIGO_COMMON_BASEC_DIR)/os_tls_win32.c
#$(INDIGO_COMMON_BASEC_DIR)/os_thread_win32.c	\
#$(INDIGO_COMMON_BASEC_DIR)/os_sync_win32.c	\
#$(INDIGO_COMMON_BASEC_DIR)/os_dir_win32.c	\
#$(INDIGO_COMMON_BASEC_DIR)/nano_win.c	\

INDIGO_COMMON_BASECPP_SRCS = \
$(INDIGO_COMMON_BASECPP_DIR)/bitinworker.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/bitoutworker.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/cancellation_handler.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/chunk_storage.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/common_exceptions_impl.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/crc32.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/d_bitset.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/exception.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/gray_codes.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/io_base.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/locale_guard.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/os_sync_wrapper.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/os_thread_wrapper.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/output.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/profiling.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/properties_map.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/scanner.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/shared_ptr.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/shmem_posix.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/smart_output.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/string_pool.cpp	\
$(INDIGO_COMMON_BASECPP_DIR)/tlscont.cpp
#$(INDIGO_COMMON_BASECPP_DIR)/shmem_win32.cpp	\

INDIFO_COMMON_MATH_SRCS = 	\
$(INDIGO_COMMON_MATH_DIR)/best_fit.cpp	\
$(INDIGO_COMMON_MATH_DIR)/line3f.cpp	\
$(INDIGO_COMMON_MATH_DIR)/lseg3f.cpp	\
$(INDIGO_COMMON_MATH_DIR)/matr3x3d.cpp	\
$(INDIGO_COMMON_MATH_DIR)/plane3f.cpp	\
$(INDIGO_COMMON_MATH_DIR)/random.cpp	\
$(INDIGO_COMMON_MATH_DIR)/statistics.cpp	\
$(INDIGO_COMMON_MATH_DIR)/transform3f.cpp	\
$(INDIGO_COMMON_MATH_DIR)/vec2f.cpp	\
$(INDIGO_COMMON_MATH_DIR)/vec3f.cpp

INDIGO_COMMON_LZW_SRCS =	\
$(INDIGO_COMMON_LZW_DIR)/lzw_decoder.cpp	\
$(INDIGO_COMMON_LZW_DIR)/lzw_dictionary.cpp	\
$(INDIGO_COMMON_LZW_DIR)/lzw_encoder.cpp

INDIGO_MOLECULE_SRCS =	\
$(INDIGO_MOLECULE_SRC_DIR)/base_molecule.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/canonical_smiles_saver.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/cmf_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/cmf_saver.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/cml_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/cml_saver.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/elements.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/elements_isotopes.inc	\
$(INDIGO_MOLECULE_SRC_DIR)/haworth_projection_finder.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/icm_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/icm_saver.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/inchi_parser.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/inchi_wrapper.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/max_common_submolecule.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_3d_constraints.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_allene_stereo.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_arom.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_arom_match.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_auto_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_automorphism_search.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_cdx_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_cdxml_saver.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_cdx_saver.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_chain_fingerprints.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_cis_trans.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_dearom.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_electrons_localizer.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_exact_matcher.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_exact_substructure_matcher.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_fingerprint.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_gross_formula.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_gross_formula_options.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_inchi_component.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_inchi.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_inchi_layers.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_inchi_utils.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_ionize.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_layered_molecules.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_mass.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_mass_options.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_name_parser.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_neighbourhood_counters.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_pi_systems_matcher.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_rgroups_composition.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_rgroups.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_savers.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_scaffold_detection.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_sgroups.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_standardize.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_standardize_options.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_stereocenter_options.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_stereocenters.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_substructure_matcher.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tautomer_chain.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tautomer_enumerator.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tautomer_match.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tautomer_matcher.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tautomer_substructure_matcher.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tautomer_superstructure.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tautomer_utils.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molecule_tgroups.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molfile_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/molfile_saver.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/multiple_cdx_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/multiple_cml_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/query_molecule.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/rdf_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/sdf_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/smiles_loader.cpp	\
$(INDIGO_MOLECULE_SRC_DIR)/smiles_saver.cpp

INDIGO_REACTION_SRCS =	\
$(INDIGO_REACTION_SRC_DIR)/base_reaction.cpp	\
$(INDIGO_REACTION_SRC_DIR)/base_reaction_substructure_matcher.cpp	\
$(INDIGO_REACTION_SRC_DIR)/canonical_rsmiles_saver.cpp	\
$(INDIGO_REACTION_SRC_DIR)/crf_loader.cpp	\
$(INDIGO_REACTION_SRC_DIR)/crf_saver.cpp	\
$(INDIGO_REACTION_SRC_DIR)/icr_loader.cpp	\
$(INDIGO_REACTION_SRC_DIR)/icr_saver.cpp	\
$(INDIGO_REACTION_SRC_DIR)/query_reaction.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_auto_loader.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_automapper.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_cdx_loader.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_cdxml_saver.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_cdx_saver.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_cml_loader.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_cml_saver.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_enumerator_state.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_exact_matcher.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_fingerprint.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_gross_formula.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_neighborhood_counters.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_product_enumerator.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_substructure_matcher.cpp	\
$(INDIGO_REACTION_SRC_DIR)/reaction_transformation.cpp	\
$(INDIGO_REACTION_SRC_DIR)/rsmiles_loader.cpp	\
$(INDIGO_REACTION_SRC_DIR)/rsmiles_saver.cpp	\
$(INDIGO_REACTION_SRC_DIR)/rxnfile_loader.cpp	\
$(INDIGO_REACTION_SRC_DIR)/rxnfile_saver.cpp

INDIGO_LAYOUT_SRCS = 	\
$(INDIGO_LAYOUT_SRC_DIR)/attachment_layout.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/layout_pattern.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/layout_pattern_smart.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/metalayout.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_cleaner_2d.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_assign.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_assign_smart.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_attach.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_border.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_cycle.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_geom.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_refine.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_graph_smart.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_macrocycle_lattice.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/molecule_layout_macrocycles.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/reaction_layout.cpp	\
$(INDIGO_LAYOUT_SRC_DIR)/refinement_state.cpp


INDIGO_GRAPH_SRCS =	\
$(INDIGO_GRAPH_SRC_DIR)/automorphism_search.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/aux_path_finder.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/biconnected_decomposer.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/cycle_basis.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/cycle_enumerator.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/dfs_walk.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/edge_rotation_matcher.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/edge_subgraph_enumerator.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/embedding_enumerator.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/embeddings_storage.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/filter.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_affine_matcher.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_constrained_bmatching_finder.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_decomposer.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_fast_access.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_iterators.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_perfect_matching.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_subchain_enumerator.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/graph_subtree_enumerator.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/max_common_subgraph.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/morgan_code.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/path_enumerator.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/scaffold_detection.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/shortest_path_finder.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/simple_cycle_basis.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/skew_symmetric_flow_finder.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/skew_symmetric_network.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/spanning_tree.cpp	\
$(INDIGO_GRAPH_SRC_DIR)/subgraph_hash.cpp

INDIGO_API_SRCS =	\
$(INDIGO_API_SRC_DIR)/indigo_abbreviations_core.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_abbreviations_expand.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_array.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_basic.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_calc.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_composition.cpp	\
$(INDIGO_API_SRC_DIR)/indigo.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_deconvolution.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_fingerprints.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_io.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_layout.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_loaders.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_mapping.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_match.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_misc.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_molecule.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_object.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_options.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_product_enumerator.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_properties.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_reaction.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_savers.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_scaffold.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_stereo.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_tautomer_enumerator.cpp	\
$(INDIGO_API_SRC_DIR)/option_manager.cpp	\
$(INDIGO_API_SRC_DIR)/indigo_macros.c

ZLIB_OBJS =	\
$(BIN_3RD_OBJ_DIR)/adler32.o	\
$(BIN_3RD_OBJ_DIR)/compress.o	\
$(BIN_3RD_OBJ_DIR)/crc32.o	\
$(BIN_3RD_OBJ_DIR)/deflate.o	\
$(BIN_3RD_OBJ_DIR)/gzclose.o	\
$(BIN_3RD_OBJ_DIR)/gzlib.o	\
$(BIN_3RD_OBJ_DIR)/gzread.o	\
$(BIN_3RD_OBJ_DIR)/gzwrite.o	\
$(BIN_3RD_OBJ_DIR)/infback.o	\
$(BIN_3RD_OBJ_DIR)/inffast.o	\
$(BIN_3RD_OBJ_DIR)/inflate.o	\
$(BIN_3RD_OBJ_DIR)/inftrees.o	\
$(BIN_3RD_OBJ_DIR)/trees.o	\
$(BIN_3RD_OBJ_DIR)/uncompr.o	\
$(BIN_3RD_OBJ_DIR)/zutil.o


TINYXML_OBJS =	\
$(BIN_3RD_OBJ_DIR)/tinystr.o	\
$(BIN_3RD_OBJ_DIR)/tinyxml.o	\
$(BIN_3RD_OBJ_DIR)/tinyxmlerror.o	\
$(BIN_3RD_OBJ_DIR)/tinyxmlparser.o	\

INCHI_OBJS = \
$(BIN_OBJ_DIR)/ichi_bns.o	\
$(BIN_OBJ_DIR)/ichi_io.o	\
$(BIN_OBJ_DIR)/ichicano.o	\
$(BIN_OBJ_DIR)/ichican2.o	\
$(BIN_OBJ_DIR)/ichicans.o	\
$(BIN_OBJ_DIR)/ichierr.o	\
$(BIN_OBJ_DIR)/ichiisot.o	\
$(BIN_OBJ_DIR)/ichimake.o	\
$(BIN_OBJ_DIR)/ichimak2.o	\
$(BIN_OBJ_DIR)/ichimap1.o	\
$(BIN_OBJ_DIR)/ichimap2.o	\
$(BIN_OBJ_DIR)/ichimap4.o	\
$(BIN_OBJ_DIR)/ichinorm.o	\
$(BIN_OBJ_DIR)/ichiprt1.o	\
$(BIN_OBJ_DIR)/ichiprt2.o	\
$(BIN_OBJ_DIR)/ichiprt3.o	\
$(BIN_OBJ_DIR)/ichiqueu.o	\
$(BIN_OBJ_DIR)/ichiring.o	\
$(BIN_OBJ_DIR)/ichisort.o	\
$(BIN_OBJ_DIR)/ichister.o	\
$(BIN_OBJ_DIR)/ichitaut.o	\
$(BIN_OBJ_DIR)/ichiparm.o	\
$(BIN_OBJ_DIR)/ichiread.o	\
$(BIN_OBJ_DIR)/ichirvr1.o	\
$(BIN_OBJ_DIR)/ichirvr2.o	\
$(BIN_OBJ_DIR)/ichirvr3.o	\
$(BIN_OBJ_DIR)/ichirvr4.o	\
$(BIN_OBJ_DIR)/ichirvr5.o	\
$(BIN_OBJ_DIR)/ichirvr6.o	\
$(BIN_OBJ_DIR)/ichirvr7.o	\
$(BIN_OBJ_DIR)/ikey_base26.o	\
$(BIN_OBJ_DIR)/ikey_dll.o	\
$(BIN_OBJ_DIR)/mol_fmt1.o	\
$(BIN_OBJ_DIR)/mol_fmt2.o	\
$(BIN_OBJ_DIR)/mol_fmt3.o	\
$(BIN_OBJ_DIR)/mol_fmt4.o	\
$(BIN_OBJ_DIR)/runichi.o	\
$(BIN_OBJ_DIR)/runichi2.o	\
$(BIN_OBJ_DIR)/runichi3.o	\
$(BIN_OBJ_DIR)/runichi4.o	\
$(BIN_OBJ_DIR)/sha2.o	\
$(BIN_OBJ_DIR)/strutil.o	\
$(BIN_OBJ_DIR)/util.o	\
$(BIN_OBJ_DIR)/mol2atom.o	\
$(BIN_OBJ_DIR)/readinch.o	\
$(BIN_OBJ_DIR)/inchi_dll.o	\
$(BIN_OBJ_DIR)/inchi_dll_a.o	\
$(BIN_OBJ_DIR)/inchi_dll_a2.o	\
$(BIN_OBJ_DIR)/inchi_dll_b.o	\
$(BIN_OBJ_DIR)/inchi_dll_main.o	\
$(BIN_OBJ_DIR)/ichilnct.o

INDIGO_COMMON_BASEC_OBJS =	\
$(BIN_OBJ_DIR)/bitarray.o	\
$(BIN_OBJ_DIR)/nano_posix.o	\
$(BIN_OBJ_DIR)/os_dir_posix.o	\
$(BIN_OBJ_DIR)/os_sync_posix.o	\
$(BIN_OBJ_DIR)/os_thread_posix.o	\
$(BIN_OBJ_DIR)/os_tls_posix.o

INDIGO_COMMON_BASECPP_OBJS = \
$(BIN_OBJ_DIR)/bitinworker.o	\
$(BIN_OBJ_DIR)/bitoutworker.o	\
$(BIN_OBJ_DIR)/cancellation_handler.o	\
$(BIN_OBJ_DIR)/chunk_storage.o	\
$(BIN_OBJ_DIR)/common_exceptions_impl.o	\
$(BIN_OBJ_DIR)/crc32.o	\
$(BIN_OBJ_DIR)/d_bitset.o	\
$(BIN_OBJ_DIR)/exception.o	\
$(BIN_OBJ_DIR)/gray_codes.o	\
$(BIN_OBJ_DIR)/io_base.o	\
$(BIN_OBJ_DIR)/locale_guard.o	\
$(BIN_OBJ_DIR)/os_sync_wrapper.o	\
$(BIN_OBJ_DIR)/os_thread_wrapper.o	\
$(BIN_OBJ_DIR)/output.o	\
$(BIN_OBJ_DIR)/profiling.o	\
$(BIN_OBJ_DIR)/properties_map.o	\
$(BIN_OBJ_DIR)/scanner.o	\
$(BIN_OBJ_DIR)/shared_ptr.o	\
$(BIN_OBJ_DIR)/shmem_posix.o	\
$(BIN_OBJ_DIR)/smart_output.o	\
$(BIN_OBJ_DIR)/string_pool.o	\
$(BIN_OBJ_DIR)/tlscont.o

INDIGO_COMMON_MATH_OBJS = 	\
$(BIN_OBJ_DIR)/best_fit.o	\
$(BIN_OBJ_DIR)/line3f.o	\
$(BIN_OBJ_DIR)/lseg3f.o	\
$(BIN_OBJ_DIR)/matr3x3d.o	\
$(BIN_OBJ_DIR)/plane3f.o	\
$(BIN_OBJ_DIR)/random.o	\
$(BIN_OBJ_DIR)/statistics.o	\
$(BIN_OBJ_DIR)/transform3f.o	\
$(BIN_OBJ_DIR)/vec2f.o	\
$(BIN_OBJ_DIR)/vec3f.o

INDIGO_COMMON_LZW_OBJS =	\
$(BIN_OBJ_DIR)/lzw_decoder.o	\
$(BIN_OBJ_DIR)/lzw_dictionary.o	\
$(BIN_OBJ_DIR)/lzw_encoder.o

INDIGO_COMMON_GZIP_OBJS =	\
$(BIN_OBJ_DIR)/gzip_output.o	\
$(BIN_OBJ_DIR)/gzip_scanner.o

INDIGO_MOLECULE_OBJS =	\
$(BIN_OBJ_DIR)/base_molecule.o	\
$(BIN_OBJ_DIR)/canonical_smiles_saver.o	\
$(BIN_OBJ_DIR)/cmf_loader.o	\
$(BIN_OBJ_DIR)/cmf_saver.o	\
$(BIN_OBJ_DIR)/elements.o	\
$(BIN_OBJ_DIR)/haworth_projection_finder.o	\
$(BIN_OBJ_DIR)/icm_loader.o	\
$(BIN_OBJ_DIR)/icm_saver.o	\
$(BIN_OBJ_DIR)/max_common_submolecule.o	\
$(BIN_OBJ_DIR)/molecule_3d_constraints.o	\
$(BIN_OBJ_DIR)/molecule_allene_stereo.o	\
$(BIN_OBJ_DIR)/molecule_arom.o	\
$(BIN_OBJ_DIR)/molecule_arom_match.o	\
$(BIN_OBJ_DIR)/molecule_auto_loader.o	\
$(BIN_OBJ_DIR)/molecule_automorphism_search.o	\
$(BIN_OBJ_DIR)/molecule_cdx_loader.o	\
$(BIN_OBJ_DIR)/molecule_cdx_saver.o	\
$(BIN_OBJ_DIR)/molecule_chain_fingerprints.o	\
$(BIN_OBJ_DIR)/molecule_cis_trans.o	\
$(BIN_OBJ_DIR)/molecule.o	\
$(BIN_OBJ_DIR)/molecule_dearom.o	\
$(BIN_OBJ_DIR)/molecule_electrons_localizer.o	\
$(BIN_OBJ_DIR)/molecule_exact_matcher.o	\
$(BIN_OBJ_DIR)/molecule_exact_substructure_matcher.o	\
$(BIN_OBJ_DIR)/molecule_fingerprint.o	\
$(BIN_OBJ_DIR)/molecule_gross_formula.o	\
$(BIN_OBJ_DIR)/molecule_gross_formula_options.o	\
$(BIN_OBJ_DIR)/molecule_ionize.o	\
$(BIN_OBJ_DIR)/molecule_layered_molecules.o	\
$(BIN_OBJ_DIR)/molecule_mass.o	\
$(BIN_OBJ_DIR)/molecule_mass_options.o	\
$(BIN_OBJ_DIR)/molecule_name_parser.o	\
$(BIN_OBJ_DIR)/molecule_neighbourhood_counters.o	\
$(BIN_OBJ_DIR)/molecule_pi_systems_matcher.o	\
$(BIN_OBJ_DIR)/molecule_rgroups_composition.o	\
$(BIN_OBJ_DIR)/molecule_rgroups.o	\
$(BIN_OBJ_DIR)/molecule_savers.o	\
$(BIN_OBJ_DIR)/molecule_scaffold_detection.o	\
$(BIN_OBJ_DIR)/molecule_sgroups.o	\
$(BIN_OBJ_DIR)/molecule_standardize.o	\
$(BIN_OBJ_DIR)/molecule_standardize_options.o	\
$(BIN_OBJ_DIR)/molecule_stereocenter_options.o	\
$(BIN_OBJ_DIR)/molecule_stereocenters.o	\
$(BIN_OBJ_DIR)/molecule_substructure_matcher.o	\
$(BIN_OBJ_DIR)/molecule_tautomer_chain.o	\
$(BIN_OBJ_DIR)/molecule_tautomer_enumerator.o	\
$(BIN_OBJ_DIR)/molecule_tautomer_match.o	\
$(BIN_OBJ_DIR)/molecule_tautomer_matcher.o	\
$(BIN_OBJ_DIR)/molecule_tautomer_substructure_matcher.o	\
$(BIN_OBJ_DIR)/molecule_tautomer_superstructure.o	\
$(BIN_OBJ_DIR)/molecule_tautomer_utils.o	\
$(BIN_OBJ_DIR)/molecule_tgroups.o	\
$(BIN_OBJ_DIR)/molfile_loader.o	\
$(BIN_OBJ_DIR)/molfile_saver.o	\
$(BIN_OBJ_DIR)/multiple_cdx_loader.o	\
$(BIN_OBJ_DIR)/query_molecule.o	\
$(BIN_OBJ_DIR)/rdf_loader.o	\
$(BIN_OBJ_DIR)/sdf_loader.o	\
$(BIN_OBJ_DIR)/smiles_loader.o	\
$(BIN_OBJ_DIR)/smiles_saver.o	\
$(BIN_OBJ_DIR)/cml_loader.o	\
$(BIN_OBJ_DIR)/cml_saver.o	\
$(BIN_OBJ_DIR)/multiple_cml_loader.o	\
$(BIN_OBJ_DIR)/molecule_cdxml_saver.o	\
$(BIN_OBJ_DIR)/molecule_inchi_component.o	\
$(BIN_OBJ_DIR)/molecule_inchi.o	\
$(BIN_OBJ_DIR)/molecule_inchi_layers.o	\
$(BIN_OBJ_DIR)/molecule_inchi_utils.o	\
$(BIN_OBJ_DIR)/inchi_parser.o	\
$(BIN_OBJ_DIR)/inchi_wrapper.o

INDIGO_REACTION_OBJS =	\
$(BIN_OBJ_DIR)/base_reaction.o	\
$(BIN_OBJ_DIR)/base_reaction_substructure_matcher.o	\
$(BIN_OBJ_DIR)/canonical_rsmiles_saver.o	\
$(BIN_OBJ_DIR)/crf_loader.o	\
$(BIN_OBJ_DIR)/crf_saver.o	\
$(BIN_OBJ_DIR)/icr_loader.o	\
$(BIN_OBJ_DIR)/icr_saver.o	\
$(BIN_OBJ_DIR)/query_reaction.o	\
$(BIN_OBJ_DIR)/reaction_auto_loader.o	\
$(BIN_OBJ_DIR)/reaction_automapper.o	\
$(BIN_OBJ_DIR)/reaction_cdx_loader.o	\
$(BIN_OBJ_DIR)/reaction_cdxml_saver.o	\
$(BIN_OBJ_DIR)/reaction_cdx_saver.o	\
$(BIN_OBJ_DIR)/reaction_cml_loader.o	\
$(BIN_OBJ_DIR)/reaction_cml_saver.o	\
$(BIN_OBJ_DIR)/reaction.o	\
$(BIN_OBJ_DIR)/reaction_enumerator_state.o	\
$(BIN_OBJ_DIR)/reaction_exact_matcher.o	\
$(BIN_OBJ_DIR)/reaction_fingerprint.o	\
$(BIN_OBJ_DIR)/reaction_gross_formula.o	\
$(BIN_OBJ_DIR)/reaction_neighborhood_counters.o	\
$(BIN_OBJ_DIR)/reaction_product_enumerator.o	\
$(BIN_OBJ_DIR)/reaction_substructure_matcher.o	\
$(BIN_OBJ_DIR)/reaction_transformation.o	\
$(BIN_OBJ_DIR)/rsmiles_loader.o	\
$(BIN_OBJ_DIR)/rsmiles_saver.o	\
$(BIN_OBJ_DIR)/rxnfile_loader.o	\
$(BIN_OBJ_DIR)/rxnfile_saver.o

INDIGO_LAYOUT_OBJS = 	\
$(BIN_OBJ_DIR)/attachment_layout.o	\
$(BIN_OBJ_DIR)/layout_pattern.o	\
$(BIN_OBJ_DIR)/layout_pattern_smart.o	\
$(BIN_OBJ_DIR)/metalayout.o	\
$(BIN_OBJ_DIR)/molecule_cleaner_2d.o	\
$(BIN_OBJ_DIR)/molecule_layout.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_assign.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_assign_smart.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_attach.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_border.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_cycle.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_geom.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_refine.o	\
$(BIN_OBJ_DIR)/molecule_layout_graph_smart.o	\
$(BIN_OBJ_DIR)/molecule_layout_macrocycle_lattice.o	\
$(BIN_OBJ_DIR)/molecule_layout_macrocycles.o	\
$(BIN_OBJ_DIR)/reaction_layout.o	\
$(BIN_OBJ_DIR)/refinement_state.o

INDIGO_GRAPH_OBJS =	\
$(BIN_OBJ_DIR)/automorphism_search.o	\
$(BIN_OBJ_DIR)/aux_path_finder.o	\
$(BIN_OBJ_DIR)/biconnected_decomposer.o	\
$(BIN_OBJ_DIR)/cycle_basis.o	\
$(BIN_OBJ_DIR)/cycle_enumerator.o	\
$(BIN_OBJ_DIR)/dfs_walk.o	\
$(BIN_OBJ_DIR)/edge_rotation_matcher.o	\
$(BIN_OBJ_DIR)/edge_subgraph_enumerator.o	\
$(BIN_OBJ_DIR)/embedding_enumerator.o	\
$(BIN_OBJ_DIR)/embeddings_storage.o	\
$(BIN_OBJ_DIR)/filter.o	\
$(BIN_OBJ_DIR)/graph_affine_matcher.o	\
$(BIN_OBJ_DIR)/graph_constrained_bmatching_finder.o	\
$(BIN_OBJ_DIR)/graph.o	\
$(BIN_OBJ_DIR)/graph_decomposer.o	\
$(BIN_OBJ_DIR)/graph_fast_access.o	\
$(BIN_OBJ_DIR)/graph_iterators.o	\
$(BIN_OBJ_DIR)/graph_perfect_matching.o	\
$(BIN_OBJ_DIR)/graph_subchain_enumerator.o	\
$(BIN_OBJ_DIR)/graph_subtree_enumerator.o	\
$(BIN_OBJ_DIR)/max_common_subgraph.o	\
$(BIN_OBJ_DIR)/morgan_code.o	\
$(BIN_OBJ_DIR)/path_enumerator.o	\
$(BIN_OBJ_DIR)/scaffold_detection.o	\
$(BIN_OBJ_DIR)/shortest_path_finder.o	\
$(BIN_OBJ_DIR)/simple_cycle_basis.o	\
$(BIN_OBJ_DIR)/skew_symmetric_flow_finder.o	\
$(BIN_OBJ_DIR)/skew_symmetric_network.o	\
$(BIN_OBJ_DIR)/spanning_tree.o	\
$(BIN_OBJ_DIR)/subgraph_hash.o


INDIGO_API_OBJS =	\
$(BIN_OBJ_DIR)/indigo_abbreviations_core.o	\
$(BIN_OBJ_DIR)/indigo_abbreviations_expand.o	\
$(BIN_OBJ_DIR)/indigo_array.o	\
$(BIN_OBJ_DIR)/indigo_basic.o	\
$(BIN_OBJ_DIR)/indigo_calc.o	\
$(BIN_OBJ_DIR)/indigo_composition.o	\
$(BIN_OBJ_DIR)/indigo.o	\
$(BIN_OBJ_DIR)/indigo_deconvolution.o	\
$(BIN_OBJ_DIR)/indigo_fingerprints.o	\
$(BIN_OBJ_DIR)/indigo_io.o	\
$(BIN_OBJ_DIR)/indigo_layout.o	\
$(BIN_OBJ_DIR)/indigo_loaders.o	\
$(BIN_OBJ_DIR)/indigo_mapping.o	\
$(BIN_OBJ_DIR)/indigo_match.o	\
$(BIN_OBJ_DIR)/indigo_misc.o	\
$(BIN_OBJ_DIR)/indigo_molecule.o	\
$(BIN_OBJ_DIR)/indigo_object.o	\
$(BIN_OBJ_DIR)/indigo_options.o	\
$(BIN_OBJ_DIR)/indigo_product_enumerator.o	\
$(BIN_OBJ_DIR)/indigo_properties.o	\
$(BIN_OBJ_DIR)/indigo_reaction.o	\
$(BIN_OBJ_DIR)/indigo_savers.o	\
$(BIN_OBJ_DIR)/indigo_scaffold.o	\
$(BIN_OBJ_DIR)/indigo_stereo.o	\
$(BIN_OBJ_DIR)/indigo_tautomer_enumerator.o	\
$(BIN_OBJ_DIR)/option_manager.o	\
$(BIN_OBJ_DIR)/indigo_macros.o

ifdef NATIVE
BENCH_ALGORITHMS_OBJS =	\
$(BIN_OBJ_DIR)/benchmarkAlgorithms.o
BENCH_NAMETOMOL_OBJS =	\
$(BIN_OBJ_DIR)/benchmarkNameToMol.o
TEST_BUILDER_OBJS =	\
$(BIN_OBJ_DIR)/indigoTestDataBuilder.o
else
MAIN_OBJS =	\
$(BIN_OBJ_DIR)/indigoErrorHandler.o
endif

ALL_OBJS = $(ZLIB_OBJS) $(TINYXML_OBJS) $(INCHI_OBJS) $(INDIGO_COMMON_BASEC_OBJS) $(INDIGO_COMMON_BASECPP_OBJS) $(INDIGO_COMMON_MATH_OBJS) $(INDIGO_COMMON_LZW_OBJS) $(INDIGO_COMMON_GZIP_OBJS) $(INDIGO_MOLECULE_OBJS) $(INDIGO_REACTION_OBJS) $(INDIGO_LAYOUT_OBJS) $(INDIGO_GRAPH_OBJS) $(INDIGO_API_OBJS) $(MAIN_OBJS)



all:createDirs exeTasks

createDirs:
	-mkdir ../bin
	-mkdir ../bin/obj_native
	-mkdir ../bin/obj_native/3rdParty
	-mkdir ../bin/obj_emcc
	-mkdir ../bin/obj_emcc/3rdParty
	
ifdef NATIVE
exeTasks: $(EXE_ALGORITHM_PATHNAME) $(EXE_NAMETOMOL_PATHNAME) $(EXE_TESTBUILDER_PATHNAME)
else	
exeTasks: $(EXE_PATHNAME) copyJsAdapter
endif

copyJsAdapter:
	-cp ../src/indigoAdapter.js ../bin/

$(EXE_PATHNAME) : $(ALL_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_PATHNAME) $(ALL_OBJS) -lm $(OPTIMIZE)
$(EXE_ALGORITHM_PATHNAME) : $(ALL_OBJS) $(BENCH_ALGORITHMS_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_ALGORITHM_PATHNAME) $(ALL_OBJS) $(BENCH_ALGORITHMS_OBJS) -lm $(OPTIMIZE)
$(EXE_NAMETOMOL_PATHNAME) : $(ALL_OBJS) $(BENCH_NAMETOMOL_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_NAMETOMOL_PATHNAME) $(ALL_OBJS) $(BENCH_NAMETOMOL_OBJS) -lm $(OPTIMIZE)
$(EXE_TESTBUILDER_PATHNAME) : $(ALL_OBJS) $(TEST_BUILDER_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_TESTBUILDER_PATHNAME) $(ALL_OBJS) $(TEST_BUILDER_OBJS) -lm $(OPTIMIZE)
#$(BIN_OBJ_DIR)/bitarray.o:
#	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $(INDIGO_COMMON_BASEC_DIR)/bitarray.c -o $@
#$(BIN_OBJ_DIR)/base_molecule.o:
#	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $(INDIGO_MOLECULE_SRC_DIR)/base_molecule.cpp -o $@
#$(BIN_OBJ_DIR)/adler32.o:
#	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $(INDIGO_ZLIB_SRC_DIR)/adler32.c -o $@

#-UMAKECRCH	
$(BIN_3RD_OBJ_DIR)/%.o: $(INDIGO_ZLIB_SRC_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) -Wno-implicit-function-declaration $< -o $@
$(BIN_3RD_OBJ_DIR)/%.o: $(INDIGO_TINYXML_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@

ifdef INCHI_FIXER_DIR
$(BIN_OBJ_DIR)/%.o: $(INCHI_FIXER_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
endif	
	
#DCOMPILE_ANSI_ONLY	
$(BIN_OBJ_DIR)/%.o: $(INDIGO_INCHI_BASE_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_INCHI_API_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS)  $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_INCHI_API_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS)  $< -o $@
	
$(BIN_OBJ_DIR)/%.o: $(INDIGO_COMMON_BASEC_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_COMMON_BASECPP_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_COMMON_MATH_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_COMMON_LZW_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_COMMON_GZIP_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
	
$(BIN_OBJ_DIR)/%.o: $(INDIGO_MOLECULE_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_REACTION_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
	
$(BIN_OBJ_DIR)/%.o: $(INDIGO_LAYOUT_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
	
$(BIN_OBJ_DIR)/%.o: $(INDIGO_GRAPH_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
	
$(BIN_OBJ_DIR)/%.o: $(INDIGO_API_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(INDIGO_API_SRC_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
	
$(BIN_OBJ_DIR)/%.o: $(MAIN_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
	
$(BIN_OBJ_DIR)/%.o: $(TEST_BUILDER_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
	
.PHONY:clean
clean :
	-rm $(BIN_OBJ_DIR)/*.o
	-rm $(BIN_3RD_OBJ_DIR)/*.o