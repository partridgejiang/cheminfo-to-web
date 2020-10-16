This directory contains the additional source codes that need to be used when compiling OpenBabel C++ lib to JavaScript using emscripten.

If you want to build the javascript yourself, please follow the steps below:


1. Create a root directory, e.g., MyOpenBabel.
2. Download OpenBabel3 source code from https://github.com/openbabel/openbabel . At present the stable version is 3.1.1.
3. Decompress the zipped file to OpenBabel-src/src sub folder of the root directory, get subdirectories MyOpenBabel/OpenBabel-src/src/src, MyOpenBabel/OpenBabel-src/src/include and so on.
4. Create directory MyOpenBabel/3rdPartyLibs.
5. Download eigen2  from http://eigen.tuxfamily.org. (Note: the latest release is eigen3, but OpenBabel compiled only with eigen2). Copy files of eigen2 into MyOpenBabel/3rdPartyLibs/eigen2.
6. Create a new sub directory (e.g. build-emcc) inside MyOpenBabel/OpenBabel-src directory.
7. Change into build-emcc directory, run command emcmake cmake ../src to generate make file and other essential files for JavaScript compilation.
8. Copy our OpenBabel-js folder into root directory. 
9. Enter into subdirectory OpenBabel-js/make.
10. Run command make EMCC=1 to build OpenBabel JS lib. The output file will be saved in "OpenBabel-js/bin" sub folder.

