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
#include "wordset.h"
#include "worddata.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

bool compareAll(vector<string> &, string);
void input(vector<wordset> &, char *);
bool isnew(vector<wordset> &, string, long unsigned int &);
void num2ordinal(int num);
void populate(worddata *, const int);
void printHelp(char *);
int randIndex(int);
double reaction(double, int);
int weightedIndex(worddata *, int);
void wordSpaces(int wordLength);
#endif