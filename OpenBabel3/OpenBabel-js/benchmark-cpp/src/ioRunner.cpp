#include <iostream>
#include <string>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <time.h>
#include "ObWrapper.cpp"
using namespace std;
using namespace OpenBabel;

OpenBabel::OBMol* readData(string inputData, int loopCount = 1)
{
  OpenBabel::OBMol *mol;
  OpenBabel::OBConversion conv;
  
  mol = new OpenBabel::OBMol();
  
  conv.SetInFormat("MOL");
  if (!conv.ReadString(mol, inputData))
  {
	cout << "Error reading MOL data" << endl;	
	return NULL;
  }
  
  // Start benchmark
  int i;  
  clock_t tStart = clock();
  for (i = 0; i < loopCount; ++i)
  {
    if (conv.ReadString(mol, inputData))
	{
	  cout << "Read " << i << " successful" << endl;
	}
	else
	{
	  cout << "Read " << i << " failed!" << endl;
	}
  }
  clock_t tEnd = clock();
  int execTime = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
  printf("Run read MOL %d times in %d ms.\n", loopCount, execTime);
  
  return mol;
}

string writeData(OpenBabel::OBMol* mol, string format = "MOL", int loopCount = 1)
{
  OpenBabel::OBConversion conv;
  conv.SetOutFormat(format.c_str());
  
  string result = conv.WriteString(mol);
  if (result == "")
  {
	cout << "Fail to write MOL data" << endl;
	return "";
  }
  
  // Start benchmark
  int i;  
  clock_t tStart = clock();
  for (i = 0; i < loopCount; ++i)
  {
	result = conv.WriteString(mol);
	/*
    if (result != "")
	{
	  cout << "Write " << i << " successful" << endl;
	}
	else
	{
	  cout << "Write " << i << " failed!" << endl;
	}
	*/
  }
  clock_t tEnd = clock();
  int execTime = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
  printf("Run write %s %d times in %d ms.\n", format.c_str(), loopCount, execTime);
  
  return result;
}

OpenBabel::OBMol* readDataWrapper(string inputData, int loopCount = 1)
{
  OpenBabel::ObConversionWrapper conv;
  
  OpenBabel::OBMol *mol;  
  
  cout << "here" << endl;
  
  mol = new OpenBabel::OBMol();
  
  cout << "there" << endl;
  
  conv.setInFormat("chemical/x-mdl-molfile", "mol");
  if (!conv.readString(mol, inputData))
  {
	cout << "Error reading MOL data" << endl;	
	return NULL;
  }
  
  // Start benchmark
  int i;  
  clock_t tStart = clock();
  for (i = 0; i < loopCount; ++i)
  {
    if (conv.readString(mol, inputData))
	{
	  //cout << "Read " << i << " successful" << endl;
	}
	else
	{
	  //cout << "Read " << i << " failed!" << endl;
	}
  }
  clock_t tEnd = clock();
  int execTime = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
  printf("Run read MOL (in wrapper) %d times in %d ms.\n", loopCount, execTime);
  
  return mol;
}

string writeDataWrapper(OpenBabel::OBMol* mol, string format = "chemical/x-mdl-molfile", string fileExt="mol", int loopCount = 1)
{
  OpenBabel::ObConversionWrapper conv;
  conv.setOutFormat(format, fileExt);
  
  string result = conv.writeString(mol);
  if (result == "")
  {
	cout << "Fail to write MOL data" << endl;
	return "";
  }
  
  // Start benchmark
  int i;  
  clock_t tStart = clock();
  for (i = 0; i < loopCount; ++i)
  {
	result = conv.writeString(mol);
	/*
    if (result != "")
	{
	  cout << "Write " << i << " successful" << endl;
	}
	else
	{
	  cout << "Write " << i << " failed!" << endl;
	}
	*/
  }
  clock_t tEnd = clock();
  int execTime = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
  printf("Run write (in wrapper) %s %d times in %d ms.\n", format.c_str(), loopCount, execTime);
  
  return result;
}

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

int main(int argc,char **argv)
{
  int loopCount = 1;  
  if(argc < 2)
  {
    cout << "Usage: ProgrameName InputFileName.mol loopCount\n";
    return 1;
  }
  if (argc >= 3)
  {
    loopCount = atoi(argv[2]);
  }
  
  string inputStr = loadFileToStr(argv[1]);
  cout << "Input data:" << endl << inputStr << endl;
  cout << "Ready to benchmark..." << endl;
  
  OpenBabel::OBMol* mol = readDataWrapper(inputStr, loopCount);
  
  string outStr = writeDataWrapper(mol, "chemical/x-mdl-molfile", "mol", loopCount);
  cout << "Output MOL data" << endl << outStr << endl << endl;
  outStr = writeDataWrapper(mol, "chemical/x-pdb", "pdb", loopCount);
  cout << "Output CML data" << endl << outStr << endl << endl;
  
  delete mol;
  /*
  ofstream ofs(argv[2]);
  if(!ofs)
  {
    cout << "Cannot open output file\n";
    return 1;
  }
  OpenBabel::OBConversion conv(&ifs, &ofs);
  if(!conv.SetInAndOutFormats("MOL","PDB"))
  {
    cout << "Formats not available\n";
    return 1;
  }
  int n = conv.Convert();
  cout << n << " molecules converted\n";
  */

  return 0;
}
