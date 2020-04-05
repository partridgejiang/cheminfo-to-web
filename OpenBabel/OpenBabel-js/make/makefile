# The compiler
ifndef NATIVE
	C_COMPILER = emcc
	CPP_COMPILER = emcc
	LINKER = emcc -s
	EXE_EXT = .js
	
	ifndef NO_MODULARIZE
		EMCC_MODULARIZE_OPTION = -s MODULARIZE=1 -s EXPORT_NAME="'OpenBabelModule'"
	endif
	
	EMCC_PRE_JS_OPTION = --pre-js $(SRC_DIR)/pre.js
	
	EMCC_MEM_FILE_OPTION = --memory-init-file 0
	EMCC_MISC_OPTION = $(EMCC_MODULARIZE_OPTION) -s ASSERTIONS=0
	#EMCC_MISC_OPTION = --separate-asm
	LINKER_OPTIONS = --bind
else
	C_COMPILER = gcc
	CPP_COMPILER = g++
	LINKER = g++ -s
	EXE_EXT = 
endif
EXE_NAME = openbabel
OPTIMIZE = -O3
FORMAT_JSON = 1;
#LINKER_OPTIONS = -static-libgcc

# === source directories ===
ifndef OB_BASE_DIR
	OB_BASE_DIR = ../../OpenBabel-src/src
endif
ifndef OB_DATA_DIR
	OB_DATA_DIR = $(OB_BASE_DIR)/data
endif
ifndef OB_SRC_DIR
	OB_SRC_DIR = $(OB_BASE_DIR)/src
endif
ifndef OB_FORMAT_SRC_DIR
	OB_FORMAT_SRC_DIR = $(OB_SRC_DIR)/formats
endif
ifndef OB_FORMAT_INCHI_DIR
	OB_FORMAT_INCHI_DIR = $(OB_FORMAT_SRC_DIR)/libinchi
endif
ifndef OB_FORMAT_JSON_DIR
	OB_FORMAT_JSON_DIR = $(OB_FORMAT_SRC_DIR)/json
endif
ifndef OB_FORCEFIELD_SRC_DIR
	OB_FORCEFIELD_SRC_DIR = $(OB_SRC_DIR)/forcefields
endif
ifndef OB_INCLUDE_DIR
	OB_INCLUDE_DIR = $(OB_BASE_DIR)/include
endif
ifndef OB_CONFIG_INCLUDE_DIR
	OB_CONFIG_INCLUDE_DIR = ../../OpenBabel-src/build-emcc/include
endif
ifndef OB_FORMAT_INCHI_INCLUDE_DIR
	OB_FORMAT_INCHI_INCLUDE_DIR = $(OB_INCLUDE_DIR)/inchi
endif
ifndef OB_FORMAT_JSON_INCLUDE_DIR
	OB_FORMAT_JSON_INCLUDE_DIR = $(OB_INCLUDE_DIR)/json
endif
ifndef SRC_DIR
	SRC_DIR = ../src
endif
ifndef BINDER_SRC_DIR
	BINDER_SRC_DIR = $(SRC_DIR)/embind
endif

# === output directories ===
ifndef BIN_DIR
  BIN_DIR = ../bin
endif
ifndef BIN_OBJ_DIR
  ifdef NATIVE
    BIN_OBJ_DIR = $(BIN_DIR)/obj_native
  else
    BIN_OBJ_DIR = $(BIN_DIR)/obj_emcc
  endif
endif

# === Compile target ===
EXE_PATHNAME = $(BIN_DIR)/$(EXE_NAME)$(EXE_EXT)

P_INCLUDE = -I$(SRC_DIR) -I$(BINDER_SRC_DIR) -I$(OB_INCLUDE_DIR) -I$(OB_CONFIG_INCLUDE_DIR) -I$(OB_SRC_DIR) -I$(OB_FORMAT_SRC_DIR) -I$(OB_DATA_DIR)
ifdef FORMAT_INCHI
  P_INCLUDE += -I$(OB_FORMAT_INCHI_INCLUDE_DIR)
endif
ifndef FORMAT_JSON
  P_INCLUDE += -I$(OB_FORMAT_JSON_INCLUDE_DIR)
endif
CPP_COMPILER_OPTIONS = $(P_INCLUDE) $(OPTIMIZE) -UHAVE_LIBZ -c -std=c++11
C_COMPILER_OPTIONS = $(P_INCLUDE) $(OPTIMIZE) -UHAVE_LIBZ -c

# === OpenBabel src files ===
EMCC_EMBED_FILE_MARK = --embed-file
OB_DATA_SUBDIR = data/

OB_DATA_FILES = \
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/bondtyp.txt@$(OB_DATA_SUBDIR)bondtyp.txt	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/ringtyp.txt@$(OB_DATA_SUBDIR)ringtyp.txt	\
	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/aromatic.txt@$(OB_DATA_SUBDIR)aromatic.txt	\
	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/atomtyp.txt@$(OB_DATA_SUBDIR)atomtyp.txt	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/element.txt@$(OB_DATA_SUBDIR)element.txt	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/types.txt@$(OB_DATA_SUBDIR)types.txt	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/phmodel.txt@$(OB_DATA_SUBDIR)phmodel.txt
#$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/aromatic.txt@$(OB_DATA_SUBDIR)aromatic.txt	\
#$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/isotope.txt@$(OB_DATA_SUBDIR)isotope.txt	\
#$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/isotope-small.txt@$(OB_DATA_SUBDIR)isotope-small.txt	\
#$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/fragments.txt@$(OB_DATA_SUBDIR)fragments.txt	\
#$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/resdata.txt@$(OB_DATA_SUBDIR)resdata.txt	\
#$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/superatom.txt@$(OB_DATA_SUBDIR)superatom.txt

# Now MMFF94/gaff/ghemical/UFF forcefield data file is included
OB_FF_DATA_FILES = \
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffang.par@$(OB_DATA_SUBDIR)mmffang.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffbndk.par@$(OB_DATA_SUBDIR)mmffbndk.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffbond.par@$(OB_DATA_SUBDIR)mmffbond.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffstbn.par@$(OB_DATA_SUBDIR)mmffstbn.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffdfsb.par@$(OB_DATA_SUBDIR)mmffdfsb.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffoop.par@$(OB_DATA_SUBDIR)mmffoop.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmfftor.par@$(OB_DATA_SUBDIR)mmfftor.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffvdw.par@$(OB_DATA_SUBDIR)mmffvdw.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffchg.par@$(OB_DATA_SUBDIR)mmffchg.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffpbci.par@$(OB_DATA_SUBDIR)mmffpbci.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffprop.par@$(OB_DATA_SUBDIR)mmffprop.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffdef.par@$(OB_DATA_SUBDIR)mmffdef.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmff94.ff@$(OB_DATA_SUBDIR)mmff94.ff	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmff94s.ff@$(OB_DATA_SUBDIR)mmff94s.ff	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffs_oop.par@$(OB_DATA_SUBDIR)mmffs_oop.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mmffs_tor.par@$(OB_DATA_SUBDIR)mmffs_tor.par	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/gaff.prm@$(OB_DATA_SUBDIR)gaff.prm	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/gaff.prm@$(OB_DATA_SUBDIR)gaff.dat	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/UFF.prm@$(OB_DATA_SUBDIR)UFF.prm	\
$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/ghemical.prm@$(OB_DATA_SUBDIR)ghemical.prm
#$(EMCC_EMBED_FILE_MARK) $(OB_DATA_DIR)/mm2.prm@$(OB_DATA_SUBDIR)mm2.prm


ifndef NATIVE
  EMCC_EMBED_FILE_OPTION = $(OB_FF_DATA_FILES) $(OB_DATA_FILES) # FF data files currently is bypass to reduce file size, normal data files usally can fall back to .h replacements
endif

OB_BASE_SRCS =	\
$(OB_SRC_DIR)/alias.cpp	\
$(OB_SRC_DIR)/atom.cpp	\
$(OB_SRC_DIR)/base.cpp	\
$(OB_SRC_DIR)/bitvec.cpp	\
$(OB_SRC_DIR)/bond.cpp	\
$(OB_SRC_DIR)/bondtyper.cpp	\
$(OB_SRC_DIR)/builder.cpp	\
$(OB_SRC_DIR)/canon.cpp	\
$(OB_SRC_DIR)/chains.cpp	\
$(OB_SRC_DIR)/chargemodel.cpp	\
$(OB_SRC_DIR)/charges	\
$(OB_SRC_DIR)/chiral.cpp	\
$(OB_SRC_DIR)/data.cpp	\
$(OB_SRC_DIR)/descriptor.cpp	\
$(OB_SRC_DIR)/fingerprint.cpp	\
$(OB_SRC_DIR)/forcefield.cpp	\
$(OB_SRC_DIR)/format.cpp	\
$(OB_SRC_DIR)/generic.cpp	\
$(OB_SRC_DIR)/graphsym.cpp	\
$(OB_SRC_DIR)/grid.cpp	\
$(OB_SRC_DIR)/griddata.cpp	\
$(OB_SRC_DIR)/isomorphism.cpp	\
$(OB_SRC_DIR)/kekulize.cpp	\
$(OB_SRC_DIR)/locale.cpp	\
$(OB_SRC_DIR)/matrix.cpp	\
$(OB_SRC_DIR)/mcdlutil.cpp	\
$(OB_SRC_DIR)/memcpy.c	\
$(OB_SRC_DIR)/molchrg.cpp	\
$(OB_SRC_DIR)/mol.cpp	\
$(OB_SRC_DIR)/obconversion.cpp	\
$(OB_SRC_DIR)/oberror.cpp	\
$(OB_SRC_DIR)/obiter.cpp	\
$(OB_SRC_DIR)/obmolecformat.cpp	\
$(OB_SRC_DIR)/obutil.cpp	\
$(OB_SRC_DIR)/op.cpp	\
$(OB_SRC_DIR)/parsmart.cpp	\
$(OB_SRC_DIR)/patty.cpp	\
$(OB_SRC_DIR)/phmodel.cpp	\
$(OB_SRC_DIR)/pointgroup.cpp	\
$(OB_SRC_DIR)/query.cpp	\
$(OB_SRC_DIR)/rand.cpp	\
$(OB_SRC_DIR)/residue.cpp	\
$(OB_SRC_DIR)/ring.cpp	\
$(OB_SRC_DIR)/rotamer.cpp	\
$(OB_SRC_DIR)/rotor.cpp	\
$(OB_SRC_DIR)/spectrophore.cpp	\
$(OB_SRC_DIR)/tautomer.cpp	\
$(OB_SRC_DIR)/tokenst.cpp	\
$(OB_SRC_DIR)/transform.cpp	\
$(OB_SRC_DIR)/typer.cpp	\
$(OB_SRC_DIR)/dlhandler_unix.cpp	\
$(OB_SRC_DIR)/stereo/cistrans.cpp	\
$(OB_SRC_DIR)/stereo/facade.cpp	\
$(OB_SRC_DIR)/stereo/perception.cpp	\
$(OB_SRC_DIR)/stereo/squareplanar.cpp	\
$(OB_SRC_DIR)/stereo/stereo.cpp	\
$(OB_SRC_DIR)/stereo/tetrahedral.cpp	\
$(OB_SRC_DIR)/stereo/tetranonplanar.cpp	\
$(OB_SRC_DIR)/stereo/tetraplanar.cpp	\
$(OB_SRC_DIR)/math/matrix3x3.cpp	\
$(OB_SRC_DIR)/math/spacegroup.cpp	\
$(OB_SRC_DIR)/math/transform3d.cpp	\
$(OB_SRC_DIR)/math/vector3.cpp
#$(OB_SRC_DIR)/conformersearch.cpp	\	# is this file needed?
#$(OB_SRC_DIR)/confsearch.cpp	\	# is this file needed?
#$(OB_SRC_DIR)/data_utilities.cpp	\	# is this file needed?
#$(OB_SRC_DIR)/distgeom.cpp	\	#is this file needed?
#$(OB_SRC_DIR)/doxygen_pages.cpp	\	# is needed?
#$(OB_SRC_DIR)/plugin.cpp	\	# is needed?
#$(OB_SRC_DIR)/RDKitConv.cpp	\	# is needed?
#$(OB_SRC_DIR)/dlhandler_win32.cpp	\
#$(OB_SRC_DIR)/strncasecmp.c	\
#snprintf.c
#snprintf.h
#zipstream.h	
#zipstreamimpl.h

OB_FORMAT_SRCS =	\
$(OB_FORMAT_SRC_DIR)/abinitformat.cpp	\
$(OB_FORMAT_SRC_DIR)/acesformat.cpp	\
$(OB_FORMAT_SRC_DIR)/acrformat.cpp	\
$(OB_FORMAT_SRC_DIR)/adfformat.cpp	\
$(OB_FORMAT_SRC_DIR)/alchemyformat.cpp	\
$(OB_FORMAT_SRC_DIR)/amberformat.cpp	\
$(OB_FORMAT_SRC_DIR)/aoforceformat.cpp	\
$(OB_FORMAT_SRC_DIR)/balstformat.cpp	\
$(OB_FORMAT_SRC_DIR)/bgfformat.cpp	\
$(OB_FORMAT_SRC_DIR)/boxformat.cpp	\
$(OB_FORMAT_SRC_DIR)/cacaoformat.cpp	\
$(OB_FORMAT_SRC_DIR)/cacheformat.cpp	\
$(OB_FORMAT_SRC_DIR)/carformat.cpp	\
$(OB_FORMAT_SRC_DIR)/castepformat.cpp	\
$(OB_FORMAT_SRC_DIR)/cccformat.cpp	\
$(OB_FORMAT_SRC_DIR)/chem3dformat.cpp	\
$(OB_FORMAT_SRC_DIR)/chemdrawcdx.cpp	\
$(OB_FORMAT_SRC_DIR)/chemdrawct.cpp	\
$(OB_FORMAT_SRC_DIR)/chemkinformat.cpp	\
$(OB_FORMAT_SRC_DIR)/chemtoolformat.cpp	\
$(OB_FORMAT_SRC_DIR)/cifformat.cpp	\
$(OB_FORMAT_SRC_DIR)/copyformat.cpp	\
$(OB_FORMAT_SRC_DIR)/crkformat.cpp	\
$(OB_FORMAT_SRC_DIR)/crystal09format.cpp	\
$(OB_FORMAT_SRC_DIR)/CSRformat.cpp	\
$(OB_FORMAT_SRC_DIR)/cssrformat.cpp	\
$(OB_FORMAT_SRC_DIR)/daltonformat.cpp	\
$(OB_FORMAT_SRC_DIR)/dlpolyformat.cpp	\
$(OB_FORMAT_SRC_DIR)/dmolformat.cpp	\
$(OB_FORMAT_SRC_DIR)/exampleformat.cpp	\
$(OB_FORMAT_SRC_DIR)/exyzformat.cpp	\
$(OB_FORMAT_SRC_DIR)/fastaformat.cpp	\
$(OB_FORMAT_SRC_DIR)/fastsearchformat.cpp	\
$(OB_FORMAT_SRC_DIR)/fchkformat.cpp	\
$(OB_FORMAT_SRC_DIR)/featformat.cpp	\
$(OB_FORMAT_SRC_DIR)/fhformat.cpp	\
$(OB_FORMAT_SRC_DIR)/fhiaimsformat.cpp	\
$(OB_FORMAT_SRC_DIR)/fingerprintformat.cpp	\
$(OB_FORMAT_SRC_DIR)/fpsformat.cpp	\
$(OB_FORMAT_SRC_DIR)/freefracformat.cpp	\
$(OB_FORMAT_SRC_DIR)/gamessformat.cpp	\
$(OB_FORMAT_SRC_DIR)/gamessukformat.cpp	\
$(OB_FORMAT_SRC_DIR)/gausscubeformat.cpp	\
$(OB_FORMAT_SRC_DIR)/gaussformat.cpp	\
$(OB_FORMAT_SRC_DIR)/gausszmatformat.cpp	\
$(OB_FORMAT_SRC_DIR)/genbankformat.cpp	\
$(OB_FORMAT_SRC_DIR)/ghemicalformat.cpp	\
$(OB_FORMAT_SRC_DIR)/groformat.cpp	\
$(OB_FORMAT_SRC_DIR)/gromos96format.cpp	\
$(OB_FORMAT_SRC_DIR)/gulpformat.cpp	\
$(OB_FORMAT_SRC_DIR)/hinformat.cpp	\
$(OB_FORMAT_SRC_DIR)/jaguarformat.cpp	\
$(OB_FORMAT_SRC_DIR)/lmpdatformat.cpp	\
$(OB_FORMAT_SRC_DIR)/lpmdformat.cpp	\
$(OB_FORMAT_SRC_DIR)/MCDLformat.cpp	\
$(OB_FORMAT_SRC_DIR)/mdffformat.cpp	\
$(OB_FORMAT_SRC_DIR)/mdlformat.cpp	\
$(OB_FORMAT_SRC_DIR)/mmcifformat.cpp	\
$(OB_FORMAT_SRC_DIR)/mmodformat.cpp	\
$(OB_FORMAT_SRC_DIR)/MNAformat.cpp	\
$(OB_FORMAT_SRC_DIR)/mol2format.cpp	\
$(OB_FORMAT_SRC_DIR)/moldenformat.cpp	\
$(OB_FORMAT_SRC_DIR)/molproformat.cpp	\
$(OB_FORMAT_SRC_DIR)/molreport.cpp	\
$(OB_FORMAT_SRC_DIR)/mopacformat.cpp	\
$(OB_FORMAT_SRC_DIR)/mpdformat.cpp	\
$(OB_FORMAT_SRC_DIR)/mpqcformat.cpp	\
$(OB_FORMAT_SRC_DIR)/msiformat.cpp	\
$(OB_FORMAT_SRC_DIR)/msmsformat.cpp	\
$(OB_FORMAT_SRC_DIR)/nulformat.cpp	\
$(OB_FORMAT_SRC_DIR)/nwchemformat.cpp	\
$(OB_FORMAT_SRC_DIR)/opendxformat.cpp	\
$(OB_FORMAT_SRC_DIR)/orcaformat.cpp	\
$(OB_FORMAT_SRC_DIR)/outformat.cpp	\
$(OB_FORMAT_SRC_DIR)/pcmodelformat.cpp	\
$(OB_FORMAT_SRC_DIR)/pdbformat.cpp	\
$(OB_FORMAT_SRC_DIR)/pdbqtformat.cpp	\
$(OB_FORMAT_SRC_DIR)/pointcloudformat.cpp	\
$(OB_FORMAT_SRC_DIR)/posformat.cpp	\
$(OB_FORMAT_SRC_DIR)/povrayformat.cpp	\
$(OB_FORMAT_SRC_DIR)/pqrformat.cpp	\
$(OB_FORMAT_SRC_DIR)/PQSformat.cpp	\
$(OB_FORMAT_SRC_DIR)/pwscfformat.cpp	\
$(OB_FORMAT_SRC_DIR)/qchemformat.cpp	\
$(OB_FORMAT_SRC_DIR)/reportformat.cpp	\
$(OB_FORMAT_SRC_DIR)/rsmiformat.cpp	\
$(OB_FORMAT_SRC_DIR)/rxnformat.cpp	\
$(OB_FORMAT_SRC_DIR)/shelxformat.cpp	\
$(OB_FORMAT_SRC_DIR)/siestaformat.cpp	\
$(OB_FORMAT_SRC_DIR)/smilesformat.cpp	\
$(OB_FORMAT_SRC_DIR)/smileyformat.cpp	\
$(OB_FORMAT_SRC_DIR)/textformat.cpp	\
$(OB_FORMAT_SRC_DIR)/thermoformat.cpp	\
$(OB_FORMAT_SRC_DIR)/tinkerformat.cpp	\
$(OB_FORMAT_SRC_DIR)/titleformat.cpp	\
$(OB_FORMAT_SRC_DIR)/turbomoleformat.cpp	\
$(OB_FORMAT_SRC_DIR)/unichemformat.cpp	\
$(OB_FORMAT_SRC_DIR)/vaspformat.cpp	\
$(OB_FORMAT_SRC_DIR)/viewmolformat.cpp	\
$(OB_FORMAT_SRC_DIR)/xedformat.cpp	\
$(OB_FORMAT_SRC_DIR)/xsfformat.cpp	\
$(OB_FORMAT_SRC_DIR)/xyzformat.cpp	\
$(OB_FORMAT_SRC_DIR)/yasaraformat.cpp	\
$(OB_FORMAT_SRC_DIR)/zindoformat.cpp	\
$(OB_FORMAT_SRC_DIR)/inchiformat.cpp	\
$(OB_FORMAT_SRC_DIR)/getinchi.cpp
#$(OB_FORMAT_SRC_DIR)/confabreport.cpp	\
#$(OB_FORMAT_SRC_DIR)/smiley.h
#$(OB_FORMAT_SRC_DIR)/png2format.cpp	\
#$(OB_FORMAT_SRC_DIR)/pngformat.cpp	\
#$(OB_FORMAT_SRC_DIR)/xtcformat.cpp	\
#$(OB_FORMAT_SRC_DIR)/asciiformat.cpp	\
#$(OB_FORMAT_SRC_DIR)/painterformat.cpp	\
#$(OB_FORMAT_SRC_DIR)/svgformat.cpp	\
#$(OB_FORMAT_SRC_DIR)/stlformat.cpp	\
#$(OB_FORMAT_SRC_DIR)/APIInterface.cpp	\
#ArrayList.c
#ArrayList.h

ifdef FORMAT_JSON
OB_FORMAT_JSON_SRCS =	\
$(OB_FORMAT_JSON_DIR)/jsoncpp.cpp	\
$(OB_FORMAT_JSON_DIR)/customwriter.cpp	\
$(OB_FORMAT_JSON_DIR)/chemdoodlejsonformat.cpp	\
$(OB_FORMAT_JSON_DIR)/pubchemjsonformat.cpp
endif

ifdef FORMAT_INCHI
OB_FORMAT_INCHI_SRCS =	\
$(OB_FORMAT_INCHI_DIR)/ichi_bns.c	\
$(OB_FORMAT_INCHI_DIR)/ichican2.c	\
$(OB_FORMAT_INCHI_DIR)/ichicano.c	\
$(OB_FORMAT_INCHI_DIR)/ichicans.c	\
$(OB_FORMAT_INCHI_DIR)/ichi_io.c	\
$(OB_FORMAT_INCHI_DIR)/ichiisot.c	\
$(OB_FORMAT_INCHI_DIR)/ichilnct.c	\
$(OB_FORMAT_INCHI_DIR)/ichimak2.c	\
$(OB_FORMAT_INCHI_DIR)/ichimake.c	\
$(OB_FORMAT_INCHI_DIR)/ichimap1.c	\
$(OB_FORMAT_INCHI_DIR)/ichimap2.c	\
$(OB_FORMAT_INCHI_DIR)/ichimap4.c	\
$(OB_FORMAT_INCHI_DIR)/ichinorm.c	\
$(OB_FORMAT_INCHI_DIR)/ichiparm.c	\
$(OB_FORMAT_INCHI_DIR)/ichiprt1.c	\
$(OB_FORMAT_INCHI_DIR)/ichiprt2.c	\
$(OB_FORMAT_INCHI_DIR)/ichiprt3.c	\
$(OB_FORMAT_INCHI_DIR)/ichiqueu.c	\
$(OB_FORMAT_INCHI_DIR)/ichiread.c	\
$(OB_FORMAT_INCHI_DIR)/ichiring.c	\
$(OB_FORMAT_INCHI_DIR)/ichirvr1.c	\
$(OB_FORMAT_INCHI_DIR)/ichirvr2.c	\
$(OB_FORMAT_INCHI_DIR)/ichirvr3.c	\
$(OB_FORMAT_INCHI_DIR)/ichirvr4.c	\
$(OB_FORMAT_INCHI_DIR)/ichirvr5.c	\
$(OB_FORMAT_INCHI_DIR)/ichirvr6.c	\
$(OB_FORMAT_INCHI_DIR)/ichirvr7.c	\
$(OB_FORMAT_INCHI_DIR)/ichisort.c	\
$(OB_FORMAT_INCHI_DIR)/ichister.c	\
$(OB_FORMAT_INCHI_DIR)/ichitaut.c	\
$(OB_FORMAT_INCHI_DIR)/ikey_base26.c	\
$(OB_FORMAT_INCHI_DIR)/ikey_dll.c	\
$(OB_FORMAT_INCHI_DIR)/inchi_dll_a2.c	\
$(OB_FORMAT_INCHI_DIR)/inchi_dll_a.c	\
$(OB_FORMAT_INCHI_DIR)/inchi_dll.c	\
$(OB_FORMAT_INCHI_DIR)/inchi_dll_main.c	\
$(OB_FORMAT_INCHI_DIR)/runichi.c	\
$(OB_FORMAT_INCHI_DIR)/sha2.c	\
$(OB_FORMAT_INCHI_DIR)/strutil.c	\
$(OB_FORMAT_INCHI_DIR)/util.c
endif

OB_FORCEFIELD_SRCS =	\
$(OB_FORCEFIELDS_SRC_DIR)/forcefieldgaff.cpp	\
$(OB_FORCEFIELDS_SRC_DIR)/forcefieldghemical.cpp	\
$(OB_FORCEFIELDS_SRC_DIR)/forcefieldmm2.cpp	\
$(OB_FORCEFIELDS_SRC_DIR)/forcefieldmmff94.cpp	\
$(OB_FORCEFIELDS_SRC_DIR)/forcefielduff.cpp

BINDER_SRCS =	\
$(BINDER_SRC_DIR)/MyEmbinding.cpp	\
$(BINDER_SRC_DIR)/ObWrapper.cpp

MAIN_SRCS =	\
$(SRC_DIR)/io_runner.cpp

# === object files === /
OB_BASE_OBJS =	\
$(BIN_OBJ_DIR)/alias.o	\
$(BIN_OBJ_DIR)/atom.o	\
$(BIN_OBJ_DIR)/base.o	\
$(BIN_OBJ_DIR)/bitvec.o	\
$(BIN_OBJ_DIR)/bond.o	\
$(BIN_OBJ_DIR)/bondtyper.o	\
$(BIN_OBJ_DIR)/builder.o	\
$(BIN_OBJ_DIR)/canon.o	\
$(BIN_OBJ_DIR)/chains.o	\
$(BIN_OBJ_DIR)/chargemodel.o	\
$(BIN_OBJ_DIR)/chiral.o	\
$(BIN_OBJ_DIR)/data.o	\
$(BIN_OBJ_DIR)/descriptor.o	\
$(BIN_OBJ_DIR)/fingerprint.o	\
$(BIN_OBJ_DIR)/forcefield.o	\
$(BIN_OBJ_DIR)/format.o	\
$(BIN_OBJ_DIR)/generic.o	\
$(BIN_OBJ_DIR)/graphsym.o	\
$(BIN_OBJ_DIR)/grid.o	\
$(BIN_OBJ_DIR)/griddata.o	\
$(BIN_OBJ_DIR)/isomorphism.o	\
$(BIN_OBJ_DIR)/kekulize.o	\
$(BIN_OBJ_DIR)/locale.o	\
$(BIN_OBJ_DIR)/matrix.o	\
$(BIN_OBJ_DIR)/mcdlutil.o	\
$(BIN_OBJ_DIR)/memcpy.o	\
$(BIN_OBJ_DIR)/molchrg.o	\
$(BIN_OBJ_DIR)/mol.o	\
$(BIN_OBJ_DIR)/obconversion.o	\
$(BIN_OBJ_DIR)/oberror.o	\
$(BIN_OBJ_DIR)/obiter.o	\
$(BIN_OBJ_DIR)/obmolecformat.o	\
$(BIN_OBJ_DIR)/obutil.o	\
$(BIN_OBJ_DIR)/op.o	\
$(BIN_OBJ_DIR)/parsmart.o	\
$(BIN_OBJ_DIR)/patty.o	\
$(BIN_OBJ_DIR)/phmodel.o	\
$(BIN_OBJ_DIR)/pointgroup.o	\
$(BIN_OBJ_DIR)/query.o	\
$(BIN_OBJ_DIR)/rand.o	\
$(BIN_OBJ_DIR)/residue.o	\
$(BIN_OBJ_DIR)/ring.o	\
$(BIN_OBJ_DIR)/rotamer.o	\
$(BIN_OBJ_DIR)/rotor.o	\
$(BIN_OBJ_DIR)/spectrophore.o	\
$(BIN_OBJ_DIR)/tautomer.o	\
$(BIN_OBJ_DIR)/tokenst.o	\
$(BIN_OBJ_DIR)/transform.o	\
$(BIN_OBJ_DIR)/typer.o	\
$(BIN_OBJ_DIR)/dlhandler_unix.o	\
$(BIN_OBJ_DIR)/cistrans.o	\
$(BIN_OBJ_DIR)/facade.o	\
$(BIN_OBJ_DIR)/perception.o	\
$(BIN_OBJ_DIR)/squareplanar.o	\
$(BIN_OBJ_DIR)/stereo.o	\
$(BIN_OBJ_DIR)/tetrahedral.o	\
$(BIN_OBJ_DIR)/tetranonplanar.o	\
$(BIN_OBJ_DIR)/tetraplanar.o	\
$(BIN_OBJ_DIR)/matrix3x3.o	\
$(BIN_OBJ_DIR)/spacegroup.o	\
$(BIN_OBJ_DIR)/transform3d.o	\
$(BIN_OBJ_DIR)/vector3.o
#$(BIN_OBJ_DIR)/conformersearch.o	\	# is this file needed?
#$(BIN_OBJ_DIR)/confsearch.o	\	# is this file needed?
#$(BIN_OBJ_DIR)/data_utilities.o	\	# is this file needed?
#$(BIN_OBJ_DIR)/distgeom.o	\	#is this file needed?
#$(BIN_OBJ_DIR)/doxygen_pages.o	\	# is needed?
#$(BIN_OBJ_DIR)/plugin.o	\	# is needed?
#$(BIN_OBJ_DIR)/RDKitConv.o	\	# is needed?
#$(BIN_OBJ_DIR)/dlhandler_win32.o	\
#$(BIN_OBJ_DIR)/strncasecmp.o	\
#snprintf.c
#snprintf.h
#zipstream.h	
#zipstreamimpl.h

ifndef NATIVE
OB_PLUGIN_OBJS =	\
$(BIN_OBJ_DIR)/plugin.o
endif

OB_FORMAT_OBJS =	\
$(BIN_OBJ_DIR)/abinitformat.o	\
$(BIN_OBJ_DIR)/acesformat.o	\
$(BIN_OBJ_DIR)/acrformat.o	\
$(BIN_OBJ_DIR)/adfformat.o	\
$(BIN_OBJ_DIR)/alchemyformat.o	\
$(BIN_OBJ_DIR)/amberformat.o	\
$(BIN_OBJ_DIR)/aoforceformat.o	\
$(BIN_OBJ_DIR)/balstformat.o	\
$(BIN_OBJ_DIR)/bgfformat.o	\
$(BIN_OBJ_DIR)/boxformat.o	\
$(BIN_OBJ_DIR)/cacaoformat.o	\
$(BIN_OBJ_DIR)/cacheformat.o	\
$(BIN_OBJ_DIR)/carformat.o	\
$(BIN_OBJ_DIR)/castepformat.o	\
$(BIN_OBJ_DIR)/cccformat.o	\
$(BIN_OBJ_DIR)/chem3dformat.o	\
$(BIN_OBJ_DIR)/chemdrawcdx.o	\
$(BIN_OBJ_DIR)/chemdrawct.o	\
$(BIN_OBJ_DIR)/chemkinformat.o	\
$(BIN_OBJ_DIR)/chemtoolformat.o	\
$(BIN_OBJ_DIR)/cifformat.o	\
$(BIN_OBJ_DIR)/copyformat.o	\
$(BIN_OBJ_DIR)/crkformat.o	\
$(BIN_OBJ_DIR)/crystal09format.o	\
$(BIN_OBJ_DIR)/CSRformat.o	\
$(BIN_OBJ_DIR)/cssrformat.o	\
$(BIN_OBJ_DIR)/daltonformat.o	\
$(BIN_OBJ_DIR)/dlpolyformat.o	\
$(BIN_OBJ_DIR)/dmolformat.o	\
$(BIN_OBJ_DIR)/exampleformat.o	\
$(BIN_OBJ_DIR)/exyzformat.o	\
$(BIN_OBJ_DIR)/fastaformat.o	\
$(BIN_OBJ_DIR)/fastsearchformat.o	\
$(BIN_OBJ_DIR)/fchkformat.o	\
$(BIN_OBJ_DIR)/featformat.o	\
$(BIN_OBJ_DIR)/fhformat.o	\
$(BIN_OBJ_DIR)/fhiaimsformat.o	\
$(BIN_OBJ_DIR)/fingerprintformat.o	\
$(BIN_OBJ_DIR)/freefracformat.o	\
$(BIN_OBJ_DIR)/gamessformat.o	\
$(BIN_OBJ_DIR)/gamessukformat.o	\
$(BIN_OBJ_DIR)/gausscubeformat.o	\
$(BIN_OBJ_DIR)/gaussformat.o	\
$(BIN_OBJ_DIR)/gausszmatformat.o	\
$(BIN_OBJ_DIR)/genbankformat.o	\
$(BIN_OBJ_DIR)/ghemicalformat.o	\
$(BIN_OBJ_DIR)/groformat.o	\
$(BIN_OBJ_DIR)/gromos96format.o	\
$(BIN_OBJ_DIR)/gulpformat.o	\
$(BIN_OBJ_DIR)/hinformat.o	\
$(BIN_OBJ_DIR)/jaguarformat.o	\
$(BIN_OBJ_DIR)/lmpdatformat.o	\
$(BIN_OBJ_DIR)/lpmdformat.o	\
$(BIN_OBJ_DIR)/MCDLformat.o	\
$(BIN_OBJ_DIR)/mdffformat.o	\
$(BIN_OBJ_DIR)/mdlformat.o	\
$(BIN_OBJ_DIR)/mmcifformat.o	\
$(BIN_OBJ_DIR)/mmodformat.o	\
$(BIN_OBJ_DIR)/MNAformat.o	\
$(BIN_OBJ_DIR)/mol2format.o	\
$(BIN_OBJ_DIR)/moldenformat.o	\
$(BIN_OBJ_DIR)/molproformat.o	\
$(BIN_OBJ_DIR)/molreport.o	\
$(BIN_OBJ_DIR)/mopacformat.o	\
$(BIN_OBJ_DIR)/mpdformat.o	\
$(BIN_OBJ_DIR)/mpqcformat.o	\
$(BIN_OBJ_DIR)/msiformat.o	\
$(BIN_OBJ_DIR)/msmsformat.o	\
$(BIN_OBJ_DIR)/nulformat.o	\
$(BIN_OBJ_DIR)/nwchemformat.o	\
$(BIN_OBJ_DIR)/opendxformat.o	\
$(BIN_OBJ_DIR)/orcaformat.o	\
$(BIN_OBJ_DIR)/outformat.o	\
$(BIN_OBJ_DIR)/pcmodelformat.o	\
$(BIN_OBJ_DIR)/pdbformat.o	\
$(BIN_OBJ_DIR)/pdbqtformat.o	\
$(BIN_OBJ_DIR)/pointcloudformat.o	\
$(BIN_OBJ_DIR)/posformat.o	\
$(BIN_OBJ_DIR)/povrayformat.o	\
$(BIN_OBJ_DIR)/pqrformat.o	\
$(BIN_OBJ_DIR)/PQSformat.o	\
$(BIN_OBJ_DIR)/pwscfformat.o	\
$(BIN_OBJ_DIR)/qchemformat.o	\
$(BIN_OBJ_DIR)/reportformat.o	\
$(BIN_OBJ_DIR)/rsmiformat.o	\
$(BIN_OBJ_DIR)/rxnformat.o	\
$(BIN_OBJ_DIR)/shelxformat.o	\
$(BIN_OBJ_DIR)/siestaformat.o	\
$(BIN_OBJ_DIR)/smilesformat.o	\
$(BIN_OBJ_DIR)/smileyformat.o	\
$(BIN_OBJ_DIR)/textformat.o	\
$(BIN_OBJ_DIR)/thermoformat.o	\
$(BIN_OBJ_DIR)/thermoformat.o	\
$(BIN_OBJ_DIR)/tinkerformat.o	\
$(BIN_OBJ_DIR)/titleformat.o	\
$(BIN_OBJ_DIR)/turbomoleformat.o	\
$(BIN_OBJ_DIR)/unichemformat.o	\
$(BIN_OBJ_DIR)/vaspformat.o	\
$(BIN_OBJ_DIR)/viewmolformat.o	\
$(BIN_OBJ_DIR)/xedformat.o	\
$(BIN_OBJ_DIR)/xsfformat.o	\
$(BIN_OBJ_DIR)/xyzformat.o	\
$(BIN_OBJ_DIR)/yasaraformat.o	\
$(BIN_OBJ_DIR)/zindoformat.o

ifdef FORMAT_JSON
OB_FORMAT_OBJS +=	\
$(BIN_OBJ_DIR)/jsoncpp.o	\
$(BIN_OBJ_DIR)/customwriter.o	\
$(BIN_OBJ_DIR)/chemdoodlejsonformat.o	\
$(BIN_OBJ_DIR)/pubchemjsonformat.o
endif

ifdef FORMAT_INCHI
OB_FORMAT_OBJS +=	\
$(BIN_OBJ_DIR)/getinchi.o	\
$(BIN_OBJ_DIR)/inchiformat.o
endif

ifdef NATIVE
OB_FORMAT_OBJS +=	\
$(BIN_OBJ_DIR)/fpsformat.o	\
$(BIN_OBJ_DIR)/painterformat.o	\
$(BIN_OBJ_DIR)/svgformat.o	\
$(BIN_OBJ_DIR)/stlformat.o	\
$(BIN_OBJ_DIR)/APIInterface.o	\
$(BIN_OBJ_DIR)/xtcformat.o	\
$(BIN_OBJ_DIR)/asciiformat.o
#$(BIN_OBJ_DIR)/png2format.o	\
#$(BIN_OBJ_DIR)/pngformat.o	\
#$(BIN_OBJ_DIR)/confabreport.o	\
#ArrayList.c
#ArrayList.h
endif

ifdef FORMAT_INCHI
OB_FORMAT_INCHI_OBJS =	\
$(BIN_OBJ_DIR)/ichi_bns.o	\
$(BIN_OBJ_DIR)/ichican2.o	\
$(BIN_OBJ_DIR)/ichicano.o	\
$(BIN_OBJ_DIR)/ichicans.o	\
$(BIN_OBJ_DIR)/ichi_io.o	\
$(BIN_OBJ_DIR)/ichiisot.o	\
$(BIN_OBJ_DIR)/ichilnct.o	\
$(BIN_OBJ_DIR)/ichimak2.o	\
$(BIN_OBJ_DIR)/ichimake.o	\
$(BIN_OBJ_DIR)/ichimap1.o	\
$(BIN_OBJ_DIR)/ichimap2.o	\
$(BIN_OBJ_DIR)/ichimap4.o	\
$(BIN_OBJ_DIR)/ichinorm.o	\
$(BIN_OBJ_DIR)/ichiparm.o	\
$(BIN_OBJ_DIR)/ichiprt1.o	\
$(BIN_OBJ_DIR)/ichiprt2.o	\
$(BIN_OBJ_DIR)/ichiprt3.o	\
$(BIN_OBJ_DIR)/ichiqueu.o	\
$(BIN_OBJ_DIR)/ichiread.o	\
$(BIN_OBJ_DIR)/ichiring.o	\
$(BIN_OBJ_DIR)/ichirvr1.o	\
$(BIN_OBJ_DIR)/ichirvr2.o	\
$(BIN_OBJ_DIR)/ichirvr3.o	\
$(BIN_OBJ_DIR)/ichirvr4.o	\
$(BIN_OBJ_DIR)/ichirvr5.o	\
$(BIN_OBJ_DIR)/ichirvr6.o	\
$(BIN_OBJ_DIR)/ichirvr7.o	\
$(BIN_OBJ_DIR)/ichisort.o	\
$(BIN_OBJ_DIR)/ichister.o	\
$(BIN_OBJ_DIR)/ichitaut.o	\
$(BIN_OBJ_DIR)/ikey_base26.o	\
$(BIN_OBJ_DIR)/ikey_dll.o	\
$(BIN_OBJ_DIR)/inchi_dll_a2.o	\
$(BIN_OBJ_DIR)/inchi_dll_a.o	\
$(BIN_OBJ_DIR)/inchi_dll.o	\
$(BIN_OBJ_DIR)/inchi_dll_main.o	\
$(BIN_OBJ_DIR)/runichi.o	\
$(BIN_OBJ_DIR)/sha2.o	\
$(BIN_OBJ_DIR)/strutil.o	\
$(BIN_OBJ_DIR)/util.o
endif

OB_FORCEFIELD_OBJS =	\
$(BIN_OBJ_DIR)/forcefieldgaff.o	\
$(BIN_OBJ_DIR)/forcefieldghemical.o	\
$(BIN_OBJ_DIR)/forcefieldmm2.o	\
$(BIN_OBJ_DIR)/forcefieldmmff94.o	\
$(BIN_OBJ_DIR)/forcefielduff.o	\

ifndef NATIVE
  BINDER_OBJS =	\
  $(BIN_OBJ_DIR)/MyEmbinding.o	\
  $(BIN_OBJ_DIR)/ObWrapper.o
endif

ifdef NATIVE
  MAIN_OBJS =	\
  $(BIN_OBJ_DIR)/io_runner.o
endif

ALL_OBJS = $(OB_BASE_OBJS) $(OB_FORMAT_OBJS) $(OB_FORMAT_INCHI_OBJS) $(OB_FORCEFIELD_OBJS) $(OB_PLUGIN_OBJS) $(BINDER_OBJS) $(MAIN_OBJS)


$(EXE_PATHNAME) : $(ALL_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(EXE_PATHNAME) $(ALL_OBJS) -lm $(OPTIMIZE) $(EMCC_MEM_FILE_OPTION) $(EMCC_EMBED_FILE_OPTION) $(EMCC_MISC_OPTION) $(EMCC_PRE_JS_OPTION)
$(BIN_OBJ_DIR)/%.o: $(OB_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OB_SRC_DIR)/%.c
	$(CPP_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OB_SRC_DIR)/stereo/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OB_SRC_DIR)/math/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@	
$(BIN_OBJ_DIR)/%.o: $(OB_FORMAT_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OB_FORMAT_INCHI_DIR)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@	
$(BIN_OBJ_DIR)/%.o: $(OB_FORMAT_JSON_DIR)/%.cpp
	$(CPP_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(OB_FORCEFIELD_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(BINDER_SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/conv.o: $(SRC_DIR)/conv.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
clean:
	rm ($BIN_OBJ_DIR)/*.o

