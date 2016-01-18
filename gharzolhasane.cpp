#include "gharzolhasane.h"

int GharzolHasane::ourCount = 0;
const int GharzolHasane::interestRate = 12;


GharzolHasane::GharzolHasane(BigInteger cash, Date *dd, const string& name)
    : balance(cash), myName(name), initialDate(dd), ID(ourCount)
{
    ourCount++;
}

void GharzolHasane::Deposite(BigInteger)
{
}

bool GharzolHasane::WithDraw(BigInteger)
{
}

BigInteger GharzolHasane::GetBalance()
{

}

BigInteger GharzolHasane::Benefit(Date *)
{

}

int GharzolHasane::GetID()
{
}

string GharzolHasane::ToString() const
{
}
