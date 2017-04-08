#include <stdio.h>
/**
  *  This is the code file that can be used to generate native benchmark EXE.
  *  The exeutable file accepts three parameters: the input MOL format file name, loop times and conversion option string,
  *  e.g. inchi_conv test.mol 100
  *  The total time of conversion to Inchi is counted and outputed.
  **/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../../inchi-src/INCHI-1-SRC/INCHI_BASE/src/inchi_api.h"

#define MOLMAXLINELEN 1000
#define MOLBUFSIZE 800000

/**************************************************/
/* Fgets which ensures single linefeed at the end */
char* fgets_lf( char* line, int line_len, FILE *f )
{
char *p=NULL, *q;

    /* Read from file */
    memset( line, 0, line_len );
    if ( NULL!=( p =fgets(line, line_len, f) ) &&
         NULL==strchr(p, '\n' ) )
    {
        char temp[64];
        /* bypass up to '\n' or up to end of file whichever comes first*/
        while ( NULL!=fgets(temp, sizeof(temp), f) &&
                NULL==strchr(temp, '\n') )
            ;
    }

    /*  fix CR CR LF line terminator. */
    if ( p )
    {
        if (q = strchr(line, '\r') )
        {
            q[0] = '\n';
            q[1] = '\0';
        }
    }

    return p;
}


/***************************************************************/
/* Read Molfile (SDFile segment) to text buffer                    */
/* Return 1 if got something, -1 if no room, otherwise 0        */
int get_next_molfile_as_text( FILE *f, char *buf, size_t buflen )
{
char *p=NULL, line[MOLMAXLINELEN];
size_t pos=0l, bufsize=0;
int empty = 1;

    while ( p=fgets_lf(line, MOLMAXLINELEN, f) )
    {
        size_t n = strlen(line);
        if ( n )
        {
            if ( empty )
                empty = 0;    /* Got something non-empty, do not mind the content */

            if ( buflen < pos + n -1 )
                return -1; /* buffer buf is too small */
            memcpy( buf + pos, line , n );
            pos+= n;
            /* Check if we at the end of Molfile segment */
            if ( line[0]=='$' && n>3 &&
                 line[1]=='$' && line[2]=='$' && line[3]=='$' )
                break;
        }
    }


    if ( empty )
        return 0;
    else
    {
        buf[pos] = '\0';
        return 1;
    }
}

int handleMolFile(char* fileName, int loopCount, char* options)
{
    int err;
    FILE* f = NULL;
    f = fopen(fileName, "rb");
    if (!f)  /* open file failed */
    {
        printf("Open input file failed: %s\n", fileName);
        return 0;
    }
    char* text = (char *) calloc( MOLBUFSIZE, sizeof(char) );
    if ( !text )
    {
        return 0;
    }
    err = get_next_molfile_as_text(f, text, MOLBUFSIZE);
    if (err <= 0)
    {
        printf("Illegal or empty mol file\n");
        return 0;
    }
    else
    {
        printf("Mol content:\n%s\n", text);

        /* convert mol text to inchi, in loop */
        inchi_Output iout, *result = &iout;
		
		err = MakeINCHIFromMolfileText(text, options, result);
		/* ensure the conversion can be successfully done */
		if ( err==mol2inchi_Ret_ERROR        ||
			 err==mol2inchi_Ret_ERROR_get    ||
			 err==mol2inchi_Ret_ERROR_comp    )
		{
			printf("Make inchi failed");
			return 0;
		}
		else
		{				
			/* Success, do nothing */
			/* printf("Convert %d: %s\n", i, result->szInChI); */
		}
		
		/* Then run the loop job */		
		clock_t tStart = clock();
		int i;
		for (i = 0; i < loopCount; ++i)
		{
			memset( result, 0, sizeof(*result) );
			MakeINCHIFromMolfileText(text, options, result);
			printf("Convert %d: %s\n", i, result->szInChI);
		}
		clock_t tEnd = clock();
		int execTime = (tEnd - tStart) * 1000 / CLOCKS_PER_SEC;
		/* Outout inchi */
		printf("Make InChi successful:\nInChi:%s\nAuxInfo:%s\nMessage:%s\nLog:%s\n",
			   result->szInChI, result->szAuxInfo, result->szMessage, result->szLog);
		/* Output benchmark info */		
		/* printf("Run %d times in %d ms.\nClock count: %d, clocks per sec: %d.\n", loopCount, execTime, tEnd - tStart, CLOCKS_PER_SEC); */
		printf("Run %d times in %d ms.\n", loopCount, execTime);

        /* Reset output data structure */
        FreeINCHI ( result );

        return 1;
    }
}

int main(int argc, char *argv[])
{
    char* fileName = NULL;
	char* convOptions = "";
	int loopCount = 1;
    /* the first argument should be the input mol file */
    if (argc < 2)
    {
        printf("You must specified the source MOL file.\n");
		return -1;
    }
    else
    {
        fileName = argv[1];
    }
	if (argc > 2)  /* the second argument should be the loop count */
	{
		loopCount = atoi(argv[2]);
	}
	if (argc > 3)  /* the third argument is conversion option string */
	{
		convOptions = argv[3];
	}	
	/* Now proceed */
	printf("Input mol file is: %s\n", fileName);
	handleMolFile(fileName, loopCount, convOptions);
    return 0;    
}
