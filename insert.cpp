#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "dbfunctions.h"


int insertRow(const char *sql, sqlite3 *db)
{
    char *Error = 0;
    int dbrc;

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
    return 0;
}

int populateDatabase(sqlite3 *db)
{
 const char *sql;
 /* Create SQL statement */
    sql = "INSERT INTO QUESTIONS (ID,QUESTION,A,B,C,D,CORRECT) "
          "VALUES (1, 'Cel mai inalt varf muntos din Romania?','Moldoveanu', 'Parang', 'Ineu', 'Omu', 'A' ); ";
   insertRow(sql,db);
    sql = "INSERT INTO QUESTIONS (ID,QUESTION,A,B,C,D,CORRECT) "
          "VALUES (2, 'Ultimul rege al Romaniei?','Carol I', 'Carol II', 'Mihai', 'Ferdinand', 'C' ); ";    
    insertRow(sql,db);
    sql = "INSERT INTO QUESTIONS (ID,QUESTION,A,B,C,D,CORRECT) "
          "VALUES (3, 'Unele luni au 31 de zile.Unele luni au 30 de zile.Cate luni au 28 de zile?','12', '1', '6', '2', 'A' ); ";    
    insertRow(sql,db);
    sql = "INSERT INTO QUESTIONS (ID,QUESTION,A,B,C,D,CORRECT) "
          "VALUES (4, 'Portugheza este vorbita in?','Columbia', 'Argentina', 'Ecuador', 'Brazilia', 'D' ); ";    
    insertRow(sql,db);
    sql = "INSERT INTO QUESTIONS (ID,QUESTION,A,B,C,D,CORRECT) "
          "VALUES (5, 'Cati dinti are o persoana adulta?','28', '42', '32', '34', 'C' ); ";    
    insertRow(sql,db);
   return 0;   
}


