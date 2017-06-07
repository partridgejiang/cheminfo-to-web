This directory contains the additional source codes that need to be used when compiling InChi C lib to JavaScript using emscripten.

If you want to build the Javascript code yourself, please follow the steps below under Linux:

1. Create a root directory (e.g. MyInChI).
2. Download InChI library source code (INCHI-1-SRC.zip) from InChI download site http://www.inchi-trust.org/downloads/.
3. Decompress INCHI-1-SRC.zip to inchi-src sub folder of root directory (e.g., if the root directory is named MyInChI, then sub directories MyInChI/inchi-src/INCHI-1-SRC/INCHI_BASE, MyInChI/inchi-src/INCHI-1-SRC/INCHI_API and MyInChI/inchi-src/INCHI-1-SRC/INCHI_EXE are got).
4. Copy our inchi-js directory to the same root directory (e.g., get MyInchI/inchi-js).
5. Enter into directory inchi-js/make/, execute command make directly or make NATIVE=1 to generate native executable files; run command make EMCC=1 to compile to JavaScript code. All compiled outputs will be created in inchi-js/bin directory.
