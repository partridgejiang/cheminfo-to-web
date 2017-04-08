#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indigo.h"


void onError(const char *message, void *context)
{
   fflush(stdout);
   fprintf(stderr, "%s\n", message);
   fflush(stderr);
   exit(-1);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
    {
        printf("You must specified the source MOL file.\n");
		return -1;
    }
	
	indigoSetErrorHandler(onError, 0);
	
	char* fileName = argv[1];
	//int mol = indigoLoadMoleculeFromFile(fileName);
	
	int mol = indigoLoadMoleculeFromString(fileName);
	const char *res = indigoCanonicalSmiles(mol);	
    printf("SMILES: %s\n", res);
	
	indigoSetOption("smart-layout", "true");
	indigoLayout(mol);
	
	/*
	const char *inchi = indigoInchi(mol);
	printf("InChI:\n%s\n", inchi);
	*/
	
	const char *cml = indigoCml(mol);	
    printf("CML:\n%s\n", cml);
	
	const char *molData = indigoMolfile(mol);	
    printf("MOL:\n%s\n", molData);
	
	/*
	const char* cdXml = indigoCdxml(mol);
	printf("CDXML:\%s\n", cdXml);
	*/
	printf("SSSR Count: %d\n", indigoCountSSSR(mol));
	
	indigoFree(mol);
		
		
	return 0;
}