#include "account.h"
#include <sstream>

ostream& operator << (ostream& out, const Account& g)
{
    out << g.tostring();
    return out;
}
