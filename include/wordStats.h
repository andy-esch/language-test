/*
 *  worddata.h
 *  
 *  Description: class definition of worddata
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */
#ifndef _WORDSTATS_H_
#define _WORDSTATS_H_

#include <cmath>
#include <iostream>

#include "Flashcard.h"

using std::cout;
using std::endl;

class wordStats
{
    unsigned int numAsked;
    float percentRight;
    float avgTime;
    double probability;
//  double reweight(int, double, double);
//  double weight(bool, double);
//  double weight(char, int, double);
/*public:
*/
    wordStats();
        //void populate(int); // Can this be part of the constructor?
};
#endif // _WORDSTATS_H_