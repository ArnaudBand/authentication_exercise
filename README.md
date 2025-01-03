# authentication_exercise
## Overview

This project is an authentication system implemented in C++. It includes functionalities for user registration, login, and password management.

## Features

- User registration with unique username and password
- Secure password storage using hashing
- User login with authentication
- Password reset functionality

## Requirements

- C++11 or later
- OpenSSL library for hashing

## Setup

1. Clone the repository:
  ```sh
  git clone /home/nuno/workspace/authentication_exercise
  cd authentication_exercise
  ```

2. Install dependencies:
  ```sh
  sudo apt update
  sudo apt-get install g++
  ```

3. Build the project:
  ```sh
  g++ -o auth_system main.cpp -lssl -lcrypto
  ```

## Usage

1. Run the authentication system:
  ```sh
  ./auth_system
  ```

2. Follow the on-screen instructions to register, login, or reset your password.

## Code Structure

- `main.cpp`: Contains the main function and user interaction logic.
- `auth.cpp`: Implements the authentication functionalities.
- `auth.h`: Header file for the authentication functions.

## Example

```cpp
#include <iostream>
#include "auth.h"

int main() {
  // Example usage of the authentication system
  registerUser("username", "password");
  if (loginUser("username", "password")) {
    std::cout << "Login successful!" << std::endl;
  } else {
    std::cout << "Login failed!" << std::endl;
  }
  return 0;
}
```

## License

This project is licensed under the MIT License.