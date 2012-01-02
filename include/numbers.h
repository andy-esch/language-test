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
//class Number {
//    usInt numOfItem;
//    int xmin, xmax;
//    /* private member functions */
//    int reduce(int, int);
//public:
//    setNumber(usInt, int, int);
//    string getNewNumber(Number &);
//}

long randNum(int, int, boost::random::mt19937 &);
usInt getPower(const long);
bool inputsAreNotOkay(int, int, int);
int findFirstError(string, string);
string numConstructor(const long);
void setCustomOptions(usInt &, int &, int &);
void loadOptions(usInt &, int &, int &);
int numbers(Account &);
string auxConst(const usInt);
void addSpace(string &);
string removeLeadingTrailingSpaces(string);
string numConst(const long);

#endif // NUMBERS_H

// EOF
