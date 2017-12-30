#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "select.h"


Question::Question()
{
    this->id = 0;
    this->ques = NULL;
    this->a = NULL;
    this->b = NULL;
    this->c = NULL;
    this->d = NULL;
    this->correct = NULL;
}
Question::Question(int id, char *question, char *a, char *b, char *c, char *d,
                   char *correct)
{
    this->id = id;
    this->ques = question;
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->correct = correct;
}

void Question::Print()
{
    if (id == 0)
        printf("Nu a fost returnata nici o intrebare.\n");
    else
        printf("%d.%s\nA:%s\nB:%s\nC:%s\nD:%s\n\n\n", id, ques, a, b, c, d);
}
    
    char* Question::Prepare()
    {
         
         char *question=ques;
        strcat(question,"~A.");
        strcat(question,a);
        strcat(question,"~B.");
         strcat(question,b);
        strcat(question,"~C.");
         strcat(question,c);
        strcat(question,"~D.");
         strcat(question,d);
         return question;
        }
        
char Question::Verify(char ans)
{
    if(this->correct[0]==ans)
    return 'Y';
    else
    return 'N';
}

sqlite3 *openDatabase()
{
    int rc;
    sqlite3 *db;
    /* Open database */
    rc = sqlite3_open("data.db", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    else
    {
        return db;
    }
}

Question selectDatabase(int number, sqlite3 *db)
{

    char *zErrMsg = 0;
    int rc;

    /* Create SQL statement */
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT * from QUESTIONS where ID=$1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, number);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        int id;
        char *question, *a, *b, *c, *d;
        char *correct;
        id = sqlite3_column_int(stmt, 0);
        question = (char *)sqlite3_column_text(stmt, 1);
        a = (char *)sqlite3_column_text(stmt, 2);
        b = (char *)sqlite3_column_text(stmt, 3);
        c = (char *)sqlite3_column_text(stmt, 4);
        d = (char *)sqlite3_column_text(stmt, 5);
        correct = (char *)sqlite3_column_text(stmt, 6);
        Question q(id, question, a, b, c, d, correct);
        return q;
    }
    else
    {
        Question q;
        return q;
    }

    sqlite3_finalize(stmt);
}

void closeDatabase(sqlite3 *db)
{
    sqlite3_close(db);
}

/*
int main(int argc, char *argv[])
{
    sqlite3 *db = openDatabase();
    Question q = selectDatabase(1, db);
    q.Print();
    closeDatabase(db);
    return 0;
}*/