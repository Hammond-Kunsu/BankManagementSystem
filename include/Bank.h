#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

class Customer;
class Account;

class Bank
{
private:
    std::string bankName;
    std::string bankCode;
    std::vector<Customer*> customers;
    std::vector<Account*> accounts;

public:
    Bank(const std::string& bankName,
         const std::string& bankCode);
    ~Bank();

    void registerCustomer(Customer* customer);
    void removeCustomer(Customer* customer);
    Customer* findCustomer(const std::string& customerID) const;
    Customer* findCustomerByName(const std::string& name) const;
        bool isCustomerRegistered(const std::string& name, const std::string& phoneNumber) const;

    void openAccount(Account* account);
    bool closeAccount(Account* account);
    Account* findAccount(const std::string& accountNumber) const;
    bool transfer(Account& sender,
                  Account& receiver,
                  double amount);

    bool saveData(const std::string& filename = "data/bank_data.txt") const;
    bool loadData(const std::string& filename = "data/bank_data.txt");
    void displayBankInfo() const;
    void displayCustomers() const;
    void displayAccounts() const;
};

#endif
