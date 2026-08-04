#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

class Account;

class Customer
{
private:
    static int nextCustomerID;
    std::string customerID;
    std::string name;
    std::string address;
    std::string phoneNumber;
    std::vector<Account*> accounts;

    void updateNextCustomerID(const std::string& existingID);

public:
    Customer(const std::string& name,
             const std::string& address,
             const std::string& phoneNumber,
             const std::string& existingID = "");

    void setName(const std::string& name);
    void setAddress(const std::string& address);
    void setPhoneNumber(const std::string& phoneNumber);
    const std::string& getCustomerID() const;
    const std::string& getName() const;
    const std::string& getAddress() const;
    const std::string& getPhoneNumber() const;
    void addAccount(Account* account);
    void removeAccount(Account* account);
    void displayCustomerInfo() const;
    const std::vector<Account*>& getAccounts() const;
};

#endif
