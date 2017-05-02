This directory contains the additional source codes that need to be used when compiling OpenMD C++ lib to JavaScript using emscripten.

If you want to build the javascript yourself, please follow the steps below:

1. Download OpenMD source code from https://github.com/OpenMD/OpenMD. At present the stable version is 2.4.1 (2017.3).
2. Decompress the zipped file to "OpenMD-src/src" sub folder of a base directory "OpenBabel" (then you can get OpenMD/OpenMD-src/src/src, OpenMD/OpenMD-src/src/forceFields... sub directories).
3. Copy "OpenMD-js" folder inside base "OpenMD" directory. 
4. Enter into make sub directory (OpenMD-js/make).
5. Run command "make EMCC=1" to build OpenBabel js lib. The output file will be saved in "OpenMD-js/bin" sub folder.
