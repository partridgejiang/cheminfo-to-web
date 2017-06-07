This directory contains the additional source codes that need to be used when compiling OpenMD C++ lib to JavaScript using emscripten.

If you want to build the javascript yourself, please follow the steps below in 64 bit Linux:

1. Create a root directory, e.g. MyOpenMD.
2. Download or clone OpenMD source code from https://github.com/OpenMD/OpenMD. At present the stable version is 2.4.1.
3. Put the OpenMD source under MyOpenMD/OpenMD-src/src sub folder, get subdirectories MyOpenMD/OpenMD-src/src/src, MyOpenMD/OpenMD-src/src/forceFields and so on.
4. Create a build-linux sub folder inside OpenMD-src directory, then run command cmake ../src inside it to create essential files for building.
5. Copy our OpenMD-js folder inside the root directory. 
6. Enter into sub directory OpenMD-js/make.
7. Run command make EMCC=1 to build OpenMD JavaScript library. The output file will be saved in OpenMD-js/bin subdirectory.

