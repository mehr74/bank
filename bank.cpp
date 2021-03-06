#include "bank.h"
#include <time.h>
#include <cstdlib>

int Bank::ourCount = 0;

Bank::Bank(const string &name)
    : myCurrentDate(new Date()),
      myNumber(ourCount),
      myName(name)
{
    ourCount++;
}

Bank::Bank(Date *dd, const string& name)
    : myCurrentDate(dd),
      myNumber(ourCount),
      myName(name)
{
    ourCount++;
}

void Bank::GetIDs()
{
    cout << "***********************************************" << endl;
    cout << "* Bank Accounts (" << myNumber << ") " << myName << endl;
    cout << "* ";
    GetDate();
    cout << "*" << endl;
    for(int i = 0; i < Accounts.size(); i++)
        cout << "* " << i+1 << " " << *Accounts[i] << endl;

    cout << "*\n***********************************************" << endl;
}

void Bank::GetAccounts()
{
    cout << "***********************************************" << endl;
    cout << "* Bank Accounts (" << myNumber << ") " << myName << endl;
    cout << "* ";
    GetDate();
    cout << "*" << endl;
    for(int i = 0; i < Accounts.size(); i++)
        cout << "* " << i+1 << " " << Accounts[i]->DeepString() << endl;

    cout << "*\n***********************************************" << endl;
}

void Bank::Deposit(int ID, BigInteger cash)
{
    bool found = false;
    for(int i = 0; i < Accounts.size(); i++)
    {
        if(Accounts[i]->GetID() == ID)
        {
            Accounts[i]->Deposite(cash, myCurrentDate);
            found = true;
        }
    }
}

bool Bank::WithDraw(int ID, BigInteger cash)
{
    bool done = false;
    bool found = false;
    for(int i = 0; i < Accounts.size(); i++)
    {
        if(Accounts[i]->GetID() == ID)
        {
            done = Accounts[i]->WithDraw(cash, myCurrentDate);
            found = true;
        }
    }
}

void Bank::Sortition()
{
    vector<int> points;
    srand(time(NULL));
    for(int i = 0; i < Accounts.size(); i++)
    {
        if(AccountTypes[i] == GHARZOL_HASANE)
        {
            int tmp = Accounts[i]->GetBalance();
            for(int j = 0; j < tmp; j++)
                points.push_back(Accounts[i]->GetID());
        }
    }
    if(!points.empty())
    {
        int winner = rand() % points.size();
        int winnerID = points[winner];
        cout << "Winner is : " << winnerID << endl;
        for(int i = 0; i < Accounts.size(); i++)
        {
            if(Accounts[i]->GetID() == winnerID)
            {
                Accounts[i]->Deposite(111111, myCurrentDate);
            }
        }
    }
}

Date * Bank::GetDate(DateType t) const
{
    if(t == GREGORIAN)
        cout << myCurrentDate->GregorianToString() << endl;
    if(t == JALALI)
        cout << myCurrentDate->JalaliToString() << endl;
}

void Bank::SetDate(Date *dd)
{
    myCurrentDate = dd;
    for(int i = 0; i < Accounts.size(); i++)
        Accounts[i]->Benefit(dd);
}

void Bank::CreateAccount(int ID, BigInteger cash, AccountType type, const string& name)
{
    switch(type)
    {
    case SHORT_TERM:
        Accounts.push_back(new ShortTerm(ID, cash, myCurrentDate, name));
        AccountTypes.push_back(SHORT_TERM);
        break;
    case LONG_TERM:
        Accounts.push_back(new LongTerm(ID, cash, myCurrentDate, name));
        AccountTypes.push_back(LONG_TERM);
        break;
    case CURRENT:
        Accounts.push_back(new Current(ID, cash, myCurrentDate, name));
        AccountTypes.push_back(CURRENT);
        break;
    case GHARZOL_HASANE:
        Accounts.push_back(new GharzolHasane(ID, cash, myCurrentDate, name));
        AccountTypes.push_back(GHARZOL_HASANE);
        break;
    }
}
