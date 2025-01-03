#ifndef AUTH_H
#define AUTH_H

#include <string>
using namespace std;

// Declare the authentication functions
void registerUser();
bool loginUser();
bool validateCredentials(const string& username, const string& password);

#endif // AUTH_H
