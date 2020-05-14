#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "../../include/postgresUtils.h"

int main() {
    int * hasError = malloc(sizeof(int));
    * hasError = 0;
    printf("%s",getQueryResult(hasError));
    return *hasError;
}