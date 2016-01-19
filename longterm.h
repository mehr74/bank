#ifndef LONGTERM_H
#define LONGTERM_H

#include "account.h"
#include <vector>

class Operation;
class LongTerm : public Account
{
    public:
        LongTerm(int ID, BigInteger cash, Date * = new Date(), const string& name = "");

        // financial operations
        virtual void Deposite(BigInteger);
        virtual bool WithDraw(BigInteger);
        virtual BigInteger GetBalance();
        virtual BigInteger Benefit(Date * = new Date());

        // display operations
        virtual int GetID();
        virtual string ToString() const;
        virtual string DeepString() const;

    private:
        int myID;
        int myNumber;
        BigInteger myBalance;

        string myName;
        vector <Operation *> myOprs;

        Date *myInitialDate;
        Date *myLastBenefitDate;

        const static BigInteger ourLeastBalance;
        const static int ourInterestRate;
        static int ourCount;
};

#endif // LONGTERM_H
