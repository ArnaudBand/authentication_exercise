#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "auth.h"
#include <termios.h>
#include <unistd.h>

using namespace std;

// Function to get hidden password input
string getHiddenPassword() {
    string password;
    char ch;
    struct termios oldt, newt;

    // Turn off terminal echo
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO; // Disable echoing characters
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read password one character at a time
    while ((ch = getchar()) != '\n' && ch != EOF) {
        password += ch;
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << endl; // Move to a new line after input

    return password;
}


// Function to encode a string in Base64
string base64Encode(const string& data) {
    const string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    string encoded;
    int val = 0, valb = -6;

    for (unsigned char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (encoded.size() % 4) encoded.push_back('=');
    return encoded;
}
// Function to get hidden password input
// string getHiddenPassword() {
//     string password;
//     char ch;
//     struct termios oldt, newt;

//     // Turn off terminal echo
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;
//     newt.c_lflag &= ~ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);

//     // Read password
//     while ((ch = getchar()) != '\n' && ch != EOF) {
//         password += ch;
//     }

//     // Restore terminal echo
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     cout << endl;

//     return password;
// }

// Function to register a new user
void registerUser() {
    string username, password;

    cout << "Register a new account\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    password = getHiddenPassword(); // Use hidden password input

    string encodedPassword = base64Encode(password); // Encode password

    // Open the file in append mode to add new credentials
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << encodedPassword << "\n";
        file.close();
        cout << "Registration successful! You can now log in.\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
}

// Function to log in a user
bool loginUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    password = getHiddenPassword(); // Use hidden password input

    return validateCredentials(username, password);
}

// Function to validate user credentials against stored data
bool validateCredentials(const string& username, const string& password) {
    string storedUsername, storedPassword;
    string encodedPassword = base64Encode(password); // Encode entered password for comparison

    // Open the file in read mode to verify credentials
    ifstream file("users.txt");
    if (file.is_open()) {
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == encodedPassword) {
                file.close();
                return true; // Match found
            }
        }
        file.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }

    return false; // No match found
}
