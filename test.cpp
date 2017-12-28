#include <stdio.h>
#include <sqlite3.h>
#include "dbfunctions.h"


int createDatabase()
{
    sqlite3 *db;
    char *Error = 0;
    int dbrc;

    dbrc = sqlite3_open("data.db", &db);

    if (dbrc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);
}
