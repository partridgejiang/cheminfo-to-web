This directory contains the additional source codes that need to be used when compiling InChi C lib to JavaScript using emscripten.

If you want to build the javascript yourself, please follow the steps below:

1. Download InChi source code from http://www.inchi-trust.org/downloads/ (INCHI-1-SRC.zip) at present (2017.3).
2. Decompress INCHI-1-SRC.zip to a base directory (e.g. MyInchi, then you can get MyInchi/INCHI-1-SRC/INCHI_BASE, MyInchi/INCHI-1-SRC/INCHI_API and MyInchi/INCHI-1-SRC/INCHI_EXE sub directories).
3. Put inchi-js directory to the same base directory (e.g., get MyInchi/inchi-js).
4. Execute make command inside MyInchi/inchi-js/gcc to generate native executable file on Linux; use make EMCC=1 to generate js code.
