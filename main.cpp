#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>

#include "Database\database.h"
using namespace std;

class Bank {
public:
    /* to-do: change this from checkPIN to updatePIN */

    // bool checkPIN(){
    //     int inputPIN;
    //     int correctPIN = 1234;

    //     for(;;){
    //         cout << "Enter PIN: ";
    //         cin >> inputPIN;

    //         if (inputPIN != correctPIN){
    //             string message = "Not correct PIN!\n";
    //             cout << message;
    //         } else {
    //             return true;
    //         }
    //     }
    // }

    void mainMenu() {
        int userSelection;
        cout << "1. Register User\n2. Dashboard\n3. Deposit\n4. Withdraw\n5. Suspend account\n0. Exit\nSelect option (1/2/3/4/5/0): ";
        cin >> userSelection;

        switch (userSelection) {
        case 1:
            registerUser();
            break;
        case 0:
            exit(0);
            break;
        default:
            cout << "Invalid selection";
            break;
        }
    }

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

    bool registerUser() {
        string name, username, password, role;
        for (;;) {
            // ask the user for username, password, and role
            cout << "What is the user's name? ";
            cin >> name;
            cout << "Enter the username you want to register: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            cout << "What is the user's role? ";
            cin >> role;

            if (role != "admin" && role != "user") {
                cout << "Invalid role!" << endl;
            }
            else {
                // generate random 6-digit numbers
                srand(time(NULL));  // seed rand
                int accountNumber = 100000 + rand() % 900000;

                // time
                time_t timestamp = time(NULL);
                struct tm datetime;
                localtime_s(&datetime, &timestamp);
                char dateCreated[50];
                strftime(dateCreated, sizeof(dateCreated), "%m/%d/%y", &datetime);

                string query = "INSERT INTO user VALUES (" + to_string(accountNumber) + ", \"" + name +"\", \"" + username + "\", \"" + password + "\", '0', \"" + dateCreated + "\", \"" + role + "\")";

                if (mysql_query(dbConnection, query.c_str())) {
                    cout << "Query Failed: " << mysql_error(dbConnection) << endl;
                    return 1;
                }

                cout << "User " + username + " was successfully registered." << endl;
                this_thread::sleep_for(chrono::seconds(3));
                return 0;
            }
        }
    }
};

int main() {
    if (connectToDatabase() != 0) {
        cout << "Failed to connect to database.\n";
        return 1;
    }

    // to-do: make a statement that only admins can log-in
    Bank Bank; // initializes class Bank to a variable Bank
    if (Bank.login(dbConnection)) {
        system("cls");
        for (;;) { // this serves the same purpose as while(true)
            Bank.mainMenu();
        }
    }
    else {
        cout << "Invalid credentials.";
        return 1;
    }
}
