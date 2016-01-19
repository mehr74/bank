#include "current.h"

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
}

void Current::Deposite(BigInteger cash)
{
    myBalance = myBalance + cash;
}

bool Current::WithDraw(BigInteger cash)
{
    if(myBalance >= cash)
    {
        myBalance = myBalance - cash;
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

string Current::ToString() const
{
    ostringstream out;
    out << "Current Account (" << myID << ") " << myName;
    return out.str();
}
