#include <iostream>
#include <string>
#include <cstdlib>
#include "bank.h"
using namespace std;

int tokenizeCommand(const string &command, string *cashStr , long long int *number)
{
    int tmp = command.find('_')+1;
  //  tmp = command.find('_', tmp+1)+1;
    int tmp2 = command.find('_', tmp+1);
    string substr = command.substr(tmp, tmp2-tmp);
    *number = atoi(substr.c_str());

    *cashStr = command.substr(tmp2+1);

    return 0;
}

int tokenizeDate(const string &dateStr, int *dd, int *mm, int *yy)
{
    int tmp = dateStr.find('_')+1;
    int tmp2 = dateStr.find('_', tmp+1)+1;
    int tmp3 = dateStr.find('_', tmp2+1)+1;
    string substr1 = dateStr.substr(tmp, tmp2-tmp-1);
    string substr2 = dateStr.substr(tmp2, tmp3-tmp2-1);
    string substr3 = dateStr.substr(tmp3);
    *dd = atoi(substr1.c_str());
    *mm = atoi(substr2.c_str());
    *yy = atoi(substr3.c_str());
}

int main()
{
    Bank bank("Mehrshad Lotfi");
    string command;
    string cash;
    long long int ID;
    while(1)
    {
        cout << "-> ";
        getline(cin, command);
        if(command.find("Create_") != string::npos)
        {
            tokenizeCommand(command.substr(8), &cash, &ID);

            switch(command[7])
            {
            case 'S':
            case 's':
                bank.CreateAccount(ID, BigInteger(cash), SHORT_TERM);
                break;
            case 'L':
            case 'l':
                bank.CreateAccount(ID, BigInteger(cash), LONG_TERM);
                break;
            case 'C':
            case 'c':
                bank.CreateAccount(ID, BigInteger(cash), CURRENT);
                break;
            case 'G':
            case 'g':
                bank.CreateAccount(ID, BigInteger(cash), GHARZOL_HASANE);
                break;
            }
        }
        else if(command.find("Increase") != string::npos)
        {
            tokenizeCommand(command, &cash, &ID);
            bank.Deposit(ID, BigInteger(cash));

        }
        else if(command.find("Decrease") != string::npos)
        {
            tokenizeCommand(command, &cash, &ID);
            bank.WithDraw(ID, BigInteger(cash));
        }
        else if(command.find("ShowAccount") != string::npos)
        {
            bank.GetAccounts();
        }
        else if(command.find("ShowIDs") != string::npos)
        {
            bank.GetIDs();
        }
        else if(command.find("Sortition") != string::npos)
        {
            bank.Sortition();
        }
        else if(command.find("Set") != string::npos)
        {
            int dd;
            int mm;
            int yy;
            tokenizeDate(command, &dd, &mm, &yy);
            if(yy < 1000)
                yy += 1300;
            bank.SetDate(new Date(dd, mm, yy, JALALI));
        }
        else if(command.find("Exit") != string::npos)
        {
            break;
        }
    }

    return 0;
}
