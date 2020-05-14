#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <libpq-fe.h>
#include "../../include/postgresUtils.h"


int main(int argc, char *argv[])
{
    if (argc<3){ //  too few arguments
        return 1;
    }

    int * hasError = malloc(sizeof(int));
    * hasError = 0;
    const char baseOID[] = ".1.3.6.1.4.1.53864.12";
    const char scalarOID[] = ".1.3.6.1.4.1.53864.12.0";
    const char responseType[] = "string";

    // if snmpgetnext request
    if (strcmp(argv[1], "-n") == 0)
    {
        if (strcmp(argv[2], baseOID) == 0)
        {
            
            char * signalValue = getQueryResult(hasError);
            if (*hasError)
                return 1;

            /*  Next OID will be .1.3.6.1.4.1.53864.12.0 */
            printf("%s.0\n", argv[2]);
            printf("%s\n",responseType);
            printf("%s\n", signalValue);
            return 0;
        }
        /*  NO OID after .1.3.6.1.4.1.53864.12.0 */
        return 0;
        
    }

    // if snmpget request
    if (strcmp(argv[2], scalarOID) == 0)
    {
        char * signalValue = getQueryResult(hasError);
        if (*hasError)
            return 1;

        printf("%s\n", argv[2]);
        printf("%s\n",responseType);
        printf("%s\n", signalValue);
        return 0;
    }
    
    return 0;
}