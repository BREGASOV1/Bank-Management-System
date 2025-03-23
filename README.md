##Banking Management System in C++
This project implements a basic banking management system in C++ that supports client and user management along with transaction operations.
The application uses file storage to persist client and user data and offers a simple console-based interface.

##Features
Client Management

List Clients: Display all client records with account details.

Add New Client: Create new client records after validating unique account numbers.

Delete Client: Remove client records (with confirmation) using account numbers.

Update Client Info: Modify client details including PIN, name, phone, and balance.

Find Client: Search for a client using their account number.

##Transaction Management

Deposit: Allow deposits to client accounts.

Withdrawal: Process withdrawals ensuring the account balance is sufficient.

Total Balances: Calculate and display the sum of all client balances.

User Management

User Login: Secure login interface that validates username and password.

Manage Users: Add, update, delete, and search for users.

Permissions: Fine-grained access control to restrict user actions (e.g., adding clients, processing transactions).

##File-Based Storage

Client data is stored in Clients.txt and user data in Users.txt, with each record formatted in a specific delimiter-separated format.

##Prerequisites
Compiler: A C++ compiler that supports C++11 or later (e.g., GCC, Clang, MSVC).

##Standard Library:
The code relies on standard C++ libraries such as <iostream>, <vector>, <fstream>, <string>, etc.

##Installation & Compilation
Clone or Download the Repository:


git clone https://github.com/BREGASOV1/BankingManagementSystem.git
cd BankingManagementSystem
Compile the Code:

#Run the Application:
./BankingSystem

Usage
Login:
On startup, you will be prompted with the login screen. Use valid credentials to access the system.

Navigation:
The main menu allows you to choose between client management, transaction management, and user management. Input the corresponding number for each operation.

Client Operations:
Follow the on-screen instructions to list, add, update, or delete client records.

Transaction Operations:
Choose deposit or withdrawal operations from the transaction menu and enter the required details.

User Operations:
Manage user accounts by adding new users, updating permissions, or deleting existing accounts (note: the admin user is protected).

File Structure
main.cpp: Contains the full source code for the banking management system.

Clients.txt: Stores client data (automatically created if it does not exist).

Users.txt: Stores user credentials and permissions (automatically created if it does not exist).

Customization
Permissions:
The system uses bitwise permissions for various operations. You can adjust the permission constants in the source code if you wish to modify the access levels.

Delimiter:
The record separator #//# is used to separate fields in the data files. This can be modified if needed.
