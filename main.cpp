#include <mysql.h>
#include <iostream>
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
    for (;;) { // this serves the same purpose as while(true)
        Bank.mainMenu();
    }
    return 0;
}
