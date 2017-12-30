
#include <sqlite3.h>
class Question
{
  private:
    int id;
    char *ques, *a, *b, *c, *d;
    char *correct;

public:
    Question();
    Question(int id, char *question, char *a, char *b, char *c, char *d,
             char *correct);
    void Print();
    char* Prepare();
};


sqlite3 *openDatabase();
Question selectDatabase(int number, sqlite3 *db);
void closeDatabase(sqlite3 *db);