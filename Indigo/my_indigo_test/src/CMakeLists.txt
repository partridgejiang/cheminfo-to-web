cmake_minimum_required(VERSION 2.6)

project(IndigoTest)

add_executable(indigoTest main.cpp)

include_directories(../../Indigo-src/Indigo/api)
target_link_libraries(indigoTest /mnt/hgfs/WinUsers/Ginger/Programer/Project/chemoinfWeblizer/Cheminfo-weblize/Indigo/Indigo-src/Indigo/build/indigo_Unix_Makefiles_ReleaseSUBSYSTEM_NAME_x64/dist/Linux/x64/lib/libindigo-static.a /mnt/hgfs/WinUsers/Ginger/Programer/Project/chemoinfWeblizer/Cheminfo-weblize/Indigo/Indigo-src/Indigo/build/indigo_Unix_Makefiles_ReleaseSUBSYSTEM_NAME_x64/dist/Linux/x64/lib/libindigo.a  /mnt/hgfs/WinUsers/Ginger/Programer/Project/chemoinfWeblizer/Cheminfo-weblize/Indigo/Indigo-src/Indigo/build/indigo_Unix_Makefiles_ReleaseSUBSYSTEM_NAME_x64/dist/Linux/x64/lib/libtinyxml.a /mnt/hgfs/WinUsers/Ginger/Programer/Project/chemoinfWeblizer/Cheminfo-weblize/Indigo/Indigo-src/Indigo/build/indigo_Unix_Makefiles_ReleaseSUBSYSTEM_NAME_x64/dist/Linux/x64/lib/libz.a /mnt/hgfs/WinUsers/Ginger/Programer/Project/chemoinfWeblizer/Cheminfo-weblize/Indigo/Indigo-src/Indigo/build/indigo_Unix_Makefiles_ReleaseSUBSYSTEM_NAME_x64/dist/Linux/x64/lib/libinchi.a /mnt/hgfs/WinUsers/Ginger/Programer/Project/chemoinfWeblizer/Cheminfo-weblize/Indigo/Indigo-src/Indigo/build/indigo_Unix_Makefiles_ReleaseSUBSYSTEM_NAME_x64/dist/Linux/x64/lib/libpixman.a)