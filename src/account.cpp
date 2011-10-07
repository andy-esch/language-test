/*
 *  Account.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/29/11.
 *
 */

#include "account.h"

void Account::exportAccount(string name)
{
}
void Account::loadAccount(void)
{
}

string Account::getName()
{
    return name;
}

void Account::establishAccount()
{
    string youAre;
    youAre = whoAreYou();
}

string Account::whoAreYou()
{
    string acctName;
    cout << "What is your account name?" << endl;
    getline(cin,acctName);

    return acctName;
}
