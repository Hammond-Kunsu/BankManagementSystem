#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class Customer;

class Account
{
protected:
    static int nextAccountID;
    std::string accountNumber;
    Customer* owner;
    double balance;
    bool status;
    std::vector<Transaction> transactions;

    void updateNextAccountID(const std::string& existingNumber);

public:
    Account(Customer* owner,
            double balance,
            const std::string& existingNumber = "");

    const std::string& getAccountNumber() const;
    Customer* getOwner() const;
    double getBalance() const;
    bool isActive() const;
    void activate();
    void deactivate();
    void addTransaction(const Transaction& transaction);
    const std::vector<Transaction>& getTransactions() const;
    void displayTransactionHistory() const;
    bool deposit(double amount);
    bool transfer(Account& receiver, double amount);
    virtual void displayAccountInfo() const;
    virtual double calculateInterest() const = 0;
    virtual std::string getAccountType() const = 0;
    virtual bool withdraw(double amount, bool addTransactionLog = true) = 0;
    virtual ~Account() = default;
};

#endif
