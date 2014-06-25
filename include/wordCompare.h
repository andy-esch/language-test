/*
 *  wordCompare.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/26/11.
 *
 */

/* TODO: Convert this namespace to a class?
 */

#ifndef WORDCOMPARE_H
#define WORDCOMPARE_H

#include <iostream>
#include <string>
#include <algorithm> // std::max, std::min

#include "functions.h"
#include "ltest_typedefs.h"

using std::max;
using std::min;

namespace wordCompare {

    string correctness(string, string);
    usInt findFirstError(string, string);
    string levRater(usInt);
    unsigned short levenshtein(string, string);
    float wordCompare(string, string);
    string unique(string);
    float lcsPercent(string, string);

}

#endif // WORDCOMPARE_H

// EOF
