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

#include "functions.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class quizSummary {
    string subject;
    time_t testDate;
    float score;
};

class Account {
    string name;
    vector<quizSummary> results;
    float score;
    string datePassed;
    int numOfTimesAttempted;
    void importViaXml(void);    // Reminder
    void saveNewResultsToXML(void); // Reminder
    void setName(string);
public:
    Account();
    void exportAccount(string);
    void loadAccount();
    string getName();
    void establishAccount();
    bool doesAcctExist(string);
    string whoAreYou();
};

#endif // ACCOUNT_H
