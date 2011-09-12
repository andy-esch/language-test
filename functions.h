/*
 *  functions.h
 *  
 *  Description:
 *
 *
 *  Created by Peter Eschbacher on 9/11/11.
 *
 */

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
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
void num2ordinal(int num);
void populate(wordData *, const int);
void printHelp(char *);
int randIndex(int);
double reaction(double, int);
int weightedIndex(wordData *, int);
void wordSpaces(int wordLength);
#endif