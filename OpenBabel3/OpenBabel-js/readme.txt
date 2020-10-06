This directory contains the additional source codes that need to be used when compiling OpenBabel C++ lib to JavaScript using emscripten.

If you want to build the javascript yourself, please follow the steps below:


1. Create a root directory, e.g., MyOpenBabel.
2. Download OpenBabel source code from http://openbabel.org/wiki/Get_Open_Babel . At present the stable version is 2.4.1.
3. Decompress the zipped file to OpenBabel-src/src sub folder of the root directory, get subdirectories MyOpenBabel/OpenBabel-src/src/src, MyOpenBabel/OpenBabel-src/src/include and so on.
4. Create a new sub directory (e.g. build-emcc) inside MyOpenBabel/OpenBabel-src directory.
5. Change into build-emcc directory, run command emcmake cmake ../src to generate make file and other essential files for JavaScript compilation.
6. Copy our OpenBabel-js folder into root directory. 
7. Enter into subdirectory OpenBabel-js/make.
8. Run command make EMCC=1 to build OpenBabel JS lib. The output file will be saved in "OpenBabel-js/bin" sub folder.

