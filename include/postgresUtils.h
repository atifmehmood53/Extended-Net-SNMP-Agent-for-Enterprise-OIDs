#ifndef POSTGRESUTILS_H
#define POSTGRESUTILS_H

void cleanup(PGconn *conn);

char * getQueryResult(int* hasError);

#endif