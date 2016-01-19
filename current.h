#ifndef CURRENT_H
#define CURRENT_H

#include <vector>
#include "account.h"

class Operation;
class Current : public Account
{
    public:
        Current(int ID, BigInteger cash, Date * = new Date(), const string& name = "");

        // financial operations
        virtual bool Deposite(BigInteger, Date * = new Date());
        virtual bool WithDraw(BigInteger, Date * = new Date());
        virtual BigInteger GetBalance();
        virtual BigInteger Benefit(Date * = new Date());

        // display operations
        virtual int GetID();
        virtual string ToString();
        virtual string DeepString();

    private:
        int myID;
        int myNumber;
        BigInteger myBalance;

        string myName;
        vector <Operation *> myOprs;

        Date *myInitialDate;

        const static BigInteger ourLeastBalance;
        const static int ourInterestRate;
        static int ourCount;
};
#endif // CURRENT_H
