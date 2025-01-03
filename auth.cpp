#include <iostream>
#include <fstream>
#include "auth.h"


using namespace std;

void registerUser() {

  string username, password;

  cout << "Register a new account" << endl;
  cout << "Enter a username: ";
  cin >> username;
  cout << "Enter a password: ";
  cin >> password;

  ofstream file("users.txt", ios::app);
  if (file.is_open()) {
    file << username << " " << password << endl;
    file.close();
    cout << "Account created successfully" << endl;
  } else {
    cout << "Error: Unable to open file" << endl;
  }
}

bool loginUser() {

  string username, password, u, p;

  cout << "Login to your account" << endl;
  cout << "Enter your username: ";
  cin >> username;
  cout << "Enter your password: ";
  cin >> password;

  return validateCredentials(username, password);
}

bool validateCredentials(const string& username, const string& password) {
    string storedUsername, storedPassword;

    // Open the file in read mode to verify credentials
    ifstream file("users.txt");
    if (file.is_open()) {
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
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