# Bank-Management-Sysytem-CPP  

A professional-grade console application for managing banking operations, built with modern C++ practices. 
The system supports client management, transaction processing, and user authentication with role-based access control.
Features
🏦 Client Management
- List Clients: Display all client records with account details.  
- Add New Client: Create new client records after validating unique account numbers.  
- Delete Client: Remove client records (with confirmation) using account numbers.  
- Update Client Info: Modify client details including PIN, name, phone, and balance.  
- Find Client: Search for a client using their account number.  
💰 Transaction Management
- Deposit: Allow deposits to client accounts.  
- Withdrawal: Process withdrawals ensuring the account balance is sufficient.  
- Total Balances: Calculate and display the sum of all client balances.  
👥 User Management
- User Login: Secure login interface that validates username and password.  
- Manage Users: Add, update, delete, and search for users.  
- Permissions: Fine-grained access control to restrict user actions (e.g., adding clients, processing transactions).  
🗄️ File-Based Storage
- Clients Data: Stored in Clients.txt  
- User Data: Stored in Users.txt  
- Custom Delimiter: Uses #//# to separate fields in the data files.  
How to Use
# Clone the repository  
git clone https://github.com/BREGASOV1/Bank-Management-System-CPP.git  
cd Bank-Management-System-CPP  

# Compile (Windows)  
g++ -std=c++11 main.cpp -o Bank-Management-System-CPP  

# Run the application  
Bank-Management-System-CPP.exe  

Usage
- Login:  
  On startup, you will be prompted with the login screen. Use valid credentials to access the system.  

- Navigation:  
  The main menu allows you to choose between client management, transaction management, and user management.  

- Client Operations:  
  Follow the on-screen instructions to list, add, update, or delete client records.  

- Transaction Operations:  
  Choose deposit or withdrawal operations from the transaction menu and enter the required details.  

- User Operations:  
  Manage user accounts by adding new users, updating permissions, or deleting existing accounts (admin user is protected).  




