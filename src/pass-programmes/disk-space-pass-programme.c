#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../include/diskSpaceUtils.h"


int main(int argc, char *argv[])
{
    if (argc<3){ //  too few arguments
        return 1;
    }

    const char baseOID[] = ".1.3.6.1.4.1.53864.11";
    const char scalarOID[] = ".1.3.6.1.4.1.53864.11.0";
    const char responseType[] = "integer";

    // if snmpgetnext request
    if (strcmp(argv[1], "-n") == 0)
    {
        if (strcmp(argv[2], baseOID) == 0)
        {
            long size_in_bytes = getSize("/var/log");
            /*  Next OID will be .1.3.6.1.4.1.53864.11.0 */
            printf("%s.0\n", argv[2]);
            printf("%s\n",responseType);
            printf("%li\n", size_in_bytes);
            return 0;
        }
        /*  NO OID after .1.3.6.1.4.1.53864.11.0 */
        return 0;
        
    }

    // if snmpget request
    if (strcmp(argv[2], scalarOID) == 0)
    {
        long size_in_bytes = getSize("/var/log");
        printf("%s\n", argv[2]);
        printf("%s\n",responseType);
        printf("%li\n", size_in_bytes);
        return 0;
    }
    
    return 0;
}