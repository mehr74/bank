#include "shortterm.h"
#include "operation.h"

int ShortTerm::ourCount = 0;
const BigInteger ShortTerm::ourLeastBalance = 10000;
const int ShortTerm::ourInterestRate = 17;


ShortTerm::ShortTerm(int ID, BigInteger cash, Date *dd, const string& name)
    : myBalance(cash),
      myName(name),
      myInitialDate(dd),
      myLastBenefitDate(dd),
      myNumber(ourCount),
      myID(ID)
{
    ourCount++;
    myOprs.push_back(new Operation(this, cash, CREATE, dd));
}

bool ShortTerm::Deposite(BigInteger cash, Date * dd)
{
    if(dd < myLastBenefitDate)
        return false;
    Benefit(dd);
    myBalance = myBalance + cash;
    myOprs.push_back(new Operation(this, cash, DEPOSIT, dd));
    return true;
}

bool ShortTerm::WithDraw(BigInteger cash, Date * dd)
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

BigInteger ShortTerm::GetBalance()
{
    Benefit();
    return myBalance;
}

BigInteger ShortTerm::Benefit(Date *dd)
{
    if(myBalance < ourLeastBalance)
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

int ShortTerm::GetID()
{
    return myID;
}

string ShortTerm::ToString()
{
    ostringstream out;
    out << "Short Term Account (" << myID << ") " << myName << "   " << myBalance;
    return out.str();
}

string ShortTerm::DeepString()
{
    ostringstream out;
    out << *this;
    for(int i = 0; i < myOprs.size(); i++)
        out << *myOprs[i];
    return out.str();
}
