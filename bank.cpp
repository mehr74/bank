#include "bank.h"

int Bank::ourCount = 0;

Bank::Bank()
{

}

void Bank::GetAccounts()
{

}

void Bank::GetAccount(int ID)
{

}

void Bank::Deposit(int ID, BigInteger cash)
{

}

bool Bank::WithDraw(int ID, BigInteger cash)
{

}

void Bank::Sortition()
{

}

Date * Bank::GetDate()
{
    return myCurrentDate;
}

void Bank::SetDate(Date *dd)
{
    myCurrentDate = dd;
}

void Bank::CreateAccount(BigInteger cash, AccountType type, const string& name)
{
    switch(type)
    {
    case SHORT_TERM:
        Accounts.push_back(new ShortTerm(cash, myCurrentDate, name));
        break;
    case LONG_TERM:
        Accounts.push_back(new LongTerm(cash, myCurrentDate, name));
        break;
    case CURRENT:
        Accounts.push_back(new Current(cash, myCurrentDate, name));
        break;
    case GHARZOL_HASANE:
        Accounts.push_back(new GharzolHasane(cash, myCurrentDate, name));
        break;
    }
}
