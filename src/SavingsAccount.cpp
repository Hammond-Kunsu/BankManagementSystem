#include "SavingsAccount.h"

#include <iostream>

SavingsAccount::SavingsAccount(Customer* owner,
                               double balance,
                               const std::string& existingNumber)
    : Account(owner, balance, existingNumber),
      interestRate(5.0)
{
}

bool SavingsAccount::withdraw(double amount, bool addTransactionLog)
{
    if(amount <= 0)
    {
        return false;
    }

    if(!status)
    {
        return false;
    }

    if(amount > balance)
    {
        return false;
    }

    balance -= amount;

    if(addTransactionLog)
    {
        Transaction transaction(
            TransactionType::Withdraw,
            amount,
            balance,
            "Withdrawal"
        );
        addTransaction(transaction);
    }

    return true;
}
double SavingsAccount::calculateInterest() const
{
    return balance * (interestRate / 100);
}

std::string SavingsAccount::getAccountType() const
{
    return "Savings Account";
}
