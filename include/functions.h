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

#include <cstring>      // strcmp()
#include <iostream>     // cin, cout, endl, etc.
#include <limits>       // numeric_limits<...>::max()
#include <sstream>      // string stream
#include <stdexcept>    // out_of_range(), exception()
#include <string>       // string class, member functions
#include <typeinfo>     // name(), what()
#include <vector>       // vector class, member functions

#include "WordData.h"
#include "ltest_typedefs.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

namespace ltest {

    bool pass(int, int, float, float);
    usInt isAccented(string);
    bool compareAll(vector<string> &, string);
    bool containsContraction(string);
    bool isInvalidAnswer(string, vector<string>);
    string hintOptions(int);
    string ordinal(const int num);

    template <class M>
    M min(M m1, M m2) { return (m1<m2?m1:m2); }

    string help(char *);
    int randIndex(const int);
    double reaction(const double, const int);
    string whitespace(const int length);
    float howWrongIsIt(string,string);
    vector<string> stripParentheses(vector<string> &);
    string prompt(void);
    string stripParentheses(string);
    string goodbye(const string="");
    bool exitProg(const char*,bool=0);
    int whatDoYouWantToDo(const string);
    double inverse(const int);

    /* */
    template <class T>
    void takeInput(T& val, const char * message = NULL)
    {
        T temp;
        while (true)
        {
            if (cin.eof()) break;
            if (message != NULL)
                cout << message << endl;
            cout << prompt();
            cin >> temp;
            if (!cin.fail()) break;
            else
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cout << '\n' << prompt();
            }
        }
        val = temp;
    }
} // namespace
#endif  // FUNCTIONS_H
