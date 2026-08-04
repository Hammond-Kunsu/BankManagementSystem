#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class Customer;

class SavingsAccount : public Account
{
private:
    double interestRate;

public:
    SavingsAccount(Customer* owner, double balance,
                   const std::string& existingNumber = "");

    bool withdraw(double amount, bool addTransactionLog = true) override;
    double calculateInterest() const override;
    std::string getAccountType() const override;
};

#endif
