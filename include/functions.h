/*
 *  functions.h
 *  
 *  Description: Header file to go with functions.cpp
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>       // numeric_limits<...>::max()
#include <numeric>
#include <sstream>
#include <string>
#include <stdexcept>    // out_of_range(), exception()
#include <typeinfo>     // name(), what()
#include <vector>

#include "WordData.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

namespace ltest {

    bool pass(int, int, float, float);
    bool compareAll(vector<string> &, string);
    bool isInvalidAnswer(string, vector<string>);
    string hintOptions(int);
    string ordinal(int num);
    int min(int, int);
    string help(char *);
    int randIndex(int);
    double reaction(double, int);
    string whitespace(int length);
    float howWrongIsIt(string,string);
    vector<string> stripParentheses(vector<string> &);
    string prompt(void);
    string stripParentheses(string);
    string goodbye(string="");
    bool exitProg(const char*,bool=0);
    int whatDoYouWantToDo(string);
    double inverse(int);

    /* */
    template <class T>
    void takeInput(T& val, const char * message = NULL)
    {
        while (true)
        {
            if (cin.eof()) break;
            if (message != NULL)
                cout << message << endl;
            cout << prompt();
            cin >> val;
            if (!cin.fail()) break;
            else
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cout << prompt();
            }
        }    
    }
} // namespace
#endif  // FUNCTIONS_H
