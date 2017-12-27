#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    return 0;
}

int main(int argc, char *argv[])
{
    sqlite3 *db;
    char *Error = 0;
    int dbrc;
    const char *sql;

    /* Open database */
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

    /* Create SQL statement */
    sql = "INSERT INTO QUESTIONS (ID,QUESTION,A,B,C,D,CORRECT) "
          "VALUES (1, 'Cel mai inalt varf muntos din Romania?','Moldoveanu', 'Parang', 'Ineu', 'Omu', 'A' ); ";

    /* Execute SQL statement */
    dbrc = sqlite3_exec(db, sql, callback, 0, &Error);

    if (dbrc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", Error);
        sqlite3_free(Error);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}
