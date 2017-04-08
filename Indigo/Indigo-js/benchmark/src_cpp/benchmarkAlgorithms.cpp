#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "indigo.h"

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
	for (i = 0; i < loopCount; ++i)
	{		
		//printf("Smiles: %s\n", smiles);
		//indigoClean2d(mol);
		//const char* molData = indigoMolfile(mol);
		//printf("Mol Data after clean 2D: \n%s\n", molData);
		if (mol2)
			indigoFree(mol2);
		int mol2 = indigoLoadMoleculeFromString(smiles);
		//const char* molData = indigoMolfile(mol2);
		//printf("Mol Data before layout: %d/%d %s\n%s\n", i, loopCount, smiles, molData);
		ret = indigoLayout(mol2);
		//const char* molData2 = indigoMolfile(mol2);
		//printf("Mol Data after layout: %d/%d\n%s\n", i, loopCount, molData2);		
		/*
		if (!ret)
			return 0;		
		*/
	}
	free(smiles);
	return ret;
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

int main(int argc, char *argv[])
{
	int loopCount = 1;
	int tCanoSmiles = -1, tSSSRCount = -1, tLayout = -1, tSaveCml = -1, tSaveMol = -1, tFindTautomer = -1;
	clock_t tStart, tEnd;
	if (argc < 2)
    {
        printf("You must specified the source MOL file.\n");
		return -1;
    }
	if (argc >= 3)
	{
		loopCount = atoi(argv[2]);
	}
	
	indigoSetErrorHandler(onError, 0);
		
	char* fileName = argv[1];
		
	int mol = indigoLoadMoleculeFromFile(fileName);	
	//int mol = indigoLoadMoleculeFromString(fileName);
	
	// Canonical smiles
	tStart = clock();
	const char* smiles = canonicalSmiles(mol, loopCount);
	if (!smiles)
		printf("Canonicalize SMILES failed!\n");
	else
	{
		tEnd = clock();		
		tCanoSmiles = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
		printf("Canonicalized SMILES: %s\n", smiles);
	}	
		
	// Auto layout
	//mol = indigoLoadMoleculeFromString(smiles);
	tStart = clock();
	int layoutRet = layoutMol(mol, loopCount);
	/*
	if (!layoutRet)
		printf("Layout failed!\n");
	else
	*/
	{
		tEnd = clock();		
		tLayout = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
	}	
	
	// SSSR count
	tStart = clock();
	int count = sssrCount(mol, loopCount);
	if (count < 0)
		printf("SSSR count failed!\n");
	else
	{
		tEnd = clock();		
		tSSSRCount = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
		printf("SSSR count: %d\n", count);
	}
	
	// find Tautomers
	tStart = clock();
	int iter = findTautomers(mol, loopCount);
	if (iter < 0)
		printf("Tautomer searching failed!\n");
	else
	{
		tEnd = clock();		
		tFindTautomer = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
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
			}
		}
		indigoFree(iter);
	}
	
	// Save to CML
	tStart = clock();
	const char* cml = saveToCml(mol, loopCount);
	if (!cml)
		printf("Save CML failed!\n");
	else
	{
		tEnd = clock();				
		tSaveCml = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
		printf("CML:\n%s\n", cml);
	}	
	
	// Save to MOL
	tStart = clock();
	const char* molData = saveToMol(mol, loopCount);
	if (!molData)
		printf("Save MOL failed!\n");
	else
	{
		tEnd = clock();				
		tSaveMol = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
		printf("MOL:\n%s\n", molData);
	}
	
	// Summary
	printf("============== Benchmark Done (Loop: %d) ====================\nCanonicalize SMILES: %dms\nSSSR Count: %dms\nTautomer: %dms\nLayout: %dms\nSave CML: %dms\nSave MOL: %dms\n",
		loopCount, tCanoSmiles, tSSSRCount, tFindTautomer, tLayout, tSaveCml, tSaveMol);
	
	indigoFree(mol);		
		
	return 0;
}