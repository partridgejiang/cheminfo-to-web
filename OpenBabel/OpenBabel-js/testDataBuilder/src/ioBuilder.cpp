#include <stdio.h>
#include <iostream>
#include <string>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <time.h>
#include "../../OpenBabel-js/src/embind/ObWrapper.cpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


using namespace std;
using namespace boost::property_tree;
using namespace OpenBabel;

OpenBabel::OBMol* readData(string inputData, OBFormat* pInFormat = NULL)
{
  OpenBabel::OBMol *mol;
  OpenBabel::OBConversion conv;
  
  mol = new OpenBabel::OBMol();
  
  if (pInFormat)
    conv.SetInFormat(pInFormat);
  else
    conv.SetInFormat("MOL");
  if (!conv.ReadString(mol, inputData))
  {
	cout << "Error reading MOL data" << endl;	
	return NULL;
  }
  
  return mol;
}

string writeData(OpenBabel::OBMol* mol, string format = "MOL")
{
  OpenBabel::OBConversion conv;
  conv.SetOutFormat(format.c_str());
  
  string result = conv.WriteString(mol);
  if (result == "")
  {
	cout << "Fail to write MOL data" << endl;
	return "";
  }
  
  return result;
}

string loadFileToStr(string fileName)
{
  ifstream ifs(fileName.c_str());
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

void buildTestData(string inputFileName, string outputFileName = "")
{
	string outputFormats[] = {"mol", "pdb", /*"cml", "xyz",*/ "mol2", "inp", "mopin", "smiles"};
		// JS-wrapper can not generate CML. XYZ format the atom mark in JS will starts with additinal blanks (but still legal, e.g. '  C  ' vs 'C    ').
	//string mimeTypes[] = {"chemical/x-mdl-molfile", "chemical/x-pdb", /*"chemical/x-cml",*/ "chemical/x-mol2", "chemical/x-xyz", "chemical/x-daylight-smiles"};
	int outFormatCount = sizeof(outputFormats) / sizeof(outputFormats[0]);

	string oFileName = outputFileName;
	if (outputFileName == "")
		oFileName = inputFileName + ".ob.json";
		
	ptree ptRoot;
	ptree ptContainer;
	ptree ptItem;
		
	string inputData = loadFileToStr(inputFileName);
	
	OBFormat* pInFormat = NULL;
	OpenBabel::OBConversion conv;
	pInFormat = conv.FormatFromExt(inputFileName);
	
	cout << inputFileName << " : " << " : " << pInFormat->GetID() << " : " << pInFormat->GetMIMEType() << endl;
	
	OpenBabel::OBMol* mol = readData(inputData, pInFormat);	
	
	cout << "Mol data loaded" << endl;
	
	ptItem.put("format", /*"mol"*/pInFormat->GetID());
	ptItem.put("mimeType", /*"chemical/x-mdl-molfile"*/pInFormat->GetMIMEType());
	ptItem.put("data", inputData);
	ptRoot.add_child("input", ptItem);
	
	int i;
	for (i = 0; i < outFormatCount; ++i)
	{
		string fmt = outputFormats[i];
		OBFormat* pOutFormat = NULL;
		pOutFormat = conv.FindFormat(fmt);
		//string mimeType = mimeTypes[i];
		string mimeType = pOutFormat->GetMIMEType();
		string outputData = writeData(mol, fmt);
		
		//cout << outputData << endl;
		
		ptItem.put("format", fmt);
		ptItem.put("mimeType", mimeType);
		ptItem.put("data", outputData);		
		
		ptContainer.push_back(std::make_pair("", ptItem));
		
		cout << "Output data (" << i + 1 << "/" << outFormatCount << ") of " << " " << fmt << " : " << mimeType << endl;
	}
	ptRoot.add_child("output", ptContainer);	
	
	//cout << "Writing to result file..." << endl;
	
	delete mol;
	
	ofstream fout(oFileName.c_str());
	if (!fout.is_open())   
    {
		cout << "Error opening file" << outputFileName << endl;
		return;         
    }
    write_json(fout, ptRoot);
	fout.close();
}

int main(int argc,char **argv)
{
  int loopCount = 1;  
  if(argc < 2)
  {
    cout << "Usage: ProgrameName InputFileName.mol [OutputResultFileName.json]\n";
    return 1;
  }
  
  string inputFileName = argv[1];
  string outputFileName = "";
  if (argc > 2)
	outputFileName = argv[2];
  
  buildTestData(inputFileName, outputFileName);  

  return 0;
}
