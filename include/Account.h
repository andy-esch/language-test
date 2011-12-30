/*
 *  Account.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/29/11.
 *
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include <readline/readline.h>

#include "functions.h"
#include "ltest_typedefs.h"
//#include "progPrefs.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class QuizSummary {
    string subject;
    time_t testDate;
    float score;
public:
    QuizSummary();
};

class Account {
/* Class members */
    string name;
    vector<QuizSummary> results;
    float score;
    string datePassed;
    int numOfTimesAttempted;
    bool verbose;

    void importViaXml(void);    // Reminder
    void saveNewResultsToXML(void); // Reminder
    void setName(char *);
public:
    Account();
    void establishAccount();
    bool doesAcctExist(string);
    void exportAccount(string);
    void loadAccount();
/* Access methods */
    string getName();
    string whoAreYou();
    void setVerbose(bool);
    void setVerbose();
    bool getVerbose() const;
//        friend usInt changeProgOptions(Account &);
};

#endif // ACCOUNT_H
