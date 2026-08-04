#include "Customer.h"
#include "Account.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

int Customer::nextCustomerID = 1;

void Customer::updateNextCustomerID(const std::string& existingID)
{
    if(existingID.length() > 3)
    {
        int number = std::atoi(existingID.substr(3).c_str());
        if(number >= nextCustomerID)
        {
            nextCustomerID = number + 1;
        }
    }
}

Customer::Customer(const std::string& name,
                   const std::string& address,
                   const std::string& phoneNumber,
                   const std::string& existingID)
    : name(name),
      address(address),
      phoneNumber(phoneNumber)
{
    if(existingID.empty())
    {
        std::stringstream stream;
        stream << "CUS" << std::setw(3) << std::setfill('0') << nextCustomerID;
        nextCustomerID++;
        customerID = stream.str();
    }
    else
    {
        customerID = existingID;
        updateNextCustomerID(existingID);
    }
}

void Customer::setName(const std::string& name)
{
    this->name = name;
}

void Customer::setAddress(const std::string& address)
{
    this->address = address;
}

void Customer::setPhoneNumber(const std::string& phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

const std::string& Customer::getCustomerID() const
{
    return customerID;
}

const std::string& Customer::getName() const
{
    return name;
}

const std::string& Customer::getAddress() const
{
    return address;
}

const std::string& Customer::getPhoneNumber() const
{
    return phoneNumber;
}

void Customer::addAccount(Account* account)
{
    if(account == nullptr)
    {
        return;
    }

    for(Account* currentAccount : accounts)
    {
        if(currentAccount == account)
        {
            return;
        }
    }

    accounts.push_back(account);
}

void Customer::removeAccount(Account* account)
{
    for(auto iterator = accounts.begin(); iterator != accounts.end(); ++iterator)
    {
        if(*iterator == account)
        {
            accounts.erase(iterator);
            return;
        }
    }
}

const std::vector<Account*>& Customer::getAccounts() const
{
    return accounts;
}

void Customer::displayCustomerInfo() const
{
    std::cout << "Customer ID : " << customerID << std::endl;
    std::cout << "Name        : " << name << std::endl;
    std::cout << "Address     : " << address << std::endl;
    std::cout << "Phone       : " << phoneNumber << std::endl;
    std::cout << "Accounts    : " << accounts.size() << std::endl;
}
