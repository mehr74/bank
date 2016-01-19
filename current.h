#ifndef CURRENT_H
#define CURRENT_H

#include "account.h"

class Current : public Account
{
    public:
        Current(int ID, BigInteger cash, Date * = new Date(), const string& name = "");

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
        int myNumber;
        BigInteger myBalance;

        string myName;

        Date *myInitialDate;

        const static BigInteger ourLeastBalance;
        const static int ourInterestRate;
        static int ourCount;
};
#endif // CURRENT_H
