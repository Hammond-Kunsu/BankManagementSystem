#include "App.h"
#include "Bank.h"
#include "CurrentAccount.h"
#include "Customer.h"
#include "SavingsAccount.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

// Forward declarations for our UI helpers
void displayMenu(bool usesFileStorage);
void registerCustomer(Bank& bank);
void openSavingsAccount(Bank& bank);
void openCurrentAccount(Bank& bank);
void deposit(Bank& bank);
void withdraw(Bank& bank);
void transfer(Bank& bank);
void closeAccount(Bank& bank);
void displayTransactionHistory(Bank& bank);
void searchCustomerByName(Bank& bank);
void editCustomer(Bank& bank);
void removeCustomerFlow(Bank& bank);
void reactivateAccount(Bank& bank);
void displayInterest(Bank& bank);

// Our standard input validators
bool isValidName(const std::string& name);
bool isValidPhoneNumber(const std::string& phoneNumber);
double getValidAmount();

// ============================================================
// Main application loop
// ============================================================
int runBankApp(Bank& bank, bool usesFileStorage)
{
    int choice = -1;
    do
    {
        displayMenu(usesFileStorage);
        while (!(std::cin >> choice))
        {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:  registerCustomer(bank); break;
        case 2:  openSavingsAccount(bank); break;
        case 3:  openCurrentAccount(bank); break;
        case 4:  deposit(bank); break;
        case 5:  withdraw(bank); break;
        case 6:  transfer(bank); break;
        case 7:  bank.displayBankInfo(); break;
        case 8:  bank.displayCustomers(); break;
        case 9:  bank.displayAccounts(); break;
        case 10: displayTransactionHistory(bank); break;
        case 11: closeAccount(bank); break;

        // File storage – only shown when usesFileStorage is true
        case 12:
            if (usesFileStorage)
            {
                if (bank.saveData()) 
                    std::cout << "Data saved successfully." << std::endl;
                else 
                    std::cout << "Could not save data." << std::endl;
            }
            else 
                std::cout << "Invalid choice." << std::endl;
            break;
        case 13:
            if (usesFileStorage)
            {
                if (bank.loadData()) 
                    std::cout << "Saved data loaded." << std::endl;
                else 
                    std::cout << "Could not load saved data." << std::endl;
            }
            else 
                std::cout << "Invalid choice." << std::endl;
            break;

        case 14: searchCustomerByName(bank); break;
        case 15: editCustomer(bank); break;
        case 16: removeCustomerFlow(bank); break;
        case 17: reactivateAccount(bank); break;
        case 18: displayInterest(bank); break;

        case 0:
            std::cout << "\nThank you for using the Bank Management System." << std::endl;
            break;
        default:
            std::cout << "\nInvalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);
    return 0;
}

// ============================================================
// Menu display
// ============================================================
void displayMenu(bool usesFileStorage)
{
    std::cout << "\n=====================================" << std::endl;
    std::cout << "     BANK MANAGEMENT SYSTEM" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "1.  Register Customer" << std::endl;
    std::cout << "2.  Open Savings Account" << std::endl;
    std::cout << "3.  Open Current Account" << std::endl;
    std::cout << "4.  Deposit" << std::endl;
    std::cout << "5.  Withdraw" << std::endl;
    std::cout << "6.  Transfer" << std::endl;
    std::cout << "7.  Display Bank Information" << std::endl;
    std::cout << "8.  Display Customers" << std::endl;
    std::cout << "9.  Display Accounts" << std::endl;
    std::cout << "10. Display Transaction History" << std::endl;
    std::cout << "11. Close Account" << std::endl;
    if (usesFileStorage)
    {
        std::cout << "12. Save Data" << std::endl;
        std::cout << "13. Load Data" << std::endl;
    }
    std::cout << "14. Search Customer by Name" << std::endl;
    std::cout << "15. Edit Customer" << std::endl;
    std::cout << "16. Remove Customer (closes all their accounts first)" << std::endl;
    std::cout << "17. Reactivate Account" << std::endl;
    std::cout << "18. Calculate Interest for an Account" << std::endl;
    std::cout << "0.  Exit" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Enter your choice: ";
}


void openSavingsAccount(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string customerID;
    std::cout << "\nEnter Customer ID: ";
    std::getline(std::cin, customerID);
    Customer* customer = bank.findCustomer(customerID);
    if (customer == nullptr)
    {
        std::cout << "Customer not found." << std::endl;
        return;
    }
    std::cout << "Enter initial deposit (GHc): ";
    SavingsAccount* account = new SavingsAccount(customer, getValidAmount());
    bank.openAccount(account);
    std::cout << "\nSavings Account opened successfully!" << std::endl;
    std::cout << "Account Number: " << account->getAccountNumber() << std::endl;
}

void openCurrentAccount(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string customerID;
    std::cout << "\nEnter Customer ID: ";
    std::getline(std::cin, customerID);
    Customer* customer = bank.findCustomer(customerID);
    if (customer == nullptr)
    {
        std::cout << "Customer not found." << std::endl;
        return;
    }
    std::cout << "Enter initial deposit (GHc): ";
    CurrentAccount* account = new CurrentAccount(customer, getValidAmount());
    bank.openAccount(account);
    std::cout << "\nCurrent Account opened successfully!" << std::endl;
    std::cout << "Account Number: " << account->getAccountNumber() << std::endl;
}

void deposit(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string accountNumber;
    std::cout << "\nEnter Account Number: ";
    std::getline(std::cin, accountNumber);
    Account* account = bank.findAccount(accountNumber);
    if (account == nullptr)
    {
        std::cout << "Account not found." << std::endl;
        return;
    }
    std::cout << "Enter deposit amount (GHc): ";
    double amount = getValidAmount();

    if (account->deposit(amount))
        std::cout << "\nDeposit completed." << std::endl;
    else
        std::cout << "\nDeposit failed." << std::endl;
}

void withdraw(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string accountNumber;
    std::cout << "\nEnter Account Number: ";
    std::getline(std::cin, accountNumber);
    Account* account = bank.findAccount(accountNumber);
    if (account == nullptr)
    {
        std::cout << "Account not found." << std::endl;
        return;
    }
    std::cout << "Enter withdrawal amount (GHc): ";
    double amount = getValidAmount();

    if (account->withdraw(amount))
        std::cout << "\nWithdrawal successful." << std::endl;
    else
        std::cout << "\nWithdrawal failed." << std::endl;
}

void transfer(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string senderNumber, receiverNumber;
    std::cout << "\nEnter sender account number: ";
    std::getline(std::cin, senderNumber);
    Account* sender = bank.findAccount(senderNumber);
    if (sender == nullptr)
    {
        std::cout << "Sender account not found." << std::endl;
        return;
    }
    std::cout << "Enter receiver account number: ";
    std::getline(std::cin, receiverNumber);
    Account* receiver = bank.findAccount(receiverNumber);
    if (receiver == nullptr)
    {
        std::cout << "Receiver account not found." << std::endl;
        return;
    }
    std::cout << "Enter transfer amount (GHc): ";
    double amount = getValidAmount();

    if (bank.transfer(*sender, *receiver, amount))
        std::cout << "\nTransfer completed." << std::endl;
    else
        std::cout << "\nTransfer failed." << std::endl;
}

void closeAccount(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string accountNumber;
    std::cout << "\nEnter Account Number to close: ";
    std::getline(std::cin, accountNumber);
    Account* account = bank.findAccount(accountNumber);
    if (account == nullptr)
    {
        std::cout << "Account not found." << std::endl;
        return;
    }
    if (bank.closeAccount(account))
        std::cout << "Account closed successfully." << std::endl;
    else
        std::cout << "Could not close account." << std::endl;
}

void displayTransactionHistory(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string accountNumber;
    std::cout << "\nEnter Account Number: ";
    std::getline(std::cin, accountNumber);
    Account* account = bank.findAccount(accountNumber);
    if (account == nullptr)
    {
        std::cout << "Account not found." << std::endl;
        return;
    }
    std::cout << "\n===== TRANSACTION HISTORY =====" << std::endl;
    account->displayTransactionHistory();
}

double getValidAmount()
{
    double amount;
    while (true)
    {
        std::cin >> amount;
        if (!std::cin.fail() && amount > 0)
            return amount;
        std::cout << "Invalid amount. Enter again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool isValidName(const std::string& name)
{
    if (name.empty()) return false;
    for (char character : name)
        if (!std::isalpha(character) && character != ' ')
            return false;
    return true;
}

bool isValidPhoneNumber(const std::string& phoneNumber)
{
    if (phoneNumber.length() != 10) return false;
    for (char character : phoneNumber)
        if (!std::isdigit(character))
            return false;
    return true;
}

// ============================================================
// Registration with duplicate check
// ============================================================
void registerCustomer(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name, address, phoneNumber;

    do
    {
        std::cout << "Enter customer's name: ";
        std::getline(std::cin, name);
        if (!isValidName(name))
            std::cout << "Invalid name. Please try again." << std::endl;
    } while (!isValidName(name));

    do
    {
        std::cout << "Enter customer's address: ";
        std::getline(std::cin, address);
        if (address.empty())
            std::cout << "Address cannot be empty." << std::endl;
    } while (address.empty());

    do
    {
        std::cout << "Enter customer's phone number: ";
        std::getline(std::cin, phoneNumber);
        if (!isValidPhoneNumber(phoneNumber))
            std::cout << "Invalid phone number. Please try again." << std::endl;
    } while (!isValidPhoneNumber(phoneNumber));

    // We prevent duplicate customers by checking name + phone
    if (bank.isCustomerRegistered(name, phoneNumber))
    {
        std::cout << "\nA customer with this name and phone number already exists." << std::endl;
        std::cout << "Registration cancelled." << std::endl;
        return;
    }

    Customer* customer = new Customer(name, address, phoneNumber);
    bank.registerCustomer(customer);
    std::cout << "\nCustomer registered successfully!" << std::endl;
    std::cout << "Customer ID: " << customer->getCustomerID() << std::endl;
}

// ============================================================
// New feature: search by name (uses Bank::findCustomerByName)
// ============================================================
void searchCustomerByName(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name;
    std::cout << "\nEnter customer name to search: ";
    std::getline(std::cin, name);

    Customer* customer = bank.findCustomerByName(name);
    if (customer == nullptr)
    {
        std::cout << "No customer found with that name." << std::endl;
        return;
    }
    std::cout << "\n===== Customer Found =====" << std::endl;
    customer->displayCustomerInfo();
}

// ============================================================
// New feature: edit customer (uses the setters we wrote)
// ============================================================
void editCustomer(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string id;
    std::cout << "\nEnter Customer ID to edit: ";
    std::getline(std::cin, id);

    Customer* customer = bank.findCustomer(id);
    if (customer == nullptr)
    {
        std::cout << "Customer not found." << std::endl;
        return;
    }

    std::string newName, newAddress, newPhone;
    std::cout << "Enter new name (or press Enter to keep current): ";
    std::getline(std::cin, newName);
    if (!newName.empty() && isValidName(newName))
        customer->setName(newName);
    else if (!newName.empty())
        std::cout << "Invalid name – not updated." << std::endl;

    std::cout << "Enter new address (or press Enter to keep current): ";
    std::getline(std::cin, newAddress);
    if (!newAddress.empty())
        customer->setAddress(newAddress);

    std::cout << "Enter new phone number (or press Enter to keep current): ";
    std::getline(std::cin, newPhone);
    if (!newPhone.empty() && isValidPhoneNumber(newPhone))
        customer->setPhoneNumber(newPhone);
    else if (!newPhone.empty())
        std::cout << "Invalid phone – not updated." << std::endl;

    std::cout << "Customer details updated." << std::endl;
}

// ============================================================
// New feature: remove customer (uses getAccounts + removeCustomer)
// ============================================================
void removeCustomerFlow(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string id;
    std::cout << "\nEnter Customer ID to remove: ";
    std::getline(std::cin, id);

    Customer* customer = bank.findCustomer(id);
    if (customer == nullptr)
    {
        std::cout << "Customer not found." << std::endl;
        return;
    }

    // We need the customer's accounts so we can close them first.
    const std::vector<Account*>& customerAccounts = customer->getAccounts();

    if (!customerAccounts.empty())
    {
        std::cout << "This customer has " << customerAccounts.size() << " account(s)." << std::endl;
        std::cout << "Closing all accounts before removing the customer..." << std::endl;

        // We iterate over a copy because closing accounts modifies the vector.
        std::vector<Account*> accountsCopy = customerAccounts;
        for (Account* acc : accountsCopy)
        {
            if (bank.closeAccount(acc))
                std::cout << "Closed account " << acc->getAccountNumber() << std::endl;
            else
                std::cout << "Failed to close account " << acc->getAccountNumber() << std::endl;
        }
    }

    // Now it is safe to remove the customer.
    bank.removeCustomer(customer);
    std::cout << "Customer removed successfully." << std::endl;
}

// ============================================================
// New feature: reactivate an account (uses Account::activate)
// ============================================================
void reactivateAccount(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string accountNumber;
    std::cout << "\nEnter Account Number to reactivate: ";
    std::getline(std::cin, accountNumber);

    Account* account = bank.findAccount(accountNumber);
    if (account == nullptr)
    {
        std::cout << "Account not found." << std::endl;
        return;
    }

    if (account->isActive())
    {
        std::cout << "Account is already active." << std::endl;
        return;
    }

    account->activate();
    std::cout << "Account reactivated successfully." << std::endl;
}

void displayInterest(Bank& bank)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string accountNumber;
    std::cout << "\nEnter Account Number: ";
    std::getline(std::cin, accountNumber);

    Account* account = bank.findAccount(accountNumber);
    if (account == nullptr)
    {
        std::cout << "Account not found." << std::endl;
        return;
    }

    double interest = account->calculateInterest();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Interest for this account: GHc " << interest << std::endl;
}