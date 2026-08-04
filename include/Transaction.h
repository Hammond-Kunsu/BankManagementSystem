#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

enum class TransactionType
{
    Deposit,
    Withdraw,
    Transfer
};

class Transaction
{
private:
    static int nextID;
    std::string transactionID;
    TransactionType type;
    double amount;
    std::string date;
    double balanceAfter;
    std::string description;

    std::string generateTransactionID();
    std::string getCurrentDate();
    void updateNextID(const std::string& existingID);

public:
    Transaction(TransactionType type,
                double amount,
                double balanceAfter,
                const std::string& description,
                const std::string& existingID = "",
                const std::string& existingDate = "");

    const std::string& getTransactionID() const;
    TransactionType getType() const;
    double getAmount() const;
    const std::string& getDate() const;
    double getBalanceAfter() const;
    const std::string& getDescription() const;
    void displayDetails() const;
};

#endif
