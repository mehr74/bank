#ifndef BANK_H
#define BANK_H

#include <iostream>
#include "accounts.h"
#include "date.h"
#include "bigint.h"
#include <string>
#include <vector>

class Bank
{
public:
    Bank(const string& name = "");
    Bank(Date *, const string& name = "");
    void GetAccounts();
    void GetIDs();

    void Deposit(int ID, BigInteger cash);
    bool WithDraw(int ID, BigInteger cash);

    void Sortition();

    Date* GetDate(DateType = JALALI) const;
    void SetDate(Date *dd);

    void CreateAccount(int ID, BigInteger cash, AccountType type, const string& name = "");


private:
    vector <Account *> Accounts;
    Date *myCurrentDate;
    string myName;
    int myNumber;
    static int ourCount;
};

#endif // BANK_H
