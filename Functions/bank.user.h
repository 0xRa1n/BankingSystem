#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>

// initialize database
#include "..\Database\database.h"

using namespace std;
class BankUser {
public:
    // user
    bool login(MYSQL* conn) {
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        string query = "SELECT COUNT(*) FROM user WHERE username = '" + username + "' AND password = '" + password + "'";
        if (mysql_query(conn, query.c_str())) {
            cout << "Query Failed: " << mysql_error(conn) << endl;
            return false;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cout << "Could not get result set: " << mysql_error(conn) << endl;
            return false;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        bool loginSuccess = row && stoi(row[0]) > 0;
        mysql_free_result(res);

        return loginSuccess;
    }
};