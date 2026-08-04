#include <iostream>
#include "App.h"
#include "Bank.h"

int main()
{
    Bank bank("OOP Bank", "GRP023");
    if(bank.loadData())
        std::cout << "Saved bank data loaded.\n";
    else
        std::cout << "Starting with an empty bank.\n";

    const int result = runBankApp(bank, true);
    if(bank.saveData())
        std::cout << "Bank data saved.\n";
    else
        std::cout << "Could not save bank data.\n";
    return result;
}
