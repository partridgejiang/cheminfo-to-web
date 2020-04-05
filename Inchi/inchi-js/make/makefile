ifdef EMCC
	ifndef C_COMPILER
		C_COMPILER   = emcc
	endif
	ifndef CPP_COMPILER
		CPP_COMPILER = emcc
	endif
	ifndef LINKER
		LINKER = emcc
	endif	
	ifndef EMCC_OPTIMIZE
		EMCC_OPTIMIZE = -O3
	endif
	
	ifndef NO_MODULARIZE
		EMCC_MODULARIZE_OPTION = -s MODULARIZE=1 -s EXPORT_NAME="'InChIModule'"
	endif
	
	EMCC_EXPORT_FUNC_UTILS = -s EXPORTED_FUNCTIONS="['_molToInchiJson', '_getInChIKeyJson']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'	
	EMCC_EXPORT_FUNCS_ALL = -s EXPORTED_FUNCTIONS="['_molToInchiJson', '_getInChIKeyJson']" -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
	EMCC_MEM_FILE_OPTION = --memory-init-file 0
	EMCC_MISC_OPTION =  $(EMCC_MODULARIZE_OPTION)
	#EMCC_MISC_OPTION = --separate-asm
else
	ifndef C_COMPILER
		C_COMPILER   = gcc
	endif
	ifndef CPP_COMPILER
		CPP_COMPILER = g++
	endif
	ifndef LINKER
		LINKER = g++
	endif	
	
	EMCC_OPTIMIZE =	
	EMCC_EXPORT_FUNC_UTILS =
	EMCC_EXPORT_FUNCS_ALL =
	EMCC_MEM_FILE_OPTION =
	EMCC_MISC_OPTION =
endif	
ifndef INCHI_EXECUTABLE_NAME
	ifdef windir
		EXE = .exe
	else ifdef EMCC
		#EXE = .html
		EXE = .js
	else
		EXE =
	endif
	ifdef EMCC
		INCHI_EXECUTABLE_NAME = inchi$(EXE)
	else
		INCHI_EXECUTABLE_NAME = inchiConv$(EXE)
	endif
	TEST_DATA_BUILDER_EXE_NAME = testDataBuilder$(EXE)
endif

 # === executable directory ===
ifndef BIN_DIR
  BIN_DIR = ../bin
endif
ifdef EMCC
  BIN_OBJ_DIR = $(BIN_DIR)/obj_emcc
else
  BIN_OBJ_DIR = $(BIN_DIR)/obj_native
endif
INCHI_EXECUTABLE_PATHNAME = $(BIN_DIR)/$(INCHI_EXECUTABLE_NAME)
TEST_DATA_BUILDER_EXE_PATHNAME = $(BIN_DIR)/$(TEST_DATA_BUILDER_EXE_NAME)
ifndef P_MAIN
	P_MAIN = ../src
endif
ifndef P_TESTER
	P_TESTER = ../test/src_cpp
endif
ifndef P_BASE
	P_BASE = ../../inchi-src/INCHI-1-SRC/INCHI_BASE/src
endif
ifndef P_LIBR
	P_LIBR = ../../inchi-src/INCHI-1-SRC/INCHI_BASE/src
endif
ifndef P_API
	P_API = ../../inchi-src/INCHI-1-SRC/INCHI_API/libinchi/src
endif

EMCC_PRE_JS_OPTION = --pre-js $(P_MAIN)/pre.js

P_INCL = -I$(P_MAIN) -I$(P_BASE) -I$(P_API)
C_COMPILER_OPTIONS = $(P_INCL) -ansi -DCOMPILE_ANSI_ONLY -DTARGET_API_LIB -O3 -c
#C_COMPILER_OPTIONS = -c $(P_INCL) -ansi -O3 -fsigned-char -ffunction-sections -fexpensive-optimizations -fstack-check -fexceptions -Wall -pedantic -Wbad-function-cast -Wreturn-type -Wformat -Wuninitialized -Wcast-align -Wshadow -Wunused -Wunused-value -Wunused-variable -Wunused-function -Wunused-parameter -Wunused-label -Wcomment -Wcast-qual -Wconversion -Wimplicit-int -Wmissing-braces -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wsign-compare -Wfloat-equal -Wstrict-prototypes -Wwrite-strings -Wundef -Waggregate-return -Wchar-subscripts -Wformat-nonliteral -Wnested-externs -Wsequence-point -Wpointer-arith -mfancy-math-387 -mieee-fp -mno-soft-float
ifdef windir
# no -ansi option due to reported MinGw bug
	#CPP_COMPILER_OPTIONS = $(P_INCL) -D_LIB -DTARGET_EXE_STANDALONE -O3 -frtti -c
	CPP_COMPILER_OPTIONS = $(P_INCL) -D_LIB -DTARGET_API_LIB -O3 -frtti -c
	#CPP_COMPILER_OPTIONS = -c $(P_INCL) -D_LIB -O3 -frtti -Wall -pedantic -Wreturn-type -Wformat -Wuninitialized -ffunction-sections -fexpensive-optimizations -fstack-check -fexceptions -Wcast-align -Wshadow -Wunused -Wunused-value -Wunused-variable -Wunused-function -fsigned-char -Wcast-qual -Wconversion -Wmissing-braces -Wredundant-decls -Wsign-compare -Wfloat-equal -Wwrite-strings -mfancy-math-387 -mieee-fp -mno-soft-float
else
	#CPP_COMPILER_OPTIONS = $(P_INCL) -D_LIB -DTARGET_EXE_STANDALONE -ansi -O3 -frtti -c
	CPP_COMPILER_OPTIONS = $(P_INCL) -D_LIB -DTARGET_API_LIB -ansi -O3 -frtti -c -std=c++11
	#CPP_COMPILER_OPTIONS = -c $(P_INCL) -D_LIB -ansi -O3 -frtti -Wall -pedantic -Wreturn-type -Wformat -Wuninitialized -ffunction-sections -fexpensive-optimizations -fstack-check -fexceptions -Wcast-align -Wshadow -Wunused -Wunused-value -Wunused-variable -Wunused-function -fsigned-char -Wcast-qual -Wconversion -Wmissing-braces -Wredundant-decls -Wsign-compare -Wfloat-equal -Wwrite-strings -mfancy-math-387 -mieee-fp -mno-soft-float
endif
#LINKER_OPTIONS = -static-libgcc
#LINKER_OPTIONS = -Wall -Wunused -Wunused-function
INCHI_SRCS = \
$(P_LIBR)/ichi_bns.c	\
$(P_LIBR)/ichi_io.c	\
$(P_LIBR)/ichican2.c	\
$(P_LIBR)/ichicano.c	\
$(P_LIBR)/ichicans.c	\
$(P_LIBR)/ichierr.c	\
$(P_LIBR)/ichiprt3.c	\
$(P_LIBR)/ichiisot.c	\
$(P_LIBR)/ichimake.c	\
$(P_LIBR)/ichiqueu.c	\
$(P_LIBR)/ichiring.c	\
$(P_LIBR)/ichierr.c	\
$(P_LIBR)/ichimap1.c	\
$(P_LIBR)/ichimap2.c	\
$(P_LIBR)/ichimap4.c	\
$(P_LIBR)/ichimak2.c	\
$(P_LIBR)/ichinorm.c	\
$(P_LIBR)/ichiparm.c	\
$(P_LIBR)/ichiprt1.c	\
$(P_LIBR)/ichiprt2.c	\
$(P_LIBR)/ichirvr1.c	\
$(P_LIBR)/ichirvr2.c	\
$(P_LIBR)/ichirvr3.c	\
$(P_LIBR)/ichirvr4.c	\
$(P_LIBR)/ichirvr5.c	\
$(P_LIBR)/ichirvr6.c	\
$(P_LIBR)/ichirvr7.c	\
$(P_LIBR)/ichisort.c	\
$(P_LIBR)/ichister.c	\
$(P_LIBR)/ichitaut.c	\
$(P_LIBR)/ikey_base26.c	\
$(P_LIBR)/ikey_dll.c	\
$(P_LIBR)/mol_fmt1.c	\
$(P_LIBR)/mol_fmt2.c	\
$(P_LIBR)/mol_fmt3.c	\
$(P_LIBR)/mol_fmt4.c	\
$(P_LIBR)/runichi.c	\
$(P_LIBR)/runichi2.c	\
$(P_LIBR)/runichi3.c	\
$(P_LIBR)/runichi4.c	\
$(P_LIBR)/sha2.c	\
$(P_LIBR)/strutil.c	\
$(P_LIBR)/util.c	\
$(P_LIBR)/mol2atom.c	\
$(P_LIBR)/readinch.c	\
$(P_API)/inchi_dll.c	\
$(P_API)/inchi_dll_a.c	\
$(P_API)/inchi_dll_a2.c	\
$(P_API)/inchi_dll_b.c	\
$(P_API)/inchi_dll_main.c	\
$(P_MAIN)/inchi_js_utils.c	\
$(P_MAIN)/inchi_conv.c
# $(P_MAIN)/dispstru.c	\
# $(P_MAIN)/ichimain.c
#
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
$(BIN_OBJ_DIR)/inchi_js_utils.o	\
#$(BIN_OBJ_DIR)/dispstru.o	\
#$(BIN_OBJ_DIR)/ichimain.o

INCHI_EXE_OBJS =	\
$(BIN_OBJ_DIR)/inchi_conv.o

TEST_DATA_BUILDER_OBJS =	\
$(BIN_OBJ_DIR)/testDataBuilder.o

ALL_EXE_PATHNAMES = $(INCHI_EXECUTABLE_PATHNAME)
ifndef EMCC
	ALL_EXE_PATHNAMES += $(TEST_DATA_BUILDER_EXE_PATHNAME)
endif

all:createDirs exeTasks

createDirs:
	-mkdir ../bin
	-mkdir ../bin/obj_native	
	-mkdir ../bin/obj_emcc	
	
ifdef EMCC
exeTasks: $(INCHI_EXECUTABLE_PATHNAME)
else
exeTasks: $(INCHI_EXECUTABLE_PATHNAME) $(TEST_DATA_BUILDER_EXE_PATHNAME)
endif	

$(INCHI_EXECUTABLE_PATHNAME) : $(INCHI_OBJS) $(INCHI_EXE_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(INCHI_EXECUTABLE_PATHNAME) $(INCHI_OBJS) $(INCHI_EXE_OBJS) -lm $(EMCC_OPTIMIZE) $(EMCC_EXPORT_FUNCS_ALL) $(EMCC_MEM_FILE_OPTION) $(EMCC_MISC_OPTION) $(EMCC_PRE_JS_OPTION)
$(TEST_DATA_BUILDER_EXE_PATHNAME) : $(INCHI_OBJS) $(TEST_DATA_BUILDER_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(TEST_DATA_BUILDER_EXE_PATHNAME) $(INCHI_OBJS) $(TEST_DATA_BUILDER_OBJS) -lm $(EMCC_OPTIMIZE) $(EMCC_EXPORT_FUNCS_ALL) $(EMCC_MEM_FILE_OPTION) $(EMCC_MISC_OPTION)
# ichi_bns.o:
#	$(C_COMPILER) $(C_COMPILER_OPTIONS) $(P_BASE)/ichi_bns.c
# inchi_dll.o:
#	$(C_COMPILER) $(C_COMPILER_OPTIONS) $(P_API)/inchi_dll.c
$(BIN_OBJ_DIR)/util.o:
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $(P_MAIN)/util.c -o $@
$(BIN_OBJ_DIR)/inchi_js_utils.o:
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $(P_MAIN)/inchi_js_utils.c $(EMCC_EXPORT_FUNC_UTILS) -o $@
$(BIN_OBJ_DIR)/%.o: $(P_BASE)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(P_API)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(P_MAIN)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $< -o $@
$(BIN_OBJ_DIR)/%.o: $(P_TESTER)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $< -o $@
clean:
	rm $(BIN_OBJ_DIR)/*.o
