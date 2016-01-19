#ifndef GHARZOLHASANE_H
#define GHARZOLHASANE_H

#include "account.h"

class GharzolHasane : public Account
{
    public:
        GharzolHasane(BigInteger cash, Date * = new Date(), const string& name = "");

        // financial operations
        virtual void Deposite(BigInteger);
        virtual bool WithDraw(BigInteger);
        virtual BigInteger GetBalance();
        virtual BigInteger Benefit(Date * = new Date());

        // display operations
        virtual int GetID();
        virtual string ToString() const;

    private:
        int myID;
        BigInteger myBalance;

        string myName;

        Date *myInitialDate;
        Date *myLastBenefitDate;

        BigInteger myLeastBalance;
        const static int ourInterestRate;
        static int ourCount;
};

#endif // GHARZOLHASANE_H
