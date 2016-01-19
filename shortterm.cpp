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

void ShortTerm::Deposite(BigInteger cash)
{
    Benefit();
    myBalance = myBalance + cash;
    myOprs.push_back(new Operation(this, cash, DEPOSIT));
}

bool ShortTerm::WithDraw(BigInteger cash)
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

BigInteger ShortTerm::GetBalance()
{
    Benefit();
    return myBalance;
}

BigInteger ShortTerm::Benefit(Date *dd)
{
    if(myBalance < ourLeastBalance)
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

int ShortTerm::GetID()
{
    return myID;
}

string ShortTerm::ToString() const
{
    ostringstream out;
    out << "Short Term Account (" << myID << ") " << myName;
    return out.str();
}

string ShortTerm::DeepString() const
{
    ostringstream out;
    out << *this;
    for(int i = 0; i < myOprs.size(); i++)
        out << *myOprs[i];
    return out.str();
}
