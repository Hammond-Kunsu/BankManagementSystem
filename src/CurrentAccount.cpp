#include "CurrentAccount.h"
#include "Customer.h"

CurrentAccount::CurrentAccount(Customer* owner,
                               double balance,
                               const std::string& existingNumber)
    : Account(owner, balance, existingNumber),
      overdraftLimit(1000.0)
{
}

bool CurrentAccount::withdraw(double amount, bool addTransactionLog)
{
    if(amount <= 0)
    {
        return false;
    }

    if(!status)
    {
        return false;
    }

    if(amount > balance + overdraftLimit)
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
double CurrentAccount::calculateInterest() const
{
    return 0;
}

std::string CurrentAccount::getAccountType() const
{
    return "Current Account";
}
