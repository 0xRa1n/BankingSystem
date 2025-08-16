#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>

// initialize database
#include "Database\database.h"

// functions
#include "Functions/bank.admin.h"
#include "Functions/bank.user.h"

using namespace std;

BankUser User; // initializes class BankUser to a variable User
BankAdmin Admin;  // initializes class BankAdmin to a variable Admin
void UserMenu() {
    int userSelection;
    cout << "1. Dashboard\n2. Deposit\n3. Withdraw\n4. Suspend account\n0. Exit\nSelect option (1/2/3/4/0): ";
    cin >> userSelection;

    switch (userSelection) {
    case 1:
        cout << "Under construction";
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "Invalid selection";
        break;
    }
}

void AdminMenu() {
    int userSelection;
    cout << "1. Register User\n2. Dashboard\n3. Terminate account\n0. Exit\nSelect option (1/2/3/0): ";
    cin >> userSelection;

    switch (userSelection) {
    case 1:
        Admin.registerUser();
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "Invalid selection";
        break;
    }
}

int main() {
    if (connectToDatabase() != 0) {
        cout << "Failed to connect to database.\n";
        return 1;
    }

    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (User.login(username, password, dbConnection)) {
        string query = "SELECT role FROM user WHERE username='" + username + "' && password='" + password + "'";
        if (mysql_query(dbConnection, query.c_str())) {
            cout << "Query Failed: " << mysql_error(dbConnection) << endl;
            return false;
        }

        MYSQL_RES* res = mysql_store_result(dbConnection);
        if (res == nullptr) {
            cout << "Failed to get result set: " << mysql_error(dbConnection) << endl;
            return false;
        }

        MYSQL_ROW row;
        string roleValue;
        while ((row = mysql_fetch_row(res)) != nullptr) {
            // row[0] is the first column value (char*), may be NULL if the value is NULL in DB
            roleValue = (row[0] != nullptr) ? string(row[0]) : "";
        }

        mysql_free_result(res);
        system("cls");
        for (;;) { // this serves the same purpose as while(true)
            if (roleValue == "admin") {
                AdminMenu();
            }
            else {
                UserMenu();
            }
        }
    }
    else {
        cout << "Invalid credentials.";
        return 1;
    }
}
