#include "account.h"
#include <sstream>

ostream& operator << (ostream& out, Account& g)
{
    out << g.ToString();
    return out;
}
