/*
 *  wordCompare.h
 *  
 *  Description:
 *
 *
 *  Created by Peter Eschbacher on 9/26/11.
 *
 */

#ifndef WORDCOMPARE_H
#define WORDCOMPARE_H

#include <iostream>
#include <string>

#include "functions.h"

string correctness(string, string);
string levRater(unsigned int);
unsigned int levenshtein(string, string);
float wordCompare(string, string);
string unique(string);

#endif // WORDCOMPARE_H