/*
 *  worddata.h
 *  
 *  Description: class definition of worddata
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */
#ifndef _WORDDATA_H_
#define _WORDDATA_H_

#include <cmath>
#include <iostream>

#include "wordSet.h"

using std::cout;
using std::endl;

class wordData
{   // Is there such a thing as 'default class values'? like there are default
    // parameter values for function arguments?  And if so, can they just be
    // defined below, such as float var1 = 3.0?
public:
    unsigned int numAsked;
    float percentRight;
    float avgTime;
    double probability;
//    void updateScore(int, bool, double, int, wordData *);
    void updateScore(int, bool, double, int, wordSet *);
//    void updateScore(int, int, wordData *, char, unsigned int=0);
    void updateScore(int, int, wordSet *, char, unsigned int=0);
    void populate(int);
private:
    double reweight(int, double, double);
    double weight(bool, double);
    double weight(char, int, double);
//    void updateProbs(int, int, double, wordData *);
    void updateProbs(int, int, double, wordSet *);
};
#endif // _WORDDATA_H_