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

int nameToMol(char* molName, int loopCount)
{
	int i, mol;
	for (i = 0; i < loopCount; ++i)
	{
		mol = indigoNameToStructure(molName, "");	
		//mol = indigoLoadMoleculeFromString(molName);
		if (!mol)
			return 0;
	}
	return mol;
}

int main(int argc, char *argv[])
{
	int loopCount = 1;
	int tNameToMol = -1;
	clock_t tStart, tEnd;
	if (argc < 2)
    {
        printf("You must specified the source molecule name.\n");
		return -1;
    }
	if (argc >= 3)
	{
		loopCount = atoi(argv[2]);
	}
	
	indigoSetErrorHandler(onError, 0);
		
	char* molName = argv[1];
	
	// mol name to structure
	tStart = clock();
	int mol = nameToMol(molName, loopCount);
	if (!mol)
		printf("Name to molecule failed!\n");
	else
	{
		tEnd = clock();
		indigoLayout(mol);
		const char* molData = indigoMolfile(mol);
		tNameToMol = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
		printf("MOL Data: \n%s\n", molData);
	}	
	printf("============== Benchmark Done (Loop: %d) ====================\nName to structure: %dms\n",
		loopCount, tNameToMol);	
	
	indigoFree(mol);		
		
	return 0;
}