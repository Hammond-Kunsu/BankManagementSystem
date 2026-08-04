#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "Account.h"

class Customer;

class CurrentAccount : public Account
{
private:
    double overdraftLimit;

public:
    CurrentAccount(Customer* owner, double balance,
                   const std::string& existingNumber = "");

    bool withdraw(double amount, bool addTransactionLog = true) override;
    double calculateInterest() const override;
    std::string getAccountType() const override;
};

#endif
