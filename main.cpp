#include <iostream>
#include "bank.h"
using namespace std;

int main()
{
    Bank bank("Mehrshad Lotfi");
    bank.GetDate(JALALI);
    bank.CreateAccount(10000, GHARZOL_HASANE, "Mehrshad");
    bank.CreateAccount(10000, SHORT_TERM, "Ali");
    bank.GetAccounts();

    return 0;
}
