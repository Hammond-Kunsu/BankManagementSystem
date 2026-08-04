# 🏦 Bank Management System

A console-based banking management application developed in **C++17** using **Object-Oriented Programming (OOP)** principles. The system simulates real-world banking operations including customer management, account handling, financial transactions, and persistent data storage.

The project demonstrates software design concepts such as **inheritance, polymorphism, encapsulation, abstraction, modular programming, and file-based data persistence**.

---

## 🚀 Features

### 👤 Customer Management
- Register new customers
- Search for existing customers
- Edit customer information
- Delete customers
- Prevent duplicate customer registration

### 💳 Account Management
- Create and manage multiple account types
- Support for:
  - Savings Accounts
    - 5% interest calculation
  - Current Accounts
    - GHC 1,000 overdraft facility
- Close and reactivate accounts

### 💰 Banking Operations
- Deposit funds
- Withdraw funds
- Transfer money between accounts
- View account balances
- Calculate savings interest

### 📜 Transaction System
- Records every financial operation
- Maintains transaction history for:
  - Deposits
  - Withdrawals
  - Transfers

### 💾 Data Persistence
- Save banking data to files
- Load previous data when the application starts
- Supports both:
  - File-based storage
  - In-memory execution

---

# 🏗️ System Design

The application follows an object-oriented architecture:
             Bank
              |
         Customer
              |
          Account
         /       \
        /         \
SavingsAccount CurrentAccount

### OOP Concepts Implemented

| Concept | Implementation |
|---|---|
| Encapsulation | Controlled access to class attributes through methods |
| Inheritance | SavingsAccount and CurrentAccount extend Account |
| Polymorphism | Different account types implement specific behaviors |
| Abstraction | Common account operations handled through base classes |

---

# 🛠️ Technologies Used

- **Language:** C++17
- **Programming Paradigm:** Object-Oriented Programming
- **Libraries:** C++ Standard Library (STL)
- **Data Storage:** File Handling
- **Development Tools:** Git, GitHub, VS Code

---

# 📁 Project Structure
BankManagementSystem/
│
├── src/ # Implementation files (.cpp)
│
├── include/ # Header files (.h)
│
├── bin/ # Compiled executables
│
├── data/ # Stored banking records
│
└── README.md

---

# ▶️ Running the Application

## Option 1: Using Executables

Navigate to: bin/

Run:bank_file.exe for file-based persistence.

or: bank_memory.exe

for in-memory execution.

---

## Option 2: Compile From Source

Requirements:

- C++ compiler supporting C++17


🔮 Future Improvements

Possible improvements:

Graphical User Interface (GUI)
Database integration
User authentication system
Password encryption
Online banking API integration
Automated testing

👨‍💻 Author

Kunsu Hammond Tietaa

Computer Engineering Student



