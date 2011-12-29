/*
 *  Account.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/29/11.
 *
 */

/*
 *
 *  If we're going to implement the spaced repetition method in our program,
 *  perhaps we need to make it work through this Account class since it
 *  remembers things between sessions.
 *
 */

#include "Account.h"

QuizSummary::QuizSummary()
            :subject(""), testDate(0), score(0.0)
{
}

Account::Account()
        :name("Geronimo"), results(0), score(100.0), \
         datePassed(""), numOfTimesAttempted(0)
{
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
    char *youAre;
    bool yn = false;
    char *ynstr;

    do
    {
        cout << "What is your account name?  Enter 'guest' to start a guest account" << endl;
        youAre = readline(">> ");

        cout << "You set your account name to '" << youAre \
             << "'. Do you want to keep that? (yes or no)" << endl;

        ynstr = readline(">> ");

        if (ynstr[0] == 'y' && not doesAcctExist(youAre))
            yn = true;

    } while (yn == false);

    setName(youAre);

    free(youAre);
    free(ynstr);
}

bool Account::doesAcctExist(string acctName)
{
    /* search xml files to see if one has a name already entered */
    return false;    // change this obviously
}

void Account::setName(char * newName)
{
    name = newName;
}

string Account::whoAreYou()
{
    string acctName;
    cout << "What is your account name?" << endl;
    return acctName;
}
