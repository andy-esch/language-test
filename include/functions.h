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

#include <readline/readline.h>

#include "WordData.h"
#include "ltest_typedefs.h"
#include "Account.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;


namespace ltest {

    void welcomeMessage();
    bool pass(int, int, float, float);
    usInt isAccented(string);
    bool compareAll(vector<string> &, string);
    bool containsContraction(string);
    bool isInvalidAnswer(string, vector<string>);
    string hintOptions(int);
    string ordinal(const int);
    void addSpace(string &);

    // TODO: needs work
    template <class X>
    X readint();

    template <class T>
    string numToStr(T num)
    {
        stringstream ss;
        ss << num;
        return ss.str();
    }

    template <class X, class Y>
    float frac(X numer, Y denom)
    {
        return static_cast<float> (numer) / static_cast<float> (denom);
    }

    template <class M>
    M min(M m1, M m2) { return (m1<m2?m1:m2); }

    /* returns false if < 0, true if > 0 */
    template <class W>
    bool sgn(W num)
    {
        if (num < 0)
            return false;
        else
            return true;
    }

    string help(char *);
    int randIndex(const int);
    double reaction(const double, const int);

    template <class Z>
    string printWhitespace(Z length)
    {
        if (length > 0)
        {
            string temp(length+1,' ');
            return temp;   
        }
        else
            return "";
    }
    float howWrongIsIt(string,string);
    vector<string> stripParentheses(vector<string> &);
    string prompt(const char * = NULL);
    string stripParentheses(string);
    string goodbye(const string="");
    bool exitProg(const char*,bool=false);
    int whatDoYouWantToDo(const string);
    double inverse(const int);
        
    // Only handles positive numbers
    template <class X>
    vector<usInt> numDecomp(const X num)
    {
        X tempNum = (num < 0 ? -1.0 : 1.0) * num;
        vector<usInt> numbers;
        
        while (tempNum != 0 || num == 0)
        {
            if (num == 0)
            {
                numbers.push_back(0);
                break;
            }
            
            numbers.push_back(tempNum % 1000);
            tempNum /= 1000;
        }
        
        return numbers;
    }
    

    /* attempt at a more robust input processor */
    template <class T>
    void takeInput(T& val, const char * message = NULL, const char * prmpt = ">> ")
    {
        T temp;
        while (true)
        {
            if (cin.eof()) break;
            if (message != NULL)
                cout << message << endl;
            cout << prompt(prmpt);
            cin >> temp;
            if (!cin.fail()) break;
            else
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cout << '\n' << prompt(prmpt);
            }
        }

        val = temp;
    }


} // namespace ltest

#endif  // FUNCTIONS_H
