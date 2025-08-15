#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>

// initialize database
#include "..\Database\database.h"

using namespace std;
class BankAdmin {
public:
    // admin
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

                string query = "INSERT INTO user VALUES (" + to_string(accountNumber) + ", \"" + name + "\", \"" + username + "\", \"" + password + "\", '0', \"" + dateCreated + "\", \"" + role + "\")";

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