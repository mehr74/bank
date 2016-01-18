#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include "bigint.h"
#include "date.h"

class Account
{
    public:
        virtual ~Account() {}

        // financial operations
        virtual void Deposite(BigInteger) = 0;
        virtual bool WithDraw(BigInteger) = 0;
        virtual BigInteger GetBalance() = 0;
        virtual BigInteger Benefit(Date * = new Date()) = 0;

        // display operations
        virtual int GetID() = 0;
        virtual string ToString() const = 0;
        virtual string deepString() const { return ToString(); }
};

ostream& operator << (ostream& out, const Account& a);

#endif // ACCOUNT_H
