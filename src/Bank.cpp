#include "Bank.h"
#include "Account.h"
#include "CurrentAccount.h"
#include "Customer.h"
#include "SavingsAccount.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

void deleteLoadedData(std::vector<Customer*>& customers,
                      std::vector<Account*>& accounts)
{
    for(Account* account : accounts)
    {
        delete account;
    }

    for(Customer* customer : customers)
    {
        delete customer;
    }
}

Bank::Bank(const std::string& bankName,
           const std::string& bankCode)
    : bankName(bankName),
      bankCode(bankCode)
{
}

Bank::~Bank()
{
    deleteLoadedData(customers, accounts);
}

void Bank::registerCustomer(Customer* customer)
{
    if(customer == nullptr)
    {
        return;
    }

    for(Customer* currentCustomer : customers)
    {
        if(currentCustomer == customer)
        {
            return;
        }
    }

    customers.push_back(customer);
}

void Bank::removeCustomer(Customer* customer)
{
    for(auto iterator = customers.begin(); iterator != customers.end(); ++iterator)
    {
        if(*iterator == customer)
        {
            customers.erase(iterator);
            delete customer;
            return;
        }
    }
}

Customer* Bank::findCustomer(const std::string& customerID) const
{
    for(Customer* customer : customers)
    {
        if(customer->getCustomerID() == customerID)
        {
            return customer;
        }
    }

    return nullptr;
}

Customer* Bank::findCustomerByName(const std::string& name) const
{
    for(Customer* customer : customers)
    {
        if(customer->getName() == name)
        {
            return customer;
        }
    }

    return nullptr;
}
bool Bank::isCustomerRegistered(const std::string& name, const std::string& phoneNumber) const
{
    for (const Customer* customer : customers)
    {
        if (customer->getName() == name && customer->getPhoneNumber() == phoneNumber)
            return true;
    }
    return false;
}

void Bank::openAccount(Account* account)
{
    if(account == nullptr)
    {
        return;
    }

    accounts.push_back(account);

    if(account->getOwner() != nullptr)
    {
        account->getOwner()->addAccount(account);
    }
}

bool Bank::closeAccount(Account* account)
{
    if(account == nullptr)
    {
        return false;
    }

    for(auto iterator = accounts.begin(); iterator != accounts.end(); ++iterator)
    {
        if(*iterator == account)
        {
            if(account->getOwner() != nullptr)
            {
                account->getOwner()->removeAccount(account);
            }

            accounts.erase(iterator);
            delete account;
            return true;
        }
    }

    return false;
}

Account* Bank::findAccount(const std::string& accountNumber) const
{
    for(Account* account : accounts)
    {
        if(account->getAccountNumber() == accountNumber)
        {
            return account;
        }
    }

    return nullptr;
}

bool Bank::transfer(Account& sender,
                    Account& receiver,
                    double amount)
{
    return sender.transfer(receiver, amount);
}

bool Bank::saveData(const std::string& filename) const
{
    std::ofstream output(filename);

    if(!output)
    {
        return false;
    }

    output << "BANK_V2" << std::endl;
    output << customers.size() << std::endl;

    for(const Customer* customer : customers)
    {
        output << customer->getCustomerID() << '|'
               << customer->getName() << '|'
               << customer->getAddress() << '|'
               << customer->getPhoneNumber() << std::endl;
    }

    output << accounts.size() << std::endl;

    for(const Account* account : accounts)
    {
        const std::vector<Transaction>& transactionList = account->getTransactions();

        output << account->getAccountType() << '|'
               << account->getAccountNumber() << '|'
               << account->getOwner()->getCustomerID() << '|'
               << std::setprecision(17) << account->getBalance() << '|'
               << account->isActive() << '|'
               << transactionList.size() << std::endl;

        for(const Transaction& transaction : transactionList)
        {
            output << static_cast<int>(transaction.getType()) << '|'
                   << transaction.getTransactionID() << '|'
                   << transaction.getDate() << '|'
                   << std::setprecision(17) << transaction.getAmount() << '|'
                   << transaction.getBalanceAfter() << '|'
                   << transaction.getDescription() << std::endl;
        }
    }

    return true;
}

bool Bank::loadData(const std::string& filename)
{
    std::ifstream input(filename);

    if(!input)
    {
        return false;
    }

    std::string line;
    std::getline(input, line);

    if(line != "BANK_V2")
    {
        return false;
    }

    std::getline(input, line);
    int customerCount = std::atoi(line.c_str());
    std::vector<Customer*> loadedCustomers;
    std::vector<Account*> loadedAccounts;

    for(int index = 0; index < customerCount; index++)
    {
        std::string id;
        std::string name;
        std::string address;
        std::string phoneNumber;
        std::stringstream stream;

        if(!std::getline(input, line))
        {
            deleteLoadedData(loadedCustomers, loadedAccounts);
            return false;
        }

        stream.str(line);
        std::getline(stream, id, '|');
        std::getline(stream, name, '|');
        std::getline(stream, address, '|');
        std::getline(stream, phoneNumber, '|');

        if(id.empty() || name.empty() || phoneNumber.empty())
        {
            deleteLoadedData(loadedCustomers, loadedAccounts);
            return false;
        }

        Customer* customer = new Customer(name, address, phoneNumber, id);
        loadedCustomers.push_back(customer);
    }

    if(!std::getline(input, line))
    {
        deleteLoadedData(loadedCustomers, loadedAccounts);
        return false;
    }

    int accountCount = std::atoi(line.c_str());

    for(int index = 0; index < accountCount; index++)
    {
        std::string type;
        std::string accountNumber;
        std::string ownerID;
        std::string balanceText;
        std::string activeText;
        std::string transactionCountText;
        std::stringstream stream;

        if(!std::getline(input, line))
        {
            deleteLoadedData(loadedCustomers, loadedAccounts);
            return false;
        }

        stream.str(line);
        std::getline(stream, type, '|');
        std::getline(stream, accountNumber, '|');
        std::getline(stream, ownerID, '|');
        std::getline(stream, balanceText, '|');
        std::getline(stream, activeText, '|');
        std::getline(stream, transactionCountText, '|');

        Customer* owner = nullptr;

        for(Customer* customer : loadedCustomers)
        {
            if(customer->getCustomerID() == ownerID)
            {
                owner = customer;
                break;
            }
        }

        if(owner == nullptr || accountNumber.empty())
        {
            deleteLoadedData(loadedCustomers, loadedAccounts);
            return false;
        }

        double balance = std::atof(balanceText.c_str());
        Account* account = nullptr;

        if(type == "Savings Account")
        {
            account = new SavingsAccount(owner, balance, accountNumber);
        }
        else if(type == "Current Account")
        {
            account = new CurrentAccount(owner, balance, accountNumber);
        }
        else
        {
            deleteLoadedData(loadedCustomers, loadedAccounts);
            return false;
        }

        if(activeText == "0")
        {
            account->deactivate();
        }

        int transactionCount = std::atoi(transactionCountText.c_str());

        for(int transactionIndex = 0;
            transactionIndex < transactionCount;
            transactionIndex++)
        {
            std::string typeText;
            std::string id;
            std::string date;
            std::string amountText;
            std::string balanceAfterText;
            std::string description;
            std::stringstream transactionStream;

            if(!std::getline(input, line))
            {
                delete account;
                deleteLoadedData(loadedCustomers, loadedAccounts);
                return false;
            }

            transactionStream.str(line);
            std::getline(transactionStream, typeText, '|');
            std::getline(transactionStream, id, '|');
            std::getline(transactionStream, date, '|');
            std::getline(transactionStream, amountText, '|');
            std::getline(transactionStream, balanceAfterText, '|');
            std::getline(transactionStream, description, '|');

            int transactionType = std::atoi(typeText.c_str());

            if(transactionType < 0 || transactionType > 2 || id.empty())
            {
                delete account;
                deleteLoadedData(loadedCustomers, loadedAccounts);
                return false;
            }

            Transaction transaction(static_cast<TransactionType>(transactionType),
                                    std::atof(amountText.c_str()),
                                    std::atof(balanceAfterText.c_str()),
                                    description,
                                    id,
                                    date);
            account->addTransaction(transaction);
        }

        loadedAccounts.push_back(account);
    }

    deleteLoadedData(customers, accounts);
    customers = loadedCustomers;
    accounts = loadedAccounts;

    for(Account* account : accounts)
    {
        account->getOwner()->addAccount(account);
    }

    return true;
}

void Bank::displayBankInfo() const
{
    std::cout << "Bank Name: " << bankName << std::endl;
    std::cout << "Bank Code: " << bankCode << std::endl;
    std::cout << "Customers: " << customers.size() << std::endl;
    std::cout << "Accounts: " << accounts.size() << std::endl;
}

void Bank::displayCustomers() const
{
    std::cout << "\n===== Customers =====" << std::endl;

    for(const Customer* customer : customers)
    {
        customer->displayCustomerInfo();
        std::cout << std::endl;
    }
}

void Bank::displayAccounts() const
{
    std::cout << "\n===== Accounts =====" << std::endl;

    for(const Account* account : accounts)
    {
        account->displayAccountInfo();
        std::cout << std::endl;
    }
}
