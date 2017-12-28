#ifndef DBFUNCTIONS_H
#define DBFUNCTIONS_H
#include <sqlite3.h>

int createDatabase();
int callback(void *NotUsed, int argc, char **argv, char **azColName);
sqlite3 * openDatabase();
int createTable(sqlite3 *db);
void closeDatabase(sqlite3 *db);
int insertRow(const char *sql, sqlite3 *db);
int populateDatabase(sqlite3 *db);

#endif
