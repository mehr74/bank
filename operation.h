#ifndef OPERATION_H
#define OPERATION_H

#include "date.h"
#include "bigint.h"
#include "accounts.h"

class Operation
{
public:
    Operation(Account *account, BigInteger cash, OperationType t, Date * = new Date());
    virtual ~Operation() {}

    string ToString() const;
    string DeepString() const;

private:
    Date *myDate;
    BigInteger myCash;

    Account *myAccount;

    OperationType myType;
    int myNumber;

    static int ourCount;
};

ostream& operator << (ostream& out, const Operation& o);

#endif // OPERATION_H
