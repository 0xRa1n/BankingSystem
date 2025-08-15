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

void mainMenu() {
    BankAdmin Admin;
    int userSelection;
    cout << "1. Register User\n2. Dashboard\n3. Deposit\n4. Withdraw\n5. Suspend account\n0. Exit\nSelect option (1/2/3/4/5/0): ";
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

    // to-do: make a statement that only admins can log-in
    BankUser User; // initializes class BankUser to a variable User
    if (User.login(dbConnection)) {
        system("cls");
        for (;;) { // this serves the same purpose as while(true)
            mainMenu();
        }
    }
    else {
        cout << "Invalid credentials.";
        return 1;
    }
}
