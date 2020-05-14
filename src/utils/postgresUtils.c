#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "../../include/postgresUtils.h"

void cleanup(PGconn *conn) {
    PQfinish(conn);
}

char * getQueryResult(int* hasError){
    PGconn *conn = PQconnectdb("dbname =afinitiTest user =fita password =atif hostaddr = 127.0.0.1 port = 5432");

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        cleanup(conn);
        * hasError = 1;
        return "NO VALUE\n";
    }

    PGresult *res = PQexec(conn, "SELECT signalvalue from \"snmpSignals\" ORDER BY time DESC LIMIT 1");    
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("No signal found\n");        
        PQclear(res);
        cleanup(conn);
        * hasError = 1;
        return "NO VALUE\n";
    }    
    
    int rows = PQntuples(res);

    char* result = PQgetvalue(res,0,0);
    
    PQclear(res);
    PQfinish(conn); 

    return result;    
}