#include <mysql.h>
#include <iostream>
#include <cstdlib>
#include <string>
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

        if (userSelection == 1) {
            // if (checkPIN()){
            //     cout << "Successfully validated PIN.\n";
            // }
        }
        else if (userSelection == 0) {
            cout << "Exiting program";
            exit(0);
        }
        else {
            cout << "Invalid selection. Try again";
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
};

int main() {
    #define SERVER "localhost"
    #define USER "root"
    #define PASSWORD "arceus0p" //,807KBre-,Ri
    #define DATABASE "userinformation"
    #define PORT 4307

    MYSQL* connect;
    connect = mysql_init(NULL);

    if (!connect) {
        cout << "MySQL Initialization Failed\n";
        return 1;
    }

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, PORT, NULL, 0);
    if (connect) {
        cout << "Connection Succeeded\n";
    }
    else {
        cout << "Connection Failed\n";
        return 1;
    }

    Bank Bank; // initializes class Bank to a variable Bank
    if (Bank.login(connect)) {
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
