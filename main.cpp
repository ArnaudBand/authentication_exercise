#include <iostream>
#include "auth.h" // Include the header file

using namespace std;

int main() {
    int choice;

    cout << "Welcome to the Authentication System\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    cout << "Login successful! Welcome.\n";
                } else {
                    cout << "Invalid username or password. Please try again.\n";
                }
                break;
            case 3:
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please choose 1, 2, or 3.\n";
        }
    }

    return 0;
}
