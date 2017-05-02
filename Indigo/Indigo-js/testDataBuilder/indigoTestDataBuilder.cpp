#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "indigo.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using namespace boost::property_tree;

void onError(const char *message, void *context)
{
   fflush(stdout);
   fprintf(stderr, "%s\n", message);
   fflush(stderr);
   exit(-1);
}

const char* canonicalSmiles(int mol, int loopCount)
{
	int i;
	const char* smiles;
	for (i = 0; i < loopCount; ++i)
	{
		smiles = indigoCanonicalSmiles(mol);
		if (!smiles)
			return NULL;
	}
	return smiles;
}

int layoutMol(int mol, int loopCount)
{
	int i;
	int ret, mol2;	
	const char* canoSmiles = indigoCanonicalSmiles(mol);
	char* smiles = (char*)malloc(strlen(canoSmiles));
	strcpy(smiles, canoSmiles);  // save copy, otherwise canoSmiles seems will be disposed in loop
	indigoSetOption("smart-layout", "true");
	//for (i = 0; i < loopCount; ++i)
	{		
		//printf("Smiles: %s\n", smiles);
		//indigoClean2d(mol);
		//const char* molData = indigoMolfile(mol);
		//printf("Mol Data after clean 2D: \n%s\n", molData);
		//if (mol2)
		//	indigoFree(mol2);
		mol2 = indigoLoadMoleculeFromString(smiles);
		//const char* molData = indigoMolfile(mol2);
		//printf("Mol Data before layout: %d/%d %s\n%s\n", i, loopCount, smiles, molData);
		ret = indigoLayout(mol2);
		//const char* molData2 = indigoMolfile(mol2);
		//printf("Mol Data after layout: %d/%d\n%s\n", i, loopCount, molData2);				
		if (!ret)
			return 0;				
	}
	free(smiles);
	//return ret;
	return mol2;
}

int sssrCount(int mol, int loopCount)
{
	int i, ret;	
	for (i = 0; i < loopCount; ++i)
	{
		indigoClearProperties(mol);
		ret = indigoCountSSSR(mol);		
		if (ret < 0)
			return -1;
	}
	return ret;
}

int findTautomers(int mol, int loopCount)
{
	int i, ret;
	for (i = 0; i < loopCount; ++i)
	{		
		ret = indigoIterateTautomers(mol, "");		
		if (ret < 0)
			return -1;
	}
	return ret;	
}

const char* saveToCml(int mol, int loopCount)
{
	int i;	
	const char* ret;
	for (i = 0; i < loopCount; ++i)
	{
		ret = indigoCml(mol);
		if (!ret)
			return NULL;
	}
	return ret;
}
const char* saveToMol(int mol, int loopCount)
{
	int i;	
	const char* ret;
	for (i = 0; i < loopCount; ++i)
	{
		ret = indigoMolfile(mol);
		if (!ret)
			return NULL;
	}
	return ret;
}

string loadFileToStr(string fileName)
{
  ifstream ifs(fileName.c_str());
  if(!ifs)
  {
    cout << "Cannot open input file: " << fileName << endl;
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

int main(int argc, char *argv[])
{
	int loopCount = 1;
	
	string oFileName = "";
	
	if (argc < 2)
    {
        printf("Usage: indigoTestDataBuilder source.mol [result.indigo.json]\n");
		return -1;
    }
	if (argc > 2)
		oFileName = argv[2];
	else
	{
		oFileName = argv[1];
		oFileName += ".indigo.json";
	}
	
	
	indigoSetErrorHandler(onError, 0);
		
	char* fileName = argv[1];
	
	ptree ptRoot;
	ptree ptInput;
	ptree ptOutput;
	
	string inputData = loadFileToStr(fileName);
	int mol = indigoLoadMoleculeFromFile(fileName);
	
	ptInput.put("format", "mol");
	ptInput.put("mimeType", "chemical/x-mdl-molfile");
	ptInput.put("data", inputData);
	ptRoot.add_child("input", ptInput);
	
	// Canonical smiles
	const char* smiles = canonicalSmiles(mol, loopCount);
	if (!smiles)
		printf("Canonicalize SMILES failed!\n");
	else
		printf("Canonicalized SMILES: %s\n", smiles);
	ptOutput.put("smiles", smiles);
		
	// Auto layout
	int layoutRet = layoutMol(mol, loopCount);
	const char* layoutMol = saveToMol(/*mol*/layoutRet, loopCount);
	ptOutput.put("layoutMol", layoutMol);
	
	// SSSR count	
	int count = sssrCount(mol, loopCount);
	if (count < 0)
		printf("SSSR count failed!\n");
	else
		printf("SSSR count: %d\n", count);
	ptOutput.put<int>("sssrCount", count);
	
	// find Tautomers
	string tautomersSmiles = "";
	int iter = findTautomers(mol, loopCount);
	if (iter < 0)
		printf("Tautomer searching failed!\n");
	else
	{	
		int item, index = 0;
		while (item = indigoNext(iter))
		{
			if (item >= 0)
			{
				++index;
				int mol2 = indigoClone(item);
				const char *itemSmiles = indigoCanonicalSmiles(mol2);
				indigoFree(item);
				indigoFree(mol2);
				printf("Tautomer %d: %s\n", index, itemSmiles);
				tautomersSmiles += itemSmiles;
				tautomersSmiles += "\n";
			}
		}
		indigoFree(iter);
	}
	ptOutput.put("tautomers", tautomersSmiles);
	
	// Save to CML	
	const char* cml = saveToCml(mol, loopCount);
	if (!cml)
		printf("Save CML failed!\n");
	else
		printf("CML:\n%s\n", cml);
	ptOutput.put("cml", cml);
	
	// Save to MOL
	const char* molData = saveToMol(mol, loopCount);
	if (!molData)
		printf("Save MOL failed!\n");
	else
		printf("MOL:\n%s\n", molData);
	ptOutput.put("mol", molData);
	
	ptRoot.add_child("output", ptOutput);	
	ofstream fout(oFileName.c_str());
	if (!fout.is_open())   
    {
		cout << "Error opening file" << oFileName << endl;
		return 1; 
    }
    write_json(fout, ptRoot);
	fout.close();
	
	indigoFree(mol);		
		
	return 0;
}