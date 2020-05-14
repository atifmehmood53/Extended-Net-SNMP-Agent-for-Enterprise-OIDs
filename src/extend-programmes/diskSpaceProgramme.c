#include <stdio.h>               
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../include/diskSpaceUtils.h"

int main(int argc, char *argv[]){
    long size= getSize();
    printf("%ld\n", size);
    return 0;
}