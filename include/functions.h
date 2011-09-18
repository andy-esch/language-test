/*
 *  functions.h
 *  
 *  Description: Header file to go with functions.cpp
 *
 *
 *  Created by Peter Eschbacher on 9/11/11.
 *
 */

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

#include "wordSet.h"
#include "wordData.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

bool compareAll(vector<string> &, string);
void hintOptions(int);
void hintPrint(int, bool, int, string, int);
void input(vector<wordSet> &, char *);
bool isnew(vector<wordSet> &, string, long unsigned int &);
string ordinal(int num);
void populate(wordData *, const int);
void printHelp(char *);
int randIndex(int);
double reaction(double, int);
int weightedIndex(wordData *, int);
string wordSpaces(int wordLength);
#endif
