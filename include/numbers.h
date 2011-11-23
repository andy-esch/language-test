/*
 *  numbers.h
 *  
 *
 *  Created by Peter Eschbacher on 11/15/11.
 *
 */

#ifndef _NUMBERS_H_
#define _NUMBERS_H_

#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdlib>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "functions.h"
#include "wordCompare.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;

string numConstructor(int);
int randNum(int, int);
int numbers(void);
unsigned short getPower(const long);
bool inputsAreNotOkay(int, int, int);

#endif // NUMBERS_H