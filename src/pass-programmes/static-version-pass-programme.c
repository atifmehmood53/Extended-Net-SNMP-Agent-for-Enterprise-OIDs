#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc<3){ //  too few arguments
        return 1;
    }

    const char baseOID[] = ".1.3.6.1.4.1.53864.10";
    const char scalarOID[] = ".1.3.6.1.4.1.53864.10.0";
    const char responseType[] = "string\n";
    const char response[] = "1.6.1\n";

    // if snmpgetnext request
    if (strcmp(argv[1], "-n") == 0)
    {
        if (strcmp(argv[2], baseOID) == 0)
        {
            
            /*  Next OID will be .1.3.6.1.4.1.53864.10.0 */
            printf("%s.0\n", argv[2]);
            printf(responseType);
            printf("%s", response);
            return 0;
        }
        /*  NO OID after .1.3.6.1.4.1.53864.10.0 */
        return 0;
        
    }

    // if snmpget request
    if (strcmp(argv[2], scalarOID) == 0)
    {
        printf("%s\n", argv[2]);
        printf("%s",responseType);
        printf("%s", response);
        return 0;
    }
    
    return 0;
}