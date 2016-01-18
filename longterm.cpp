#include "longterm.h"

int LongTerm::ourCount = 0;
const BigInteger LongTerm::leastBalance = 15000;
const int LongTerm::interestRate = 42;


LongTerm::LongTerm(BigInteger cash, Date *dd, const string& name)
    : balance(cash), myName(name), initialDate(dd), ID(ourCount)
{
    ourCount++;
}

void LongTerm::Deposite(BigInteger)
{
}

bool LongTerm::WithDraw(BigInteger)
{
}

BigInteger LongTerm::GetBalance()
{

}

BigInteger LongTerm::Benefit(Date *)
{

}

int LongTerm::GetID()
{
}

string LongTerm
::ToString() const
{
}
