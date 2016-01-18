#ifndef LONGTERM_H
#define LONGTERM_H

#include "account.h"

class LongTerm : public Account
{
    public:
        LongTerm(BigInteger cash, Date * = new Date(), const string& name = "");

        // financial operations
        virtual void Deposite(BigInteger);
        virtual bool WithDraw(BigInteger);
        virtual BigInteger GetBalance();
        virtual BigInteger Benefit(Date *);

        // display operations
        virtual int GetID();
        virtual string ToString() const;

    private:
        int ID;
        BigInteger balance;

        string myName;

        Date *initialDate;

        const static BigInteger leastBalance;
        const static int interestRate;
        static int ourCount;
};

#endif // LONGTERM_H
