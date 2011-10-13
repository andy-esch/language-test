/*
 *  WordData.cpp
 *  
 *  Description: functions for the class WordData
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#include "WordData.h"

extern bool debug;

WordData::WordData()
{
    numAsked = 0;
    numCorrect = 0;
    answeringTime = 0.0;
}

double WordData::getPercentCorrect(){
  return 100.00*(static_cast<double>(numCorrect)/static_cast<double>(numAsked));
}

double WordData::getAverageCorrectAnswerTime(){
  return static_cast<double>(answeringTime)/static_cast<double>(numCorrect);
}






//void WordData::setProbability(int N)
//{
//    probability= 1.0 / static_cast<double> (N);
//}

//void WordData::populate(int size)
//{   // Populates WordData object to initialization values
//    numAsked = 0;
//    percentRight = 0.0;
//    avgTime = 0.0;
//    probability = 1.0 / static_cast<double> (size);
//}

//double WordData::weight(bool wrong, double diff)
//{   // weight for answering (non-hints)
//    double weight;
//
//    if (wrong)
//    {    // Probability increase with response time for wrong answers
//         // Quick responses are proportional to smaller probability differentials
//      weight = 0.24 * (1.0 - exp(-0.2 * diff));
//    }
//    else // if correct
//    {    // Probability decreases with response times for correct answers
//         // Quick responses are proportional to larger probabilty differentials
//      weight = -0.24 * exp(-0.2 * diff);
//    }
//    
//    if (debug) cout << "weight = " << weight << endl;
//
//    return weight;
//}
//
//double WordData::weight(char typeOfHint, int numLetReqstd, double currProb)
//{   // weight for hints
//    double weight = 0.0;
//
//    switch (typeOfHint)
//    {   // Bounds on weight: Let p = currProb, then:
//        //  -1/(1-p) < weight < 1/p  -- so the 's' case is the lower bound
//        //  and we have a lot more freedom on the upper bound, even up to 1.0
//        //  safely since p <= 1.0 by definition
//        // All of this is not firmly grounded yet.  The -s case worries me
//        // because I've gotten -0.0, which may be floating point errors.  Not
//        // sure how to handle those delicately :(
//        case 'l':   // get a letter
//            weight = 0.3 * static_cast<double> (numLetReqstd);
//            if (weight >= 1.0 / currProb)  // to ensure that probability constraints aren't broken
//                weight = 1.0 / currProb - 0.1;
//            break;
//        case 'a':   // get answer
//            weight = 0.5;
//            break;
//        case 'n':   // get number of letters
//            weight = 0.05;
//            break;
//        case 's':   // skip a word (this weight sets alpha to 0.0, beta = - weight)
//            weight = - 1.0 / (1.0 - currProb);
//            break;
//        case 'u':
//                // Not yet implemented -- for showing usage of word in question
//            break;
//        case 'y':   // Synonym?
//            weight = 0.025;
//            break;
//        default:
//            weight = 0.0; // no effect, shouldn't be triggered
//            break;
//    }
//
//    if (debug) cout << "weight = " << weight << endl;
//
//    return weight;
//}

//void WordData::updateProbs(int index, int numOfEntries, double weight, WordData * wordInfo)
//{   // Updates probabilities
//    double beta = 1.0 - weight * wordInfo[index].probability;
//    double alpha = beta + weight;
//
//    for (int ii = 0; ii < numOfEntries; ii++)
//    {
//        if ( ii != index )
//            wordInfo[ii].probability *= beta;
//        else
//            wordInfo[ii].probability *= alpha;
//    }
//}

//void WordData::updateScore(int index, bool wrong, double timeDiff, \
//                           int numOfEntries, WordData * wordInfo)
//{
//    // Update probabilities
//    updateProbs(index, numOfEntries, \
//                WordData::weight(wrong,timeDiff), wordInfo);
//
//    // Update number of individual queries of word
//    numAsked++;
//
//    // Update scoring percentage
//    if (numAsked == 1)
//        (wrong)?(percentRight = 0.0):(percentRight = 1.0);
//    else if (!wrong && numAsked > 1)
//        percentRight = reweight(numAsked,percentRight,1.0);
//    else if (wrong && numAsked > 1)
//        percentRight = reweight(numAsked,percentRight,0.0);
//
//    // Update timing information
//    avgTime = reweight(numAsked,avgTime,timeDiff);
//}

//void WordData::updateScore(int index, int numOfEntries, WordData * wordStats, \
//                           char typeOfHint, unsigned int numLetReqstd)
//{ // This is the hints variant of this function
//    updateProbs(index, numOfEntries, \
//                weight(typeOfHint,numLetReqstd,wordStats[index].probability), \
//                wordStats);
//}
//
//double WordData::reweight(int num, double old, double newish)
//{
//    double nd = static_cast<double> (num);
//    return ((nd - 1.0) * old + newish)/nd;
//}
