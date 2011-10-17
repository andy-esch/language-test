/*
 *  Account.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/29/11.
 *
 */

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Account {
    string name;
    vector<string> flashcardTests;
    float score;
    string datePassed;
    int numOfTimesAttempted;
    void importViaXml(void);    // Reminder
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