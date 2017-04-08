#include <iostream>
//#include "../../openbabel-src/src/include/openbabel/obconversion.h"
#include <openbabel/obconversion.h>
using namespace std;

int main(int argc,char **argv)
{
  if(argc<3)
  {
    cout << "Usage: ProgrameName InputFileName OutputFileName\n";
    return 1;
  }

  ifstream ifs(argv[1]);
  if(!ifs)
  {
    cout << "Cannot open input file\n";
    return 1;
  }
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

  return 0;
}
