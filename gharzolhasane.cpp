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

bool GharzolHasane::Deposite(BigInteger cash, Date *dd)
{
    if(dd < myLastBenefitDate)
        return false;
    Benefit(dd);
    myBalance = myBalance + cash;
    myOprs.push_back(new Operation(this, cash, DEPOSIT, dd));
    return true;
}

bool GharzolHasane::WithDraw(BigInteger cash, Date *dd)
{
    if(dd < myLastBenefitDate)
        return false;
    Benefit(dd);
    if(myBalance >= cash)
    {
        myBalance = myBalance - cash;
        myOprs.push_back(new Operation(this, cash, WITH_DRAW, dd));
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
        return 0;

    int days = *dd - *myLastBenefitDate;

    if(days < 0)
        return 0;

    BigInteger prevBalance = myBalance;
    for(int i = 0; i < days; i++)
    {
        double interest;
        double tmp1 = (double)myBalance;
        double tmp2 = (double)ourInterestRate / (365*100);
        interest = tmp1 * tmp2;
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

string GharzolHasane::ToString()
{
    ostringstream out;
    out << "GharzolHasane Account (" << myID << ") " << myName << "   " << myBalance;
    return out.str();
}

string GharzolHasane::DeepString()
{
    ostringstream out;
    out << *this;
    int j = 0;
    int i = myOprs.size();
    for(int i = 0; i < myOprs.size(); i++)
        out << *myOprs[i];
    return out.str();
}
