/*
 *  wordStats.h
 *  
 *  Description: class definition of wordStats
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#ifndef _WORDSTATS_H_
#define _WORDSTATS_H_
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

class wordStats
{
    unsigned int numAsked;
    float percentRight;
    float avgTime;
    double probability;
public:
    wordStats();
    void output(void);
    void updateProb(int);
    friend class Flashcard;
};

wordStats::wordStats()  // Default constructor
{
    numAsked = 0;
    percentRight = 0.0;
    avgTime = 0.0;
    probability = 0.0; // This needs to be changed to 1/numEntries
}

void wordStats::output(void)
{
    cout << "numAsked = " << numAsked << endl;
    cout << "percentRight = " << percentRight << endl;
    cout << "avgTime = " << avgTime << endl;
    cout << "probability = " << probability << endl;
}

void wordStats::updateProb(int num)
{
     probability = 1.0 / static_cast<double> (num);
}

#endif // _WORDSTATS_H_