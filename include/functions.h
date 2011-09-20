/*
 *  functions.h
 *  
 *  Description: Header file to go with functions.cpp
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
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
#include <sstream>
#include <string>
#include <vector>

#include "wordSet.h"
#include "wordData.h"
// Remove wordData.h if this goes through

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

bool compareAll(vector<string> &, string);
string hintOptions(int);
string hint(int, bool, int, string, int);
void input(vector<wordSet> &, char *);
void insertWords(string, wordSet &,int);
bool isnew(vector<wordSet> &, string, long unsigned int &);
string ordinal(int num);
string printHelp(char *);
int randIndex(int);
double reaction(double, int);
int weightedIndex(wordData *, int);
//int weightedIndex(wordSet *, int);
string whitespace(int length);
#endif
