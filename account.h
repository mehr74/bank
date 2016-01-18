#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include "bigint.h"
#include "date.h"

class Account
{
    public:
        Account();
        virtual ~Account();

        // financial operations
        virtual bool Deposit(BigInteger) = 0;
        virtual bool WithDraw(BigInteger) = 0;
        virtual BigInteger GetBalance() = 0;

        // display operations
        virtual int GetID() = 0;
        virtual string tostring() const = 0;
        virtual string deepString() const { return tostring(); }

    protected:
        int leastBalance;
        int interestRate;
        int ID;
        int balance;
        Date *currentDate;
        Date *initialDate;
};

ostream& operator << (ostream& out, const Account& a);

#endif // ACCOUNT_H
