#include <iostream>
#include <mysql.h>
#include "database.h"

using namespace std;

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "arceus0p" //,807KBre-,Ri
#define DATABASE "userinformation"
#define PORT 4307

MYSQL* dbConnection = nullptr; // global definition

int connectToDatabase() {
    dbConnection = mysql_init(NULL);
    if (!dbConnection) {
        cout << "MySQL Initialization Failed\n";
        return 1;
    }

    dbConnection = mysql_real_connect(dbConnection, SERVER, USER, PASSWORD, DATABASE, PORT, NULL, 0);
    if (dbConnection) {
        cout << "Connection Succeeded\n";
        return 0;  // success
    }
    else {
        cout << "Connection Failed\n";
        return 1;  // failure
    }
}
