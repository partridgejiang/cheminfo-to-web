#include <iostream>
#include <string>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <time.h>
#include "ObWrapper.cpp"
using namespace std;
using namespace OpenBabel;

string loadFileToStr(char* fileName)
{
  ifstream ifs(fileName);
  if(!ifs)
  {
    cout << "Cannot open input file\n";
    return "";
  }
  
  ostringstream buf;
  char ch;
  while(buf && ifs.get(ch))
  {
	buf.put(ch);
  }
  return buf.str();
}

string writeMolData(OpenBabel::OBMol* mol, string format = "chemical/x-mdl-molfile", string fileExt="mol", int loopCount = 1)
{
  OpenBabel::ObConversionWrapper conv;
  conv.setOutFormat(format, fileExt);
  
  string result = conv.writeString(mol);
  if (result == "")
  {
	cout << "Fail to write MOL data" << endl;
	return "";
  }  
  return result;
}

OpenBabel::OBMol* runGen3D(string srcData, string forceField = "MMFF94", int loopCount = 1)
{
  OpenBabel::OB3DGenWrapper gen;
  int i;
  clock_t tStart = clock();
  OpenBabel::OBMol* mol;
  for (i = 0; i < loopCount; ++i)
  {
    mol = gen.generate3DStructureFromMolData(srcData, forceField);
  }
  clock_t tEnd = clock();
  int execTime = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
  printf("Run 3D generation by force field [%s] %d times in %d ms.\n", forceField.c_str(), loopCount, execTime);
  
  return mol;
}

int main(int argc,char **argv)
{
  int loopCount = 1;  
  string forceField = "";
  if(argc < 2)
  {
    cout << "Usage: ProgrameName InputFileName.mol loopCount forceField \n";
    return 1;
  }
  if (argc >= 3)
  {
    loopCount = atoi(argv[2]);
  }
  if (argc >= 4)
  {
    forceField = argv[3];
  }
  
  string inputStr = loadFileToStr(argv[1]);
  cout << "Input data:" << endl << inputStr << endl;
  cout << "Ready to benchmark..." << endl;
  
  OpenBabel::OBMol* mol = runGen3D(inputStr, forceField, loopCount);
  
  string outStr = writeMolData(mol);  
   
  cout << "Output MOL data" << endl << outStr << endl << endl;

  return 0;
}