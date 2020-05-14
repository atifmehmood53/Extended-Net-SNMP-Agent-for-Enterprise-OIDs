#include <stdio.h>               
#include <stdlib.h>
#include <errno.h>
#include <string.h>

long getSize(){
    FILE *in;
    char tmp[4096]={'\0'};
    char cmd[128]={0x0};
    long total=0;
    sprintf(cmd,"du -sb /var/log  2>&1 | grep -oE '^\s*[0-9]+'");
    in=popen(cmd, "r");
    while(1){
            if(fgets(tmp,4095,in)!=NULL) {
                total+=atol(tmp);
            }else{
                if(feof(in)) break;
            }
    }
    pclose(in);
    return  total;
}
