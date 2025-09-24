# AdminSecure – Simple Authentication System

## Description
This project is a **C++ based authentication system** that manages secure admin login using a password.  
It demonstrates fundamental concepts of **file handling, password protection, and authentication**.

## Features
- **Password Creation** – create a new password if none exists  
- **Login** – enter a password to access the system  
- **Password Verification** – verify password before accessing features  
- **Change Password** – securely update password with validation  
- **Security** – passwords are hidden during input (`getch()`) and stored in a binary file  

## How It Works
- Passwords are saved in a binary file: `pw.bin`  
- User gets **3 attempts** to log in or verify before the program exits  
- The menu provides options to create, change, or log in  

