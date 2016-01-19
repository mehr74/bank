#ifndef GHARZOLHASANE_H
#define GHARZOLHASANE_H

#include "account.h"
#include <vector>

class Operation;
class GharzolHasane : public Account
{
    public:
        GharzolHasane(int ID, BigInteger cash, Date * = new Date(), const string& name = "");

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

        BigInteger myLeastBalance;
        const static int ourInterestRate;
        static int ourCount;
};

#endif // GHARZOLHASANE_H
