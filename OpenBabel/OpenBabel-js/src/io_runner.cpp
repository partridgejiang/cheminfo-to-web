#include <iostream>
#include <string>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <time.h>
using namespace std;

void readData(string inputData, int loopCount)
{
  OpenBabel::OBMol mol;
  OpenBabel::OBConversion conv;
  
  conv.SetInFormat("MOL");
  if (!conv.ReadString(&mol, inputData))
  {
	cout << "Error reading MOL data" << endl;	
  }
  
  // Start benchmark
  int i;  
  clock_t tStart = clock();
  for (i = 0; i < loopCount; ++i)
  {
    if (conv.ReadString(&mol, inputData))
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
  printf("Run %d times in %d ms.\n", loopCount, execTime);
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
    cout << "Usage: ProgrameName InputFileName.mol\n";
    return 1;
  }
  if (argc >= 3)
  {
    loopCount = atoi(argv[2]);
  }
  
  string inputStr = loadFileToStr(argv[1]);
  cout << "Input data:" << endl << inputStr << endl;
  cout << "Ready to benchmark..." << endl;
  readData(inputStr, loopCount);
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
