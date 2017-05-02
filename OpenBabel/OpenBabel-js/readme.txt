This directory contains the additional source codes that need to be used when compiling OpenBabel C++ lib to JavaScript using emscripten.

If you want to build the javascript yourself, please follow the steps below:

1. Download OpenBabel source code from http://openbabel.org/wiki/Get_Open_Babel . At present the stable version is 2.4.1 (2017.3).
2. Decompress the zipped file to "OpenBabel-src/src" sub folder of a base directory "OpenBabel" (then you can get OpenBabel/OpenBabel-src/src/src, OpenBabel/OpenBabel-src/src/include... sub directories).
3. Create a new sub directory inside "OpenBabel-src" directory, e.g. "build-emcc"
4. Change into build-emcc directory, run command "emcmake cmake ../src" to generate make file.
5. Run command "emmake make" to build source code of OpenBabel and generate essential object files.
6. Copy "OpenBabel-js" folder inside base "OpenBabel" directory. 
7. Enter into make sub directory (OpenBabel-js/make).
7. Run command make to build OpenBabel js lib. The output file will be saved in "OpenBabel-js/bin" sub folder.
