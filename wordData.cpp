/*
 *  wordData.cpp
 *  
 *  Description: functions for the class wordData
 *
 *
 *  Created by Peter Eschbacher on 9/11/11.
 *
 */

#include "wordData.h"
#include <iostream>
using std::cout;
using std::endl;

extern bool debug;

double wordData::strength(bool wrong, double diff)
{
    double score;
        // Replace inner if-structures with an exponential function?
    if (wrong)
    {    // Probability increase with response time for wrong answers
         // Quick responses are proportional to smaller probability differentials
        if (diff < 2.0)
            score = 0.03;
        else if (diff < 4.0)
            score = 0.06;
        else if (diff < 8.0)
            score = 0.12;
        else if (diff < 16.0)
            score = 0.18;
        else
            score = 0.24;
    }
    else
    {    // Probability decreases with response times for correct answers
         // Quick responses are proportional to larger probabilty differentials
        if (diff < 1.0)
            score = 0.24;
        else if (diff < 2.0)
            score = 0.18;
        else if (diff < 4.0)
            score = 0.12;
        else if (diff < 8.0)
            score = 0.06;
        else if (diff < 16.0)
            score = 0.03;
        else
            score = 0.015;
    }

    return score;
}

void wordData::updateScore(int pos, bool wrong, double timeDiff, \
                           int numOfEntries, wordData * wordSet)
{
    double weight = ( wrong ? 1.0 : -1.0 ) * wordData::strength(wrong,timeDiff);
    if (debug) cout << "weight = " << weight << endl;
    double beta = 1.0 - weight * wordSet[pos].probability;
    double alpha = beta + weight;
    if (debug)
    {
        cout << "Since the word is " << (wrong?"wrong":"right") << " its probability ";
        cout << (wordSet[pos].probability > (alpha*wordSet[pos].probability)?"decreases":"increases") << endl;
        cout << "beta = " << beta << ", alpha = " << alpha << endl;
    }

        // Update probability of this word coming up again
    for (int ii = 0; ii < numOfEntries; ii++)
    {
        if ( ii != pos )
            wordSet[ii].probability *= beta;
        else
            wordSet[ii].probability *= alpha;
    }

        // Update number of individual queries of word
    numAsked++;

        // Update scoring percentage
    if (numAsked == 1)
        (wrong)?(percentRight = 0.0):(percentRight = 1.0);
    else if (!wrong && numAsked > 1)
        percentRight = reweight(numAsked,percentRight,1.0);
    else if (wrong && numAsked > 1)
        percentRight = reweight(numAsked,percentRight,0.0);

        // Update timing information
    avgTime = reweight(numAsked,avgTime,timeDiff);
}

double wordData::reweight(int num, double old, double newish)
{
    double nd = static_cast<double> (num);
    return ((nd - 1.0) * old + newish)/nd;
}