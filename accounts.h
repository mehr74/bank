#ifndef ACCOUNTS_H
#define ACCOUNTS_H

enum AccountType
{
    SHORT_TERM,
    LONG_TERM,
    CURRENT,
    GHARZOL_HASANE
};

enum OperationType
{
    DEPOSIT,
    WITH_DRAW,
    CREATE
};

#include "shortterm.h"
#include "longterm.h"
#include "gharzolhasane.h"
#include "current.h"
#include "account.h"

#endif // ACCOUNTS_H
