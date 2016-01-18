#include "current.h"

int Current::ourCount = 0;
const BigInteger Current::leastBalance = 0;
const int Current::interestRate = 0;


Current::Current(BigInteger cash, Date *dd, const string& name)
    : balance(cash), myName(name), initialDate(dd), ID(ourCount)
{
    ourCount++;
}

void Current::Deposite(BigInteger)
{
}

bool Current::WithDraw(BigInteger)
{
}

BigInteger Current::GetBalance()
{

}

BigInteger Current::Benefit(Date *)
{

}

int Current::GetID()
{
}

string Current::ToString() const
{
}
