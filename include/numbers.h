/*
 *  numbers.h
 *  
 *
 *  Created by Añdy Eschbacher on 11/15/11.
 *
 */

#ifndef NUMBERS_H
#define NUMBERS_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdlib>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <readline/readline.h>

#include "functions.h"
#include "wordCompare.h"
#include "ltest_typedefs.h"
#include "Account.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::cerr;

/* rethink the naming of this class */
class Number {
    usInt numOfItems, numCorrect;
    long xmin, xmax, currentNum;
    string numWord;

    /* private member functions */
//    int reduce(int, int);
    void setCustomOptions();
    bool inputsAreNotOkay();
    string numConst(const long);
    string auxConst(const usInt);
    long randNum(long, long, boost::random::mt19937_64 &);
public:
    Number();
    void setNumber(usInt, long, long);
    usInt getnumOfItems() const { return numOfItems; }
    usInt getNumCorrect() const { return numCorrect; }
    long getxmin() const { return xmin; }
    long getxmax() const { return xmax; }
    long getCurrNum() const { return currentNum; }
    string getNumWord() const { return numWord; }
    void printNumber();
    void getNewNumber(boost::random::mt19937_64 &);
    void loadOptions();
    void incrNumCorrect();
};

string commaAdder(const string, const bool=true);
usInt getPower(const long); // not in use

template <class U, class V>
U reduce(U num1, V num2)
{
    return (num1/num2) * num2;
}

int numbers(Account &);

//string numConstructor(const long); // going out

#endif // NUMBERS_H

// EOF
