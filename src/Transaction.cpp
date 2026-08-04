#include "Transaction.h"

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

int Transaction::nextID = 1;

std::string Transaction::generateTransactionID()
{
    std::stringstream stream;
    stream << "T" << std::setw(4) << std::setfill('0') << nextID;
    nextID++;
    return stream.str();
}

std::string Transaction::getCurrentDate()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);
    std::stringstream stream;
    stream << (localTime->tm_year + 1900) << '-'
           << std::setw(2) << std::setfill('0') << (localTime->tm_mon + 1) << '-'
           << std::setw(2) << std::setfill('0') << localTime->tm_mday;
    return stream.str();
}

void Transaction::updateNextID(const std::string& existingID)
{
    if(existingID.length() > 1)
    {
        int number = std::atoi(existingID.substr(1).c_str());
        if(number >= nextID)
        {
            nextID = number + 1;
        }
    }
}

Transaction::Transaction(TransactionType type,
                         double amount,
                         double balanceAfter,
                         const std::string& description,
                         const std::string& existingID,
                         const std::string& existingDate)
    : type(type),
      amount(amount),
      balanceAfter(balanceAfter),
      description(description)
{
    if(existingID.empty())
    {
        transactionID = generateTransactionID();
    }
    else
    {
        transactionID = existingID;
        updateNextID(existingID);
    }

    if(existingDate.empty())
    {
        date = getCurrentDate();
    }
    else
    {
        date = existingDate;
    }
}

const std::string& Transaction::getTransactionID() const
{
    return transactionID;
}

TransactionType Transaction::getType() const
{
    return type;
}

double Transaction::getAmount() const
{
    return amount;
}

const std::string& Transaction::getDate() const
{
    return date;
}

double Transaction::getBalanceAfter() const
{
    return balanceAfter;
}

const std::string& Transaction::getDescription() const
{
    return description;
}

void Transaction::displayDetails() const
{
    std::cout << "Transaction ID: " << transactionID << std::endl;
    std::cout << "Type: ";

    switch(type)
    {
        case TransactionType::Deposit:
            std::cout << "Deposit";
            break;
        case TransactionType::Withdraw:
            std::cout << "Withdraw";
            break;
        case TransactionType::Transfer:
            std::cout << "Transfer";
            break;
    }

    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Amount: GHc " << amount << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Balance After: GHc " << balanceAfter << std::endl;
    std::cout << "Description: " << description << std::endl;
}
