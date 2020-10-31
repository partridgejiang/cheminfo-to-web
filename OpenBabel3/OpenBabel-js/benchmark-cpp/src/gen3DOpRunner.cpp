#include <iostream>
#include <string>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/op.h>
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

OBMol* generate3DStructureFromMolData(std::string molData, std::string srcFormat = "mol")
{
	ObConversionWrapper conv;
	conv.setInFormat("", srcFormat);

	OBMol* obMol = new OBMol();
	conv.readString(obMol, molData);	

	// std::cout << obMol->NumAtoms() << std::endl;
	// std::cout << srcFormat << std::endl;

	OBOp* opGen3D = OpenBabel::OBOp::FindType("Gen3D");	

	opGen3D->Do(obMol, "");		

	//delete opGen3D;
	return obMol;
}

OpenBabel::OBMol* runGen3D(string srcData, string srcFormat="mol", int loopCount = 1)
{  
  int i;
  clock_t tStart = clock();
  OpenBabel::OBMol* mol;
  for (i = 0; i < loopCount; ++i)
  {
    mol = generate3DStructureFromMolData(srcData, srcFormat);
  }
  clock_t tEnd = clock();
  int execTime = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
  printf("Run 3D generation %d times in %d ms.\n", loopCount, execTime);
  
  return mol;
}

int main(int argc,char **argv)
{
  int loopCount = 1;  
  string sFormat = "mol";  
  if(argc < 2)
  {
    cout << "Usage: ProgrameName InputFileName InputFileFormat\n";
    return 1;
  }
  if (argc >= 4)
  {
    loopCount = atoi(argv[3]);
    sFormat = argv[2];
  }
  else if (argc >= 3)
  {
    loopCount = atoi(argv[2]);
    sFormat = "mol";
  }
  
  string inputStr = loadFileToStr(argv[1]);  
  cout << "Input data:" << endl << inputStr << endl;
  cout << "Ready to benchmark..." << endl;
  
  OpenBabel::OBMol* mol = runGen3D(inputStr, sFormat, loopCount);

  std::cout << "Mol atom count" << mol->NumAtoms() << std::endl;
  
  string outStr = writeMolData(mol);  
   
  cout << "Output MOL data" << endl << outStr << endl << endl;

  return 0;
}