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

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <stdexcept>    // out_of_range(), exception()
#include <typeinfo>     // name(), what()
#include <vector>

#include "WordData.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

bool pass(int, int, float, float);
bool compareAll(vector<string> &, string);
bool isInvalidAnswer(string, vector<string>);
string hintOptions(int);
string hint(int, bool, int, string, int);
string ordinal(int num);
int min(int, int);
string help(char *);
int randIndex(int);
double reaction(double, int);
string whitespace(int length);
float howWrongIsIt(string,string);
vector<string> stripParentheses(vector<string> &);
string stripParentheses(string);
string goodbye(string="");
bool exitProg(const char*,bool=0);
int whatDoYouWantToDo(string);
double inverse(int);
#endif  // FUNCTIONS_H
