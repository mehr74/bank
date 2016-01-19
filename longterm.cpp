#include "longterm.h"
#include "operation.h"

int LongTerm::ourCount = 0;
const BigInteger LongTerm::ourLeastBalance = 15000;
const int LongTerm::ourInterestRate = 42;


LongTerm::LongTerm(int ID, BigInteger cash, Date *dd, const string& name)
    : myBalance(cash),
      myName(name),
      myInitialDate(dd),
      myLastBenefitDate(dd),
      myNumber(ourCount),
      myID(ID)
{
    ourCount++;
    myOprs.push_back(new Operation(this, cash, CREATE));
}

void LongTerm::Deposite(BigInteger cash)
{
    Benefit();
    myBalance = myBalance + cash;
    myOprs.push_back(new Operation(this, cash, DEPOSIT));
}

bool LongTerm::WithDraw(BigInteger cash)
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

BigInteger LongTerm::GetBalance()
{
    Benefit();
    return myBalance;
}

BigInteger LongTerm::Benefit(Date *dd)
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

int LongTerm::GetID()
{
    return myID;
}

string LongTerm::ToString() const
{
    ostringstream out;
    out << "Long Term Account (" << myID << ") " << myName;
    return out.str();
}

string LongTerm::DeepString() const
{
    ostringstream out;
    out << *this;
    for(int i = 0; i < myOprs.size(); i++)
        out << *myOprs[i];
    return out.str();
}
