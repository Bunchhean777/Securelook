/*
    # SecureLock Admin System Management
*/

/*
    + This project is a simple authentication system written in C++.
    It provides secure password management for an admin user.
    Features include creating a password, changing the password,
    and logging in with the password.
    + The password is stored in a binary file for security.
*/

#include <bits/stdc++.h> // using this sigle header file it's can be include all standard bibaries
#include <conio.h>

#define MAX 50
#define RE  "\033[0m"       /* Reset */
#define R   "\033[31m"      /* Red */
#define G   "\033[32m"      /* Green */

using namespace std;

class Record {
private:
    int userID;
    char userName[MAX],userSex[5],password[MAX]; // here you can add email or phone number

public:
    void create();
    void changePass();
    void login();
    void verify();

}record[MAX]; // declare gobal object from class record


// Verify password use to verify before you add to your features 
void Record::verify() {

    bool success = false;
    int m = 0;
    char pw[MAX], data[MAX];
    int attempts = 3;

    ifstream read_file("pw.bin", ios::in | ios::binary);

    read_file.read((char*)data, sizeof(data));

    for ( int i = 0; i < attempts; ++i) {

        cout << endl << "\t\t=> need enter password to verify: ";
        m = 0;
        do {
            pw[m] = getch();
            if ((pw[m] != '\r') && (pw[m] != '\b')) {
                cout << "*";
            }
            m++;
        } while (pw[m - 1] != '\r');
        pw[m - 1] = '\0';

        if (strcmp(pw, data) == 0) {

            cout << endl << G << "\n\t\t\tSuccessful to Verify! \n" << RE;
            break;
            read_file.close();

        } else {

            int left = attempts - i - 1;

            if (left > 0) {
                cout << R << "\n\t\tWrong password. You have " << left 
                    << " attempt(s) left.\n" << RE;
            } else {
                cout << R << "\n\t\tProgram is Exiting...\n" << RE;
                read_file.close();
                exit(0);
            }
        }
    }
    read_file.close();
}

/*
    In this section you can create your password when you don't have password. It's will neet you to create a new once.
*/

// user create password
void Record::create() {
    char pw[MAX];
    int m = 0;

    ofstream write_password("pw.bin", ios::out | ios::binary | ios::app);

    if (!write_password.is_open()) {
        cerr << "\nError: Unable to open file.\n" << endl;
        return;
    }

    cout << "=> Create password: ";
    do {
        pw[m] = getch();
        if ((pw[m] != '\r') && (pw[m] != '\b')) {
            cout << "*";
        }
        m++;
    } while (pw[m - 1] != '\r');
    pw[m - 1] = '\0';

    write_password.write((char*)pw, strlen(pw) + 1);
    write_password.close();

    cout << G << "\n Password has been created successfully!\n" << RE;
}


// user change password.
void Record::changePass() {

    int m = 0, incorrect = 0;
    char pw[MAX], old_password[MAX], new_password[MAX];
    ifstream read_password;
    ofstream write_password;

    read_password.open("pw.bin", ios::in | ios::binary);
    if (!read_password.is_open()) {
        cout << R << "\n\t\tNo existing password found!\n" << RE;
        return;
    }
    read_password.read((char*)old_password, sizeof(old_password));

    cout << "\n\t\t=> enter your new password : ";
    do {
        new_password[m] = getch();
        if ((new_password[m] != '\r') && (new_password[m] != '\b')) {
            cout << "*";
        }
        m++;
    } while (new_password[m - 1] != '\r');
    new_password[m - 1] = '\0';
    m = 0;

    while (incorrect < 3) {
        cout << "\n\t\t=> enter your old password : ";
        do {
            pw[m] = getch();
            if ((pw[m] != '\r') && (pw[m] != '\b')) {
                cout << "*";
            }
            m++;
        } while (pw[m - 1] != '\r');
        pw[m - 1] = '\0';

        if (strcmp(pw, old_password) == 0) {
            read_password.close();
            write_password.open("pw.bin", ios::binary | ios::out);
            write_password.write((char*)new_password, strlen(new_password) + 1);
            write_password.close();
            cout << endl << G << "\n\t\tyour password has been changed successfully! \n" << RE;
            return;
        } else {
            if (incorrect == 2) {
                cout << endl << R << "\n\t\tyou have entered the wrong password 3 times. Program is Exiting...\n" << RE;
                read_password.close();
                exit(0);
            }
            cout << endl << R << "\n\t\tIncorrect password, Try again!\n" << RE;
            m = 0;
            ++incorrect;
        }
    }
    read_password.close();
}


// user login.
void Record::login() {

    char pw[MAX], data[MAX];
    bool success = false;
    int m = 0, attempts = 3;

    ifstream read_file("pw.bin", ios::in | ios::binary);
    
    if (!read_file.is_open()) {
        record[0].create();
        return;
    }

    read_file.read((char*)data, sizeof(data));

    for ( int i = 0; i < attempts; ++i) {

        cout << endl << "\t\t=> enter password to login: ";
        m = 0;
        do {
            pw[m] = getch();
            if ((pw[m] != '\r') && (pw[m] != '\b')) {
                cout << "*";
            }
            m++;
        } while (pw[m - 1] != '\r');
        pw[m - 1] = '\0';

        if (strcmp(pw, data) == 0) {

            cout << endl << G << "\n\t\t\tlogin successful! \n" << RE;
            getch();
            read_file.close();
            return;

        } else {

            int left = attempts - i - 1;

            if (left > 0) {
                cout << R << "\n\t\tWrong password. You have " << left 
                    << " attempt(s) left.\n" << RE;
            } else {
                cout << R << "\n\t\tProgram is Exiting...\n" << RE;
                read_file.close();
                exit(0);
            }
        }
    }
    read_file.close();
}


// Menu
void menu() {
    cout << "\n\n\t\t\t  A D M I N S  S Y S T E M  \n";
    cout << "\t\t-------------------------------------\n";
    cout << "\t\t| 1. Create Password                |\n";
    cout << "\t\t| 2. Change Password                |\n";
    cout << "\t\t| 3. Login                          |\n";
    cout << "\t\t| 4. Exit                           |\n";
    cout << "\t\t-------------------------------------\n";
    cout << "\t\tSelect your option (1-4): ";
}

int main() {

    int i = 0;
    record[i].login();
    return  0;
    
}
