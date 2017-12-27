#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *Error = 0;
   int dbrc;
   const char * sql;

   /* Open database */
   dbrc = sqlite3_open("data.db", &db);
   
   if( dbrc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE QUESTIONS("  \
         "ID INT  NOT NULL," \
         "QUESTION          TEXT    NOT NULL," \
         "A        TEXT     NOT NULL," \
         "B        TEXT     NOT NULL," \
         "C        TEXT     NOT NULL," \
         "D        TEXT     NOT NULL," \
         "CORRECT  CHAR(1) );";

   /* Execute SQL statement */
   dbrc = sqlite3_exec(db, sql, callback, 0, &Error);
   
   if( dbrc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", Error);
      sqlite3_free(Error);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
