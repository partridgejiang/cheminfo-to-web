/**
 *
 *  In this c file, function molToInchiJson is provided to convert MOL format text data to Inchi.
 *  To simplify the JavaScript-C code commnunication, return value is a JSON string containing fields
 *  {success, inchi, auxInfo, message} (mapped from szInChI, szAuxInfo and szMessage from inchi_Output).
 * 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inchi-src/INCHI-1-SRC/INCHI_BASE/src/inchi_api.h"
#include "inchi_js_utils.h"

char* _concreateStr(const char* str)
{
    if (str)
        return str;
    else
        return "";
}

int _safeStrLen(const char* str)
{
    if (str)
        return strlen(_concreateStr(str));
    else
        return 0;
}

char* molToInchiJson(char* molText, char* options)
{
    /*InchiResultDetail result;*/
    char* sSuccess;

    /* convert mol text to inchi */
    inchi_Output iout, *inchiResult = &iout;
    memset( inchiResult, 0, sizeof(*inchiResult) );

    int err = MakeINCHIFromMolfileText(molText, options, inchiResult);
    if ( err==mol2inchi_Ret_ERROR        ||
         err==mol2inchi_Ret_ERROR_get    ||
         err==mol2inchi_Ret_ERROR_comp    )
    {
        sSuccess = "false";
    }
    else
    {
        sSuccess = "true";
        /*
        if (inchiResult->szInChI)
        {
            result.inchi = malloc(strlen(inchiResult->szInChI) + 1);
            strcpy(result.inchi, inchiResult->szInChI);
        }
        if (inchiResult->szAuxInfo)
        {
            result.auxInfo = malloc(strlen(inchiResult->szAuxInfo) + 1);
        }

        result.message = malloc(strlen(inchiResult->szMessage) + 1);

        strcpy(result.auxInfo, inchiResult->szAuxInfo);
        strcpy(result.message, inchiResult->szMessage);
        */
    }

    /* Turn into JSON */
    int strSize = _safeStrLen(inchiResult->szInChI) + _safeStrLen(inchiResult->szAuxInfo) + _safeStrLen(inchiResult->szMessage) + _safeStrLen(sSuccess)
        + _safeStrLen("{'inchi':'','auxInfo':'','message':'','success':''}") + 1;
    /* debug */
    /*
    printf("strSize: %d\n{\"inchi\":\"%s\",\"auxInfo\":\"%s\",\"message\":\"%s\",\"success\":\"%s\"}",
             strSize, result.inchi, result.auxInfo, result.message, result.success);
    */

    char* sResult = (char*)malloc(strSize);
    snprintf(sResult, strSize,
             "{\"inchi\":\"%s\",\"auxInfo\":\"%s\",\"message\":\"%s\",\"success\":\"%s\"}",
             _concreateStr(inchiResult->szInChI), _concreateStr(inchiResult->szAuxInfo), _concreateStr(inchiResult->szMessage),
             _concreateStr(sSuccess));

    /* Reset output data structure */
    FreeINCHI ( inchiResult );

    return sResult;
}

char* getInChIKeyJson(char* inchiSource, int xtra1, int xtra2)
{
	char* sInChIKey = (char*)malloc(28);
	char* sXtra1 = (char*)malloc(65);
	char* sXtra2 = (char*)malloc(65);;
	
	// memset(sInChIKey, 0, sizeof(*sInChIKey));
	// memset(sXtra1, 0, sizeof(*sXtra1));
	// memset(sXtra2, 0, sizeof(*sXtra1));
	
	int rawResult = GetINCHIKeyFromINCHI(inchiSource, xtra1, xtra2, sInChIKey, sXtra1, sXtra2);
	
	/* Turn into JSON */
	char* sSuccess;		
	if (rawResult == INCHIKEY_OK)
	{
		sSuccess = "true";		
	}
	else
	{
		sSuccess = "false";						
	}
	int strSize = _safeStrLen(sInChIKey) + _safeStrLen(sXtra1) + _safeStrLen(sXtra2) + _safeStrLen(sSuccess)
			+ _safeStrLen("{'inchiKey':'','xtra1':'','xtra2':'','success':'','errorCode':###}") + 1;
	    
	char* sResult = (char*)malloc(strSize);
	
	snprintf(sResult, strSize, "{\"inchiKey\":\"%s\",\"xtra1\":\"%s\",\"xtra2\":\"%s\",\"success\":\"%s\",\"errorCode\":%d}",
		_concreateStr(sInChIKey), _concreateStr(sXtra1), _concreateStr(sXtra2), sSuccess, rawResult);
		
	free(sInChIKey);
	free(sXtra1);
	free(sXtra2);
	
	return sResult;
}
