This directory contains the additional source codes that need to be used when compiling Indigo lib to JavaScript using Emscripten.

If you want to build the Javascript code yourself, please follow the steps below under 64 bit Linux:

1. Create a base directory, e.g. Indigo.
2. Download Indigo source code from https://github.com/epam/Indigol (1.3.0 in 2017.6). Put the zip archieve inside base directory.
3. Decompress the archieve to indigo-src sub folder of the base directory, then rename Indigo-src/Indigo-master(or any other name with version numbers) to Indigo-src/Indigo. Ensure you can get Indigo-src/Indigo/api, Indigo-src/Indigo/common sub directories and so on.
4. Download InChi source code from http://www.inchi-trust.org/downloads/ (INCHI-1-SRC.zip) at present (2017.6).
5. Decompress INCHI-1-SRC.zip, and copy its INCHI_API, INCHI_BASE sub folder under INCHI-1-SRC to Indigo-src/Indigo/third_party/inchi (fixes some issues of InChI code shipped with Indigo itself).
6. Enter Indigo-src/Indigo/build_scriptes directory, run the following commands:
      python ./indigo-release-libs.py --preset=linux64
      python ./indigo-release-utils.py --preset=linux64
   Those commands will build Indigo source and generate essential files.
7. Put the Indigo-js directory to the same base directory (e.g., get Indigo/Indigo-js).
8. Execute "make" command inside Indigo/Indigo-js/make to generate native executable file on Linux; use "make EMCC=1" to generate js code. The compiled outputs are all in bin directory.