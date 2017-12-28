#include "dbfunctions.h"

int main()
{
     createDatabase();
     sqlite3 *db =openDatabase();
      createTable(db);
    populateDatabase(db);
    closeDatabase(db);
}