#include "current.h"
#include "operation.h"

int Current::ourCount = 0;
const BigInteger Current::ourLeastBalance = 0;
const int Current::ourInterestRate = 0;


Current::Current(int ID, BigInteger cash, Date *dd, const string& name)
    : myBalance(cash),
      myName(name),
      myInitialDate(dd),
      myNumber(ourCount),
      myID(ID)
{
    ourCount++;
    myOprs.push_back(new Operation(this, cash, CREATE, dd));
}

bool Current::Deposite(BigInteger cash, Date *dd)
{
    if(dd < myInitialDate)
        return false;
    myBalance = myBalance + cash;
    myOprs.push_back(new Operation(this, cash, DEPOSIT, dd));
    return true;
}

bool Current::WithDraw(BigInteger cash, Date *dd)
{
    if(dd < myInitialDate)
        return false;
    if(myBalance >= cash)
    {
        myBalance = myBalance - cash;
        myOprs.push_back(new Operation(this, cash, WITH_DRAW, dd));
        return true;
    }
    return false;
}

BigInteger Current::GetBalance()
{
    return myBalance;
}

BigInteger Current::Benefit(Date * dd)
{
    return 0;
}

int Current::GetID()
{
    return myID;
}

string Current::ToString()
{
    ostringstream out;
    out << "Current Account (" << myID << ") " << myName << "   " << myBalance;
    return out.str();
}

string Current::DeepString()
{
    ostringstream out;
    out << *this;
    for(int i = 0; i < myOprs.size(); i++)
        out << *myOprs[i];

    return out.str();
}
