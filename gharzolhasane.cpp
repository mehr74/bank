#include "gharzolhasane.h"
#include "operation.h"

int GharzolHasane::ourCount = 0;
const int GharzolHasane::ourInterestRate = 12;


GharzolHasane::GharzolHasane(int ID, BigInteger cash, Date *dd, const string& name)
    : myBalance(cash),
      myName(name),
      myInitialDate(dd),
      myLastBenefitDate(dd),
      myNumber(ourCount),
      myID(ID)
{
    myLeastBalance = cash;
    ourCount++;
    myOprs.push_back(new Operation(this, cash, CREATE, dd));
}

void GharzolHasane::Deposite(BigInteger cash)
{
    Benefit();
    myBalance = myBalance + cash;
    myOprs.push_back(new Operation(this, cash, DEPOSIT));
}

bool GharzolHasane::WithDraw(BigInteger cash)
{
    Benefit();
    if(myBalance >= cash)
    {
        myBalance = myBalance - cash;
        myOprs.push_back(new Operation(this, cash, WITH_DRAW));
        return true;
    }
    return false;
}

BigInteger GharzolHasane::GetBalance()
{
    Benefit();
    return myBalance;
}

BigInteger GharzolHasane::Benefit(Date *dd)
{
    if(myBalance < myLeastBalance)
    {
        return 0;
    }
    int days = dd - myLastBenefitDate;
    BigInteger prevBalance = myBalance;
    for(int i = 0; i < days; i++)
    {
        double interest;
        interest = (double)myBalance * ((double)ourInterestRate / 365*100);
        BigInteger dayInterest((int)interest);
        myBalance = myBalance + dayInterest;
    }
    myLastBenefitDate = dd;
    return myBalance - prevBalance;
}

int GharzolHasane::GetID()
{
    return myID;
}

string GharzolHasane::ToString() const
{
    ostringstream out;
    out << "GharzolHasane Account (" << myID << ") " << myName;
    return out.str();
}

string GharzolHasane::DeepString() const
{
    ostringstream out;
    out << *this;
    for(int i = 0; i < myOprs.size(); i++)
        out << *myOprs[i];
    return out.str();
}
