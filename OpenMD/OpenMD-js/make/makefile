# Paths
EXE_NAME = openMD
EXE_NAME_OMD_RUNNER = omdRunner
EXE_NAME_TEST_RUNNER = omTestDataBuilder

OPENMD_BASE_DIR = ../../openMD-src/src
OPENMD_SRC_DIR = $(OPENMD_BASE_DIR)/src
OPENMD_BIN_DIR = ../../openMD-src/build-linux
ADAPTER_SRC_DIR = ../adapter_src
BENCHMARK_CPP_SRC_DIR = ../benchmark/src_cpp
TESTER_CPP_SRC_DIR = ../tester/src_cpp

P_DEFINES = -UHAVE_QHULL -DDISABLE_QHULL
P_INCLUDE = -I. -I$(OPENMD_SRC_DIR)/ -I$(OPENMD_SRC_DIR)/antlr -I$(OPENMD_SRC_DIR)/brains -I$(OPENMD_SRC_DIR)/hydrodynamics -I$(OPENMD_SRC_DIR)/integrators -I$(OPENMD_SRC_DIR)/flucq -I$(OPENMD_SRC_DIR)/io	\
-I$(OPENMD_SRC_DIR)/lattice -I$(OPENMD_SRC_DIR)/math -I$(OPENMD_SRC_DIR)/mdParser -I$(OPENMD_SRC_DIR)/optimization -I$(OPENMD_SRC_DIR)/nonbonded -I$(OPENMD_SRC_DIR)/primitives -I$(OPENMD_SRC_DIR)/perturbations	\
-I$(OPENMD_SRC_DIR)/restraints -I$(OPENMD_SRC_DIR)/selection -I$(OPENMD_SRC_DIR)/types -I$(OPENMD_SRC_DIR)/utils -I$(OPENMD_SRC_DIR)/visitors -I$(OPENMD_SRC_DIR)/rnemd -I$(OPENMD_SRC_DIR)/clusters -I$(ADAPTER_SRC_DIR)

BIN_DIR = ../bin

# The compiler
ifndef EMCC
	NATIVE = 1
	C_COMPILER = gcc
	CPP_COMPILER = g++
	LINKER = g++ -s	
	EXE_EXT = 
	MAIN_DIR = ../benchmark/src_cpp
else
	EMCC = 1	
	
	MAIN_DIR = ../src
	C_COMPILER = emcc
	CPP_COMPILER = emcc
	LINKER = emcc -s
	EXE_EXT = .js
	
	ifndef NO_MODULARIZE
		EMCC_MODULARIZE_OPTION = -s MODULARIZE=1 -s EXPORT_NAME="'OpenMdModule'"
	endif
	
	EMCC_MEM_FILE_OPTION = --memory-init-file 0
	#EMCC_EXTERNAL_FILE_OPTION = --preload-file $(OPENMD_BASE_DIR)/forceFields@/FRC_ROOT	
	EMCC_EXTERNAL_FILE_OPTION = --embed-file $(OPENMD_BASE_DIR)/forceFields@/FRC_ROOT	
	EMCC_MISC_OPTION = -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=1 -s ASSERTIONS=0 -s ALLOW_MEMORY_GROWTH=0 -s TOTAL_MEMORY=33554432 -s FORCE_FILESYSTEM=1 --pre-js ../adapter_src/pre.js --bind
	EMCC_MISC_OPTION += $(EMCC_MODULARIZE_OPTION)
	#-s DEMANGLE_SUPPORT=1 -s ASSERTIONS=1 
	#-s USE_PTHREADS=2
endif


OPTIMIZE = -O3
LINKER_OPTIONS = -pthread $(OPTIMIZE) $(EMCC_MEM_FILE_OPTION) $(EMCC_EXPORT_FUNCS) $(EMCC_EXTERNAL_FILE_OPTION) $(EMCC_MISC_OPTION)
CPP_COMPILER_OPTIONS = $(P_DEFINES) $(P_INCLUDE) $(OPTIMIZE) -c -pthread -std=c++11
C_COMPILER_OPTIONS = $(P_DEFINES) $(P_INCLUDE) $(OPTIMIZE) -c -pthread


ifdef EMCC
	BIN_OBJ_DIR = $(BIN_DIR)/obj_emcc
else
	BIN_OBJ_DIR = $(BIN_DIR)/obj_native
endif

EXE_PATHNAME = $(BIN_DIR)/$(EXE_NAME)$(EXE_EXT)
EXE_OMD_RUNNER_PATHNAME = $(BIN_DIR)/$(EXE_NAME_OMD_RUNNER)$(EXE_EXT)
EXE_TEST_RUNNER_PATHNAME = $(BIN_DIR)/$(EXE_NAME_TEST_RUNNER)$(EXE_EXT)

OPENMD_SRCS = \
$(OPENMD_BIN_DIR)/Revision.cpp	\
$(OPENMD_SRC_DIR)/antlr/ANTLRUtil.cpp	\
$(OPENMD_SRC_DIR)/antlr/ASTFactory.cpp	\
$(OPENMD_SRC_DIR)/antlr/ASTNULLType.cpp	\
$(OPENMD_SRC_DIR)/antlr/ASTRefCount.cpp	\
$(OPENMD_SRC_DIR)/antlr/BaseAST.cpp	\
$(OPENMD_SRC_DIR)/antlr/BitSet.cpp	\
$(OPENMD_SRC_DIR)/antlr/CommonAST.cpp	\
$(OPENMD_SRC_DIR)/antlr/CommonASTWithHiddenTokens.cpp	\
$(OPENMD_SRC_DIR)/antlr/CommonHiddenStreamToken.cpp	\
$(OPENMD_SRC_DIR)/antlr/CommonToken.cpp	\
$(OPENMD_SRC_DIR)/antlr/LLkParser.cpp	\
$(OPENMD_SRC_DIR)/antlr/MismatchedCharException.cpp	\
$(OPENMD_SRC_DIR)/antlr/MismatchedTokenException.cpp	\
$(OPENMD_SRC_DIR)/antlr/NoViableAltException.cpp	\
$(OPENMD_SRC_DIR)/antlr/NoViableAltForCharException.cpp	\
$(OPENMD_SRC_DIR)/antlr/Parser.cpp	\
$(OPENMD_SRC_DIR)/antlr/RecognitionException.cpp	\
$(OPENMD_SRC_DIR)/antlr/String.cpp	\
$(OPENMD_SRC_DIR)/antlr/Token.cpp	\
$(OPENMD_SRC_DIR)/antlr/TokenRefCount.cpp	\
$(OPENMD_SRC_DIR)/antlr/TokenStreamBasicFilter.cpp	\
$(OPENMD_SRC_DIR)/antlr/TokenStreamHiddenTokenFilter.cpp	\
$(OPENMD_SRC_DIR)/antlr/TokenStreamRewriteEngine.cpp	\
$(OPENMD_SRC_DIR)/antlr/TokenStreamSelector.cpp	\
$(OPENMD_SRC_DIR)/antlr/TreeParser.cpp	\
$(OPENMD_SRC_DIR)/brains/BlockSnapshotManager.cpp	\
$(OPENMD_SRC_DIR)/brains/DataStorage.cpp	\
$(OPENMD_SRC_DIR)/brains/ForceField.cpp	\
$(OPENMD_SRC_DIR)/brains/MoleculeCreator.cpp	\
$(OPENMD_SRC_DIR)/brains/PairList.cpp	\
$(OPENMD_SRC_DIR)/brains/Register.cpp	\
$(OPENMD_SRC_DIR)/brains/SimSnapshotManager.cpp	\
$(OPENMD_SRC_DIR)/brains/Snapshot.cpp	\
$(OPENMD_SRC_DIR)/brains/Stats.cpp	\
$(OPENMD_SRC_DIR)/hydrodynamics/Ellipsoid.cpp	\
$(OPENMD_SRC_DIR)/hydrodynamics/HydroProp.cpp	\
$(OPENMD_SRC_DIR)/hydrodynamics/Sphere.cpp	\
$(OPENMD_SRC_DIR)/integrators/DLM.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargeLangevin.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargeParameters.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargeNVE.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargeNVT.cpp	\
$(OPENMD_SRC_DIR)/integrators/Integrator.cpp	\
$(OPENMD_SRC_DIR)/integrators/IntegratorFactory.cpp	\
$(OPENMD_SRC_DIR)/integrators/LangevinDynamics.cpp	\
$(OPENMD_SRC_DIR)/integrators/LDForceManager.cpp	\
$(OPENMD_SRC_DIR)/integrators/NgammaT.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPA.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPAT.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPrT.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPT.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPTf.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPTi.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPTsz.cpp	\
$(OPENMD_SRC_DIR)/integrators/NPTxyz.cpp	\
$(OPENMD_SRC_DIR)/integrators/NVE.cpp	\
$(OPENMD_SRC_DIR)/integrators/NVT.cpp	\
$(OPENMD_SRC_DIR)/integrators/VelocityVerletIntegrator.cpp	\
$(OPENMD_SRC_DIR)/io/AtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/BaseAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/BendTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/BondTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/ChargeAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/DirectionalAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/EAMAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/FluctuatingChargeAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/ForceFieldOptions.cpp	\
$(OPENMD_SRC_DIR)/io/GayBerneAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/Globals.cpp	\
$(OPENMD_SRC_DIR)/io/InversionTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/LennardJonesAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/MultipoleAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/NonBondedInteractionsSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/OptionSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/ParamConstraint.cpp	\
$(OPENMD_SRC_DIR)/io/PolarizableAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/SCAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/SectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/SectionParserManager.cpp	\
$(OPENMD_SRC_DIR)/io/ShapeAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/StickyAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/StickyPowerAtomTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/TorsionTypesSectionParser.cpp	\
$(OPENMD_SRC_DIR)/io/ZConsReader.cpp	\
$(OPENMD_SRC_DIR)/lattice/CubicLattice.cpp	\
$(OPENMD_SRC_DIR)/lattice/FCCLattice.cpp	\
$(OPENMD_SRC_DIR)/lattice/Lattice.cpp	\
$(OPENMD_SRC_DIR)/lattice/LatticeFactory.cpp	\
$(OPENMD_SRC_DIR)/lattice/shapedLattice.cpp	\
$(OPENMD_SRC_DIR)/math/ChebyshevT.cpp	\
$(OPENMD_SRC_DIR)/math/ChebyshevU.cpp	\
$(OPENMD_SRC_DIR)/math/CubicSpline.cpp	\
$(OPENMD_SRC_DIR)/math/LegendrePolynomial.cpp	\
$(OPENMD_SRC_DIR)/math/RealSphericalHarmonic.cpp	\
$(OPENMD_SRC_DIR)/math/RMSD.cpp	\
$(OPENMD_SRC_DIR)/math/SeqRandNumGen.cpp	\
$(OPENMD_SRC_DIR)/math/SphericalHarmonic.cpp	\
$(OPENMD_SRC_DIR)/math/Wigner3jm.cpp	\
$(OPENMD_SRC_DIR)/mdParser/FilenameObserver.cpp	\
$(OPENMD_SRC_DIR)/optimization/OptimizationFactory.cpp	\
$(OPENMD_SRC_DIR)/optimization/Armijo.cpp	\
$(OPENMD_SRC_DIR)/optimization/BFGS.cpp	\
$(OPENMD_SRC_DIR)/optimization/ConjugateGradient.cpp	\
$(OPENMD_SRC_DIR)/optimization/Constraint.cpp	\
$(OPENMD_SRC_DIR)/optimization/EndCriteria.cpp	\
$(OPENMD_SRC_DIR)/optimization/LineSearch.cpp	\
$(OPENMD_SRC_DIR)/optimization/LineSearchBasedMethod.cpp	\
$(OPENMD_SRC_DIR)/optimization/SteepestDescent.cpp	\
$(OPENMD_SRC_DIR)/optimization/PotentialEnergyObjectiveFunction.cpp	\
$(OPENMD_SRC_DIR)/optimization/MinimizerParameters.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/Buckingham.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/EAM.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/GB.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/InteractionManager.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/LJ.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/MAW.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/Morse.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/RepulsivePower.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/Mie.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/SC.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/Sticky.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/SwitchingFunction.cpp	\
$(OPENMD_SRC_DIR)/primitives/Atom.cpp	\
$(OPENMD_SRC_DIR)/primitives/Bend.cpp	\
$(OPENMD_SRC_DIR)/primitives/DirectionalAtom.cpp	\
$(OPENMD_SRC_DIR)/primitives/GhostBend.cpp	\
$(OPENMD_SRC_DIR)/primitives/GhostTorsion.cpp	\
$(OPENMD_SRC_DIR)/primitives/Inversion.cpp	\
$(OPENMD_SRC_DIR)/primitives/Molecule.cpp	\
$(OPENMD_SRC_DIR)/primitives/RigidBody.cpp	\
$(OPENMD_SRC_DIR)/primitives/StuntDouble.cpp	\
$(OPENMD_SRC_DIR)/primitives/ShortRangeInteraction.cpp	\
$(OPENMD_SRC_DIR)/primitives/Torsion.cpp	\
$(OPENMD_SRC_DIR)/primitives/UreyBradleyBend.cpp	\
$(OPENMD_SRC_DIR)/perturbations/UniformField.cpp	\
$(OPENMD_SRC_DIR)/perturbations/UniformGradient.cpp	\
$(OPENMD_SRC_DIR)/restraints/MolecularRestraint.cpp	\
$(OPENMD_SRC_DIR)/restraints/ObjectRestraint.cpp	\
$(OPENMD_SRC_DIR)/selection/HullFinder.cpp	\
$(OPENMD_SRC_DIR)/selection/IndexFinder.cpp	\
$(OPENMD_SRC_DIR)/selection/NameFinder.cpp	\
$(OPENMD_SRC_DIR)/selection/SelectionCompiler.cpp	\
$(OPENMD_SRC_DIR)/selection/SelectionEvaluator.cpp	\
$(OPENMD_SRC_DIR)/selection/SelectionToken.cpp	\
$(OPENMD_SRC_DIR)/selection/TokenMap.cpp	\
$(OPENMD_SRC_DIR)/types/AtomStamp.cpp	\
$(OPENMD_SRC_DIR)/types/AtomType.cpp	\
$(OPENMD_SRC_DIR)/types/BendStamp.cpp	\
$(OPENMD_SRC_DIR)/types/BendTypeParser.cpp	\
$(OPENMD_SRC_DIR)/types/BondStamp.cpp	\
$(OPENMD_SRC_DIR)/types/BondTypeParser.cpp	\
$(OPENMD_SRC_DIR)/types/CharmmTorsionType.cpp	\
$(OPENMD_SRC_DIR)/types/Component.cpp	\
$(OPENMD_SRC_DIR)/types/ConstraintStamp.cpp	\
$(OPENMD_SRC_DIR)/types/CutoffGroupStamp.cpp	\
$(OPENMD_SRC_DIR)/types/DirectionalAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/EAMAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/FixedChargeAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/FluctuatingChargeAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/FragmentStamp.cpp	\
$(OPENMD_SRC_DIR)/types/GayBerneAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/ImproperCosineInversionType.cpp	\
$(OPENMD_SRC_DIR)/types/InversionStamp.cpp	\
$(OPENMD_SRC_DIR)/types/InversionTypeParser.cpp	\
$(OPENMD_SRC_DIR)/types/LennardJonesAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/MoleculeStamp.cpp	\
$(OPENMD_SRC_DIR)/types/MultipoleAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/NonBondedInteractionType.cpp	\
$(OPENMD_SRC_DIR)/types/PolarizableAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/RestraintStamp.cpp	\
$(OPENMD_SRC_DIR)/types/RigidBodyStamp.cpp	\
$(OPENMD_SRC_DIR)/types/ShapeAtomType.cpp	\
$(OPENMD_SRC_DIR)/types/StickyAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/SuttonChenAdapter.cpp	\
$(OPENMD_SRC_DIR)/types/TorsionStamp.cpp	\
$(OPENMD_SRC_DIR)/types/TorsionTypeParser.cpp	\
$(OPENMD_SRC_DIR)/types/ZconsStamp.cpp	\
$(OPENMD_SRC_DIR)/utils/ElementsTable.cpp	\
$(OPENMD_SRC_DIR)/utils/MoLocator.cpp	\
$(OPENMD_SRC_DIR)/utils/PropertyMap.cpp	\
$(OPENMD_SRC_DIR)/utils/StringTokenizer.cpp	\
$(OPENMD_SRC_DIR)/utils/StringUtils.cpp	\
$(OPENMD_SRC_DIR)/utils/Trim.cpp	\
$(OPENMD_SRC_DIR)/utils/Utility.cpp	\
$(OPENMD_SRC_DIR)/utils/wildcards.cpp	\
$(OPENMD_SRC_DIR)/visitors/AtomNameVisitor.cpp	\
$(OPENMD_SRC_DIR)/visitors/AtomVisitor.cpp	\
$(OPENMD_SRC_DIR)/visitors/CompositeVisitor.cpp	\
$(OPENMD_SRC_DIR)/visitors/LipidTransVisitor.cpp	\
$(OPENMD_SRC_DIR)/visitors/OtherVisitor.cpp	\
$(OPENMD_SRC_DIR)/visitors/ReplacementVisitor.cpp	\
$(OPENMD_SRC_DIR)/visitors/RigidBodyVisitor.cpp	\
$(OPENMD_SRC_DIR)/visitors/ZconsVisitor.cpp	\
$(OPENMD_SRC_DIR)/rnemd/RNEMDParameters.cpp	\
$(OPENMD_SRC_DIR)/clusters/Icosahedron.cpp	\
$(OPENMD_SRC_DIR)/clusters/Cuboctahedron.cpp	\
$(OPENMD_SRC_DIR)/clusters/Decahedron.cpp

OPENMD_PARALLEL_SRCS =	\
$(OPENMD_SRC_DIR)/antlr/CharBuffer.cpp	\
$(OPENMD_SRC_DIR)/antlr/CharScanner.cpp	\
$(OPENMD_SRC_DIR)/antlr/InputBuffer.cpp	\
$(OPENMD_SRC_DIR)/antlr/TokenBuffer.cpp	\
$(OPENMD_SRC_DIR)/mdParser/MDLexer.cpp	\
$(OPENMD_SRC_DIR)/mdParser/MDParser.cpp	\
$(OPENMD_SRC_DIR)/mdParser/MDTreeParser.cpp	\
$(OPENMD_SRC_DIR)/brains/ForceManager.cpp	\
$(OPENMD_SRC_DIR)/brains/SimCreator.cpp	\
$(OPENMD_SRC_DIR)/brains/SimInfo.cpp	\
$(OPENMD_SRC_DIR)/brains/Thermo.cpp	\
$(OPENMD_SRC_DIR)/constraints/ZconstraintForceManager.cpp	\
$(OPENMD_SRC_DIR)/constraints/Rattle.cpp	\
$(OPENMD_SRC_DIR)/constraints/Shake.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargeConstraints.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargeObjectiveFunction.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargeForces.cpp	\
$(OPENMD_SRC_DIR)/flucq/FluctuatingChargePropagator.cpp	\
$(OPENMD_SRC_DIR)/integrators/LangevinHullForceManager.cpp	\
$(OPENMD_SRC_DIR)/rnemd/RNEMD.cpp	\
$(OPENMD_SRC_DIR)/integrators/Velocitizer.cpp	\
$(OPENMD_SRC_DIR)/io/ConstraintWriter.cpp	\
$(OPENMD_SRC_DIR)/io/DumpReader.cpp	\
$(OPENMD_SRC_DIR)/io/DumpWriter.cpp	\
$(OPENMD_SRC_DIR)/io/RestReader.cpp	\
$(OPENMD_SRC_DIR)/io/RestWriter.cpp	\
$(OPENMD_SRC_DIR)/io/StatWriter.cpp	\
$(OPENMD_SRC_DIR)/io/ZConsWriter.cpp	\
$(OPENMD_SRC_DIR)/io/ifstrstream.cpp	\
$(OPENMD_SRC_DIR)/math/ParallelRandNumGen.cpp	\
$(OPENMD_SRC_DIR)/nonbonded/Electrostatic.cpp	\
$(OPENMD_SRC_DIR)/parallel/ForceDecomposition.cpp	\
$(OPENMD_SRC_DIR)/parallel/ForceMatrixDecomposition.cpp	\
$(OPENMD_SRC_DIR)/restraints/RestraintForceManager.cpp	\
$(OPENMD_SRC_DIR)/restraints/ThermoIntegrationForceManager.cpp	\
$(OPENMD_SRC_DIR)/selection/DistanceFinder.cpp	\
$(OPENMD_SRC_DIR)/selection/SelectionManager.cpp	\
$(OPENMD_SRC_DIR)/selection/SelectionSet.cpp	\
$(OPENMD_SRC_DIR)/utils/ProgressBar.cpp	\
$(OPENMD_SRC_DIR)/utils/simError.cpp	\
$(OPENMD_SRC_DIR)/utils/OpenMDBitSet.cpp	\
$(OPENMD_SRC_DIR)/optimization/Problem.cpp

OPENMD_QHULL_PARALLEL_SRCS =	\
$(OPENMD_SRC_DIR)/integrators/LangevinHullForceManager.cpp	\
$(OPENMD_SRC_DIR)/math/ConvexHull.cpp	\
$(OPENMD_SRC_DIR)/math/AlphaHull.cpp

OPENMD_OBJS = \
$(BIN_OBJ_DIR)/Revision.o	\
$(BIN_OBJ_DIR)/ANTLRUtil.o	\
$(BIN_OBJ_DIR)/ASTFactory.o	\
$(BIN_OBJ_DIR)/ASTNULLType.o	\
$(BIN_OBJ_DIR)/ASTRefCount.o	\
$(BIN_OBJ_DIR)/BaseAST.o	\
$(BIN_OBJ_DIR)/BitSet.o	\
$(BIN_OBJ_DIR)/CommonAST.o	\
$(BIN_OBJ_DIR)/CommonASTWithHiddenTokens.o	\
$(BIN_OBJ_DIR)/CommonHiddenStreamToken.o	\
$(BIN_OBJ_DIR)/CommonToken.o	\
$(BIN_OBJ_DIR)/LLkParser.o	\
$(BIN_OBJ_DIR)/MismatchedCharException.o	\
$(BIN_OBJ_DIR)/MismatchedTokenException.o	\
$(BIN_OBJ_DIR)/NoViableAltException.o	\
$(BIN_OBJ_DIR)/NoViableAltForCharException.o	\
$(BIN_OBJ_DIR)/Parser.o	\
$(BIN_OBJ_DIR)/RecognitionException.o	\
$(BIN_OBJ_DIR)/String.o	\
$(BIN_OBJ_DIR)/Token.o	\
$(BIN_OBJ_DIR)/TokenRefCount.o	\
$(BIN_OBJ_DIR)/TokenStreamBasicFilter.o	\
$(BIN_OBJ_DIR)/TokenStreamHiddenTokenFilter.o	\
$(BIN_OBJ_DIR)/TokenStreamRewriteEngine.o	\
$(BIN_OBJ_DIR)/TokenStreamSelector.o	\
$(BIN_OBJ_DIR)/TreeParser.o	\
$(BIN_OBJ_DIR)/BlockSnapshotManager.o	\
$(BIN_OBJ_DIR)/DataStorage.o	\
$(BIN_OBJ_DIR)/ForceField.o	\
$(BIN_OBJ_DIR)/MoleculeCreator.o	\
$(BIN_OBJ_DIR)/PairList.o	\
$(BIN_OBJ_DIR)/Register.o	\
$(BIN_OBJ_DIR)/SimSnapshotManager.o	\
$(BIN_OBJ_DIR)/Snapshot.o	\
$(BIN_OBJ_DIR)/Stats.o	\
$(BIN_OBJ_DIR)/Ellipsoid.o	\
$(BIN_OBJ_DIR)/HydroProp.o	\
$(BIN_OBJ_DIR)/Sphere.o	\
$(BIN_OBJ_DIR)/DLM.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeLangevin.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeParameters.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeNVE.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeNVT.o	\
$(BIN_OBJ_DIR)/Integrator.o	\
$(BIN_OBJ_DIR)/IntegratorFactory.o	\
$(BIN_OBJ_DIR)/LangevinDynamics.o	\
$(BIN_OBJ_DIR)/LDForceManager.o	\
$(BIN_OBJ_DIR)/NgammaT.o	\
$(BIN_OBJ_DIR)/NPA.o	\
$(BIN_OBJ_DIR)/NPAT.o	\
$(BIN_OBJ_DIR)/NPrT.o	\
$(BIN_OBJ_DIR)/NPT.o	\
$(BIN_OBJ_DIR)/NPTf.o	\
$(BIN_OBJ_DIR)/NPTi.o	\
$(BIN_OBJ_DIR)/NPTsz.o	\
$(BIN_OBJ_DIR)/NPTxyz.o	\
$(BIN_OBJ_DIR)/NVE.o	\
$(BIN_OBJ_DIR)/NVT.o	\
$(BIN_OBJ_DIR)/VelocityVerletIntegrator.o	\
$(BIN_OBJ_DIR)/AtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/BaseAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/BendTypesSectionParser.o	\
$(BIN_OBJ_DIR)/BondTypesSectionParser.o	\
$(BIN_OBJ_DIR)/ChargeAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/DirectionalAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/EAMAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/ForceFieldOptions.o	\
$(BIN_OBJ_DIR)/GayBerneAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/Globals.o	\
$(BIN_OBJ_DIR)/InversionTypesSectionParser.o	\
$(BIN_OBJ_DIR)/LennardJonesAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/MultipoleAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/NonBondedInteractionsSectionParser.o	\
$(BIN_OBJ_DIR)/OptionSectionParser.o	\
$(BIN_OBJ_DIR)/ParamConstraint.o	\
$(BIN_OBJ_DIR)/PolarizableAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/SCAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/SectionParser.o	\
$(BIN_OBJ_DIR)/SectionParserManager.o	\
$(BIN_OBJ_DIR)/ShapeAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/StickyAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/StickyPowerAtomTypesSectionParser.o	\
$(BIN_OBJ_DIR)/TorsionTypesSectionParser.o	\
$(BIN_OBJ_DIR)/ZConsReader.o	\
$(BIN_OBJ_DIR)/CubicLattice.o	\
$(BIN_OBJ_DIR)/FCCLattice.o	\
$(BIN_OBJ_DIR)/Lattice.o	\
$(BIN_OBJ_DIR)/LatticeFactory.o	\
$(BIN_OBJ_DIR)/shapedLattice.o	\
$(BIN_OBJ_DIR)/ChebyshevT.o	\
$(BIN_OBJ_DIR)/ChebyshevU.o	\
$(BIN_OBJ_DIR)/CubicSpline.o	\
$(BIN_OBJ_DIR)/LegendrePolynomial.o	\
$(BIN_OBJ_DIR)/RealSphericalHarmonic.o	\
$(BIN_OBJ_DIR)/RMSD.o	\
$(BIN_OBJ_DIR)/SeqRandNumGen.o	\
$(BIN_OBJ_DIR)/SphericalHarmonic.o	\
$(BIN_OBJ_DIR)/Wigner3jm.o	\
$(BIN_OBJ_DIR)/FilenameObserver.o	\
$(BIN_OBJ_DIR)/OptimizationFactory.o	\
$(BIN_OBJ_DIR)/Armijo.o	\
$(BIN_OBJ_DIR)/BFGS.o	\
$(BIN_OBJ_DIR)/ConjugateGradient.o	\
$(BIN_OBJ_DIR)/Constraint.o	\
$(BIN_OBJ_DIR)/EndCriteria.o	\
$(BIN_OBJ_DIR)/LineSearch.o	\
$(BIN_OBJ_DIR)/LineSearchBasedMethod.o	\
$(BIN_OBJ_DIR)/SteepestDescent.o	\
$(BIN_OBJ_DIR)/PotentialEnergyObjectiveFunction.o	\
$(BIN_OBJ_DIR)/MinimizerParameters.o	\
$(BIN_OBJ_DIR)/Buckingham.o	\
$(BIN_OBJ_DIR)/EAM.o	\
$(BIN_OBJ_DIR)/GB.o	\
$(BIN_OBJ_DIR)/InteractionManager.o	\
$(BIN_OBJ_DIR)/LJ.o	\
$(BIN_OBJ_DIR)/MAW.o	\
$(BIN_OBJ_DIR)/Morse.o	\
$(BIN_OBJ_DIR)/RepulsivePower.o	\
$(BIN_OBJ_DIR)/Mie.o	\
$(BIN_OBJ_DIR)/SC.o	\
$(BIN_OBJ_DIR)/Sticky.o	\
$(BIN_OBJ_DIR)/SwitchingFunction.o	\
$(BIN_OBJ_DIR)/Atom.o	\
$(BIN_OBJ_DIR)/Bend.o	\
$(BIN_OBJ_DIR)/DirectionalAtom.o	\
$(BIN_OBJ_DIR)/GhostBend.o	\
$(BIN_OBJ_DIR)/GhostTorsion.o	\
$(BIN_OBJ_DIR)/Inversion.o	\
$(BIN_OBJ_DIR)/Molecule.o	\
$(BIN_OBJ_DIR)/RigidBody.o	\
$(BIN_OBJ_DIR)/StuntDouble.o	\
$(BIN_OBJ_DIR)/ShortRangeInteraction.o	\
$(BIN_OBJ_DIR)/Torsion.o	\
$(BIN_OBJ_DIR)/UreyBradleyBend.o	\
$(BIN_OBJ_DIR)/UniformField.o	\
$(BIN_OBJ_DIR)/UniformGradient.o	\
$(BIN_OBJ_DIR)/MolecularRestraint.o	\
$(BIN_OBJ_DIR)/ObjectRestraint.o	\
$(BIN_OBJ_DIR)/HullFinder.o	\
$(BIN_OBJ_DIR)/IndexFinder.o	\
$(BIN_OBJ_DIR)/NameFinder.o	\
$(BIN_OBJ_DIR)/SelectionCompiler.o	\
$(BIN_OBJ_DIR)/SelectionEvaluator.o	\
$(BIN_OBJ_DIR)/SelectionToken.o	\
$(BIN_OBJ_DIR)/TokenMap.o	\
$(BIN_OBJ_DIR)/AtomStamp.o	\
$(BIN_OBJ_DIR)/AtomType.o	\
$(BIN_OBJ_DIR)/BendStamp.o	\
$(BIN_OBJ_DIR)/BendTypeParser.o	\
$(BIN_OBJ_DIR)/BondStamp.o	\
$(BIN_OBJ_DIR)/BondTypeParser.o	\
$(BIN_OBJ_DIR)/CharmmTorsionType.o	\
$(BIN_OBJ_DIR)/Component.o	\
$(BIN_OBJ_DIR)/ConstraintStamp.o	\
$(BIN_OBJ_DIR)/CutoffGroupStamp.o	\
$(BIN_OBJ_DIR)/DirectionalAdapter.o	\
$(BIN_OBJ_DIR)/EAMAdapter.o	\
$(BIN_OBJ_DIR)/FixedChargeAdapter.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeAdapter.o	\
$(BIN_OBJ_DIR)/FragmentStamp.o	\
$(BIN_OBJ_DIR)/GayBerneAdapter.o	\
$(BIN_OBJ_DIR)/ImproperCosineInversionType.o	\
$(BIN_OBJ_DIR)/InversionStamp.o	\
$(BIN_OBJ_DIR)/InversionTypeParser.o	\
$(BIN_OBJ_DIR)/LennardJonesAdapter.o	\
$(BIN_OBJ_DIR)/MoleculeStamp.o	\
$(BIN_OBJ_DIR)/MultipoleAdapter.o	\
$(BIN_OBJ_DIR)/NonBondedInteractionType.o	\
$(BIN_OBJ_DIR)/PolarizableAdapter.o	\
$(BIN_OBJ_DIR)/RestraintStamp.o	\
$(BIN_OBJ_DIR)/RigidBodyStamp.o	\
$(BIN_OBJ_DIR)/ShapeAtomType.o	\
$(BIN_OBJ_DIR)/StickyAdapter.o	\
$(BIN_OBJ_DIR)/SuttonChenAdapter.o	\
$(BIN_OBJ_DIR)/TorsionStamp.o	\
$(BIN_OBJ_DIR)/TorsionTypeParser.o	\
$(BIN_OBJ_DIR)/ZconsStamp.o	\
$(BIN_OBJ_DIR)/ElementsTable.o	\
$(BIN_OBJ_DIR)/MoLocator.o	\
$(BIN_OBJ_DIR)/PropertyMap.o	\
$(BIN_OBJ_DIR)/StringTokenizer.o	\
$(BIN_OBJ_DIR)/StringUtils.o	\
$(BIN_OBJ_DIR)/Trim.o	\
$(BIN_OBJ_DIR)/Utility.o	\
$(BIN_OBJ_DIR)/wildcards.o	\
$(BIN_OBJ_DIR)/AtomNameVisitor.o	\
$(BIN_OBJ_DIR)/AtomVisitor.o	\
$(BIN_OBJ_DIR)/CompositeVisitor.o	\
$(BIN_OBJ_DIR)/LipidTransVisitor.o	\
$(BIN_OBJ_DIR)/OtherVisitor.o	\
$(BIN_OBJ_DIR)/ReplacementVisitor.o	\
$(BIN_OBJ_DIR)/RigidBodyVisitor.o	\
$(BIN_OBJ_DIR)/ZconsVisitor.o	\
$(BIN_OBJ_DIR)/RNEMDParameters.o	\
$(BIN_OBJ_DIR)/Icosahedron.o	\
$(BIN_OBJ_DIR)/Cuboctahedron.o	\
$(BIN_OBJ_DIR)/Decahedron.o

OPENMD_PARALLEL_OBJS =	\
$(BIN_OBJ_DIR)/CharBuffer.o	\
$(BIN_OBJ_DIR)/CharScanner.o	\
$(BIN_OBJ_DIR)/InputBuffer.o	\
$(BIN_OBJ_DIR)/TokenBuffer.o	\
$(BIN_OBJ_DIR)/MDLexer.o	\
$(BIN_OBJ_DIR)/MDParser.o	\
$(BIN_OBJ_DIR)/MDTreeParser.o	\
$(BIN_OBJ_DIR)/ForceManager.o	\
$(BIN_OBJ_DIR)/SimCreator.o	\
$(BIN_OBJ_DIR)/SimInfo.o	\
$(BIN_OBJ_DIR)/Thermo.o	\
$(BIN_OBJ_DIR)/ZconstraintForceManager.o	\
$(BIN_OBJ_DIR)/Rattle.o	\
$(BIN_OBJ_DIR)/Shake.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeConstraints.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeObjectiveFunction.o	\
$(BIN_OBJ_DIR)/FluctuatingChargeForces.o	\
$(BIN_OBJ_DIR)/FluctuatingChargePropagator.o	\
$(BIN_OBJ_DIR)/RNEMD.o	\
$(BIN_OBJ_DIR)/Velocitizer.o	\
$(BIN_OBJ_DIR)/ConstraintWriter.o	\
$(BIN_OBJ_DIR)/DumpReader.o	\
$(BIN_OBJ_DIR)/DumpWriter.o	\
$(BIN_OBJ_DIR)/RestReader.o	\
$(BIN_OBJ_DIR)/RestWriter.o	\
$(BIN_OBJ_DIR)/StatWriter.o	\
$(BIN_OBJ_DIR)/ZConsWriter.o	\
$(BIN_OBJ_DIR)/ifstrstream.o	\
$(BIN_OBJ_DIR)/ParallelRandNumGen.o	\
$(BIN_OBJ_DIR)/Electrostatic.o	\
$(BIN_OBJ_DIR)/ForceDecomposition.o	\
$(BIN_OBJ_DIR)/ForceMatrixDecomposition.o	\
$(BIN_OBJ_DIR)/RestraintForceManager.o	\
$(BIN_OBJ_DIR)/ThermoIntegrationForceManager.o	\
$(BIN_OBJ_DIR)/DistanceFinder.o	\
$(BIN_OBJ_DIR)/SelectionManager.o	\
$(BIN_OBJ_DIR)/SelectionSet.o	\
$(BIN_OBJ_DIR)/ProgressBar.o	\
$(BIN_OBJ_DIR)/simError.o	\
$(BIN_OBJ_DIR)/OpenMDBitSet.o	\
$(BIN_OBJ_DIR)/Problem.o
#$(BIN_OBJ_DIR)/LangevinHullForceManager.o	\

OPENMD_QHULL_PARALLEL_OBJS =	\
$(BIN_OBJ_DIR)/ConvexHull.o	\
$(BIN_OBJ_DIR)/AlphaHull.o
#$(BIN_OBJ_DIR)/LangevinHullForceManager.o	\

ADAPTER_OBJS =	\
$(BIN_OBJ_DIR)/adapters.o

JS_WRAPPER_OBJS = \
$(BIN_OBJ_DIR)/jsWrapper.o

WRAPPER_JS_FILES =	\
$(ADAPTER_SRC_DIR)/pre.js

ifdef NATIVE
OMD_RUNNER_OBJS =	\
$(BIN_OBJ_DIR)/omdRunner.o
TEST_RUNNER_OBJS =	\
$(BIN_OBJ_DIR)/omTestDataBuilder.o
endif

ALL_OBJS = $(OPENMD_OBJS) $(OPENMD_PARALLEL_OBJS) $(ADAPTER_OBJS)

ifdef EMCC
ALL_OBJS += $(JS_WRAPPER_OBJS) 
# $(WRAPPER_JS_FILES)
endif
#  $(OPENMD_QHULL_PARALLEL_OBJS)

all:createDirs exeTasks

createDirs:
	-mkdir ../bin
	-mkdir ../bin/obj_native	
	-mkdir ../bin/obj_emcc	
	
ifdef NATIVE
exeTasks: $(EXE_OMD_RUNNER_PATHNAME) $(EXE_TEST_RUNNER_PATHNAME)
else	
exeTasks: $(EXE_PATHNAME)
#exeTasks: $(EXE_OMD_RUNNER_PATHNAME)
endif

$(EXE_PATHNAME) : $(ALL_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_PATHNAME) $(ALL_OBJS) -lm $(OPTIMIZE)
$(EXE_OMD_RUNNER_PATHNAME) : $(ALL_OBJS) $(OMD_RUNNER_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_OMD_RUNNER_PATHNAME) $(ALL_OBJS) $(OMD_RUNNER_OBJS) -lm $(OPTIMIZE)
$(EXE_TEST_RUNNER_PATHNAME) : $(ALL_OBJS) $(TEST_RUNNER_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_TEST_RUNNER_PATHNAME) $(ALL_OBJS) $(TEST_RUNNER_OBJS) -lm $(OPTIMIZE)	

$(BIN_OBJ_DIR)/%.o: $(ADAPTER_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(BENCHMARK_CPP_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(TESTER_CPP_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@	

$(BIN_OBJ_DIR)/%.o: $(OPENMD_BIN_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/antlr/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/brains/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/constraints/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/hydrodynamics/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/integrators/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/flucq/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/io/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/lattice/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/math/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/mdParser/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/optimization/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/nonbonded/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/parallel/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/primitives/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/perturbations/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/restraints/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/selection/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/types/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/utils/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/visitors/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/rnemd/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OPENMD_SRC_DIR)/clusters/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
	
.PHONY:clean
clean :
	-rm $(BIN_OBJ_DIR)/*.o
	-rm $(BIN_3RD_OBJ_DIR)/*.o
