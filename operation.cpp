#include "operation.h"

int Operation::ourCount = 0;

Operation::Operation(Account *account, BigInteger cash, OperationType t, Date *dd)
    : myAccount(account),
      myCash(cash),
      myDate(dd),
      myType(t),
      myNumber(ourCount)
{
    ourCount++;
}

string Operation::ToString() const
{
    ostringstream out;
    out << "\n*      Operation (" << myNumber << ") ";
    switch(myType)
    {
    case CREATE:
        out << "Create (" << myCash << ") ";
        break;
    case WITH_DRAW:
        out << "Withdraw (" << myCash << ") ";
        break;
    case DEPOSIT:
        out << "Deposit (" << myCash << ") ";
        break;
    }

    return out.str();
}

string Operation::DeepString() const
{
    return ToString();
}

ostream& operator << (ostream& out, const Operation& o)
{
    out << o.ToString();
    return out;
}
