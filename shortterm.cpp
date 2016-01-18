#include "shortterm.h"

int ShortTerm::ourCount = 0;
const BigInteger ShortTerm::leastBalance = 10000;
const int ShortTerm::interestRate = 17;


ShortTerm::ShortTerm(BigInteger cash, Date *dd, const string& name)
    : balance(cash), myName(name), initialDate(dd), ID(ourCount)
{
    ourCount++;
}

void ShortTerm::Deposite(BigInteger)
{
}

bool ShortTerm::WithDraw(BigInteger)
{
}

BigInteger ShortTerm::GetBalance()
{

}

BigInteger ShortTerm::Benefit(Date *)
{

}

int ShortTerm::GetID()
{
}

string ShortTerm::ToString() const
{
}
