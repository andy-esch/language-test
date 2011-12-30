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
         datePassed(""), numOfTimesAttempted(0), verbose(false)
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

void Account::setVerbose(bool newVal)
{
    verbose = newVal;
}

void Account::setVerbose()
{
    verbose = !verbose;
}

bool Account::getVerbose() const
{
    return verbose;
}

void Account::establishAccount()
{
    char *youAre, *yesOrNo;
    bool yn = false;

    do
    {
        cout << endl \
             << "Current user is " << name << ".\n" << endl \
             << "What is your account name?  " \
             << "Enter 'guest' to start a temporary guest account" << endl;

        do
        {
            youAre = readline(">> ");
        } while ( !strcmp(youAre,"\0") );

        if ( !strcmp(youAre,"guest") )
        {
            cout << endl \
                 << "You are picking a guest account.  Your data will only be" \
                 << " active during the current session.  Nothing will be saved." \
                 << "  Do you want to continue as a guest?" << endl;
        }
        else
        {
            cout << endl \
                 << "You set your account name to '" << youAre \
                 << "'. Do you want to keep that? (yes or no)" << endl;
        }

        yesOrNo = readline(">> ");

        if (yesOrNo[0] == 'y' && not doesAcctExist(youAre))
            yn = true;

    } while (yn == false);

    setName(youAre);

    free(youAre);
    free(yesOrNo);
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
