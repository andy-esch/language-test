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
        :name("Geronimo"), results(0), score(100.0), datePassed(""), numOfTimesAttempted(0)
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
    string youAre;
    bool yn = false;
    string ynstr;

    do
    {
        cout << "What is your account name?" << endl;
        getline(cin,youAre);

        cout << "You set your account name to '" << youAre \
             << "'. Do you want to keep that? (yes or no)" << endl;

        ltest::takeInput(ynstr);

        if (ynstr[0] == 'y' && not doesAcctExist(youAre))
            yn = true;

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
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
