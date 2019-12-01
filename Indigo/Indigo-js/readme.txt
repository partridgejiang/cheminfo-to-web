This directory contains the additional source codes that need to be used when compiling Indigo lib to JavaScript using Emscripten.

If you want to build the Javascript code yourself, please follow the steps below under 64 bit Linux:

1. Create a root directory, e.g. MyIndigo.
2. Download or clone Indigo source code from https://github.com/epam/Indigol (1.4.0 at present).
3. Put the downloaded Indigo source to indigo-src/Indigo sub folder of the base directory. Ensure subdirectories MyIndigo/Indigo-src/Indigo/api, MyIndigo/Indigo-src/Indigo/common and so on are got.
4. Download InChi source code (INCHI-1-SRC.zip) from http://www.inchi-trust.org/downloads/.
5. Decompress INCHI-1-SRC.zip, and copy its INCHI-1-SRC/INCHI_API, INCHI-1-SRC/INCHI_BASE sub folder to MyIndigo/Indigo-src/Indigo/third_party/inchi. Those operations fix some issues of InChI code shipped with Indigo itself.
Enter Indigo-src/Indigo/build_scripts directory, run the following commands to build Indigo source and generate additional files for compiling JavaScript library:
      python ./indigo-release-libs.py --preset=linux64
      python ./indigo-release-utils.py --preset=linux64
6. Copy our Indigo-js directory to the root directory (e.g., MyIndigo/Indigo-js).
7. Enter into directory Indigo-js /make/, execute command make directly or make NATIVE=1 to generate native executable files; run command make EMCC=1 to compile to JavaScript code. All compiled outputs will be created in Indigo-js/bin directory.
