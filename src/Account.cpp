/*
 *  Account.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/29/11.
 *
 */

#include "Account.h"

Account::Account()
{
    name = "Andy";
    score = 100.0;
}

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
    bool yn = false;
    youAre = whoAreYou();
    do
    {
        getline(cin,youAre);
        string ynstr;
        cout << "You set your account name to '" << youAre \
             << "'. Do you want to keep that? (yes or no)" << endl;
        cin >> ynstr;
        if (ynstr == "yes" && not doesAcctExist(youAre))
            yn = true;
    } while (yn == false);  // Should there be other escape sequences?
                            // such as if you accidentally entered this and
                            // don't want to establish a new account?

    setName(youAre);
}

bool Account::doesAcctExist(string acctName)
{
    /* search xml files to see if one has a name already entered */
    return false;    // change this obviously
}

void Account::setName(string newName)
{
    name = newName;
}

string Account::whoAreYou()
{
    string acctName;
    cout << "What is your account name?" << endl;
    return acctName;
}
