#ifndef BANK_H
#define BANK_H

#include <iostream>
#include "accounts.h"
#include "date.h"
#include "bigint.h"
#include <string>
#include <vector>

enum AccountType
{
    SHORT_TERM,
    LONG_TERM,
    CURRENT,
    GHARZOL_HASANE
};

class Bank
{
public:
    Bank();
    void GetAccounts();
    void GetAccount(int ID);

    void Deposit(int ID, BigInteger cash);
    bool WithDraw(int ID, BigInteger cash);

    void Sortition();

    Date* GetDate();
    void SetDate(Date *dd);

    void CreateAccount(BigInteger cash, AccountType type, const string& name = "");


private:
    vector <Account *> Accounts;
    Date *myCurrentDate;
    string myName;
    static int ourCount;
};

#endif // BANK_H
