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
#include <math.h>
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
      score=0.24*(1-exp(-0.2*diff));
        // if (diff < 2.0)
        //     score = 0.09;
        // else if (diff < 4.0)
        //     score = 0.12;
        // else if (diff < 8.0)
        //     score = 0.15;
        // else if (diff < 16.0)
        //     score = 0.21;
        // else
        //     score = 0.24;
    }
    else // if correct
    {    // Probability decreases with response times for correct answers
         // Quick responses are proportional to larger probabilty differentials
      score=0.24*exp(-0.2*diff));  

      // if (diff < 1.0)
        //     score = 0.24;
        // else if (diff < 2.0)
        //     score = 0.12;
        // else if (diff < 4.0)
        //     score = 0.06;
        // else if (diff < 8.0)
        //     score = 0.015;
        // else if (diff < 16.0)
        //     score = 0.001;
        // else
        //     score = 0.0;
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

void wordData::updateScore(int pos, int numOfEntries, wordData * wordStats, \
                           char typeOfHint, unsigned int numLetReq)
{
    double weight = 0.0;
    if (debug) cout << "typeOfHint = " << typeOfHint << "." << endl;
    switch (typeOfHint)
    {
        case 'l':   // get a letter
            weight = 0.2 * static_cast<double> (numLetReq);
            break;
        case 'a':   // get answer
            weight = 0.5;
            break;
        case 'n':   // get number of letters
            weight = 0.1;
            break;
        case 's':   // skip a word
            weight = - 1.0 / (1 - wordStats[pos].probability);
            break;
        default:
            weight = 0.0; // no effect
            break;
    }

    double beta = 1.0 - weight * wordStats[pos].probability;
    double alpha = beta + weight;

    // Update probability of this word coming up again
    for (int ii = 0; ii < numOfEntries; ii++)
    {
        if ( ii != pos )
            wordStats[ii].probability *= beta;
        else
            wordStats[ii].probability *= alpha;
    }

    // Update number of individual queries of word
//    numAsked++;

}

double wordData::reweight(int num, double old, double newish)
{
    double nd = static_cast<double> (num);
    return ((nd - 1.0) * old + newish)/nd;
}
