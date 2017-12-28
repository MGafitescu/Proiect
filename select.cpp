#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>

int selectDatabase(int number)
{
sqlite3 *db;
   char *zErrMsg = 0;
   int rc;


   /* Open database */
   rc = sqlite3_open("data.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }/* else {
      fprintf(stderr, "Opened database successfully\n");
   }*/

   /* Create SQL statement */
   sqlite3_stmt *stmt;
   sqlite3_prepare_v2(db, "SELECT * from QUESTIONS where ID=$1", -1, &stmt, NULL);                                       
   sqlite3_bind_int(stmt, 1, number);                                                                  
rc = sqlite3_step(stmt); 
if (rc == SQLITE_ROW) {
                int id;
               const unsigned char * question, *a, *b,*c,*d;
                const unsigned char *correct;
                id = sqlite3_column_int(stmt, 0);
                question  = sqlite3_column_text (stmt, 1);
                a  = sqlite3_column_text (stmt, 2);
                b  = sqlite3_column_text (stmt, 3);
                c  = sqlite3_column_text (stmt, 4);
                d  = sqlite3_column_text (stmt, 5);
                correct = sqlite3_column_text (stmt,6);
                printf ("%d.%s\nA:%s\nB:%s\nC:%s\nD:%s\n\n\n", id, question,a,b,c,d,correct);
            }
            else
            {
                printf("Statement didn't return any rows\n");
            }



sqlite3_finalize(stmt);
   

  
   
   
   sqlite3_close(db);
}

int main(int argc, char* argv[]) {
   selectDatabase(1);
   selectDatabase(3);
   return 0;
}