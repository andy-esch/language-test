/*
 *  Numbers.h
 *  
 *
 *  Created by Añdy Eschbacher on 11/15/11.
 *
 */

#ifndef NUMBERS_H
#define NUMBERS_H

#include <cmath>    
#include <cstdlib>
#include <ctime>    // time(NULL)
#include <iomanip>  // setw()
#include <iostream>
#include <limits>   // numeric_limits
#include <string>
#include <vector>

#include <boost/random/mersenne_twister.hpp>    // mt19937_64
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <readline/readline.h>

#include "functions.h"
#include "wordCompare.h"
#include "ltest_typedefs.h"
#include "Account.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::setw;
using std::string;

extern bool exitToMain;

/* rethink the naming of this class */
class Number {
    usInt numOfItems, numCorrect;
    long xmin, xmax, currentNum;
    string numWord;

    /* private member functions */
    void setCustomOptions();
    bool inputsAreNotOkay();
    string numConst(const long);
    string auxConst(const usInt);
    long randNum(boost::random::mt19937_64 &);
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

usInt getPower(const long); // not in use

template <class U, class V>
U reduce(U num1, V num2)
{
    return (num1/num2) * num2;
}

int numbers(Account &);

#endif // NUMBERS_H

// EOF
