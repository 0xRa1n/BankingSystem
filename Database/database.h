#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
// exports the variable dbConnection with the value MYSQL* inside the function connectToDatabase
extern MYSQL* dbConnection;
int connectToDatabase();

#endif
