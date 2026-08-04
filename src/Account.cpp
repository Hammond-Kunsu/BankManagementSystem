#include "Account.h"
#include "Customer.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

int Account::nextAccountID = 1;

void Account::updateNextAccountID(const std::string& existingNumber)
{
    if(existingNumber.length() > 3)
    {
        int number = std::atoi(existingNumber.substr(3).c_str());
        if(number >= nextAccountID)
        {
            nextAccountID = number + 1;
        }
    }
}

Account::Account(Customer* owner,
                 double balance,
                 const std::string& existingNumber)
    : owner(owner),
      balance(balance),
      status(true)
{
    if(this->balance < 0)
    {
        this->balance = 0;
    }

    if(existingNumber.empty())
    {
        std::stringstream stream;
        stream << "ACC" << std::setw(3) << std::setfill('0') << nextAccountID;
        nextAccountID++;
        accountNumber = stream.str();
    }
    else
    {
        accountNumber = existingNumber;
        updateNextAccountID(existingNumber);
    }
}

const std::string& Account::getAccountNumber() const
{
    return accountNumber;
}

Customer* Account::getOwner() const
{
    return owner;
}

double Account::getBalance() const
{
    return balance;
}

bool Account::isActive() const
{
    return status;
}

void Account::activate()
{
    status = true;
}

void Account::deactivate()
{
    status = false;
}

void Account::addTransaction(const Transaction& transaction)
{
    transactions.push_back(transaction);
}

const std::vector<Transaction>& Account::getTransactions() const
{
    return transactions;
}

void Account::displayTransactionHistory() const
{
    if(transactions.empty())
    {
        std::cout << "No transaction history." << std::endl;
        return;
    }

    for(const Transaction& transaction : transactions)
    {
        transaction.displayDetails();
        std::cout << "----------------------" << std::endl;
    }
}

bool Account::deposit(double amount)
{
    if(!status || amount <= 0)
    {
        return false;
    }

    balance += amount;
    Transaction transaction(TransactionType::Deposit,
                            amount,
                            balance,
                            "Deposit");
    addTransaction(transaction);
    return true;
}

bool Account::transfer(Account& receiver, double amount)
{
    if(!status || !receiver.isActive() || amount <= 0)
    {
        return false;
    }

    if(!withdraw(amount, false))
    {
        return false;
    }

    if(!receiver.deposit(amount))
    {
        balance += amount;
        return false;
    }

    Transaction transaction(TransactionType::Transfer,
                            amount,
                            balance,
                            "Transfer to " + receiver.getAccountNumber());
    addTransaction(transaction);
    return true;
}

void Account::displayAccountInfo() const
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Type: " << getAccountType() << std::endl;

    if(owner != nullptr)
    {
        std::cout << "Owner Name: " << owner->getName() << std::endl;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Balance: GHc " << balance << std::endl;

    if(status)
    {
        std::cout << "Status: Active" << std::endl;
    }
    else
    {
        std::cout << "Status: Inactive" << std::endl;
    }

    std::cout << "-----------------------------" << std::endl;
}
