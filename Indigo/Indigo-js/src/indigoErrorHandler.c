#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h>
#include "indigo.h"

void indigoOnError(const char *message, void *context)
{
   /*
   fflush(stdout);
   fprintf(stderr, "%s\n", message);
   fflush(stderr);
   exit(-1);
   */
   EM_ASM_({
     Module.printErr('[Indigo Error] '  + $0);
   }, message);
}

int main()
{
	indigoSetErrorHandler(indigoOnError, 0);
	printf("Indigo Loaded");
}