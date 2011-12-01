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

WordData::WordData(void)
         :numAsked(0), numCorrect(0), answeringTime(0.0)
{
}

double WordData::getPercentCorrect(void) const
{
    return 100.0 * static_cast<double>(numCorrect) * ltest::inverse(numAsked);
}

double WordData::getAverageCorrectAnswerTime(void) const
{
    return static_cast<double>(answeringTime) * ltest::inverse(numCorrect);
}

unsigned short int WordData::getNumAsked(void) const
{
    return numAsked;
}

unsigned short int WordData::getNumCorrect(void) const
{
    return numCorrect;
}

void WordData::incrNumAsked(void)
{
    numAsked++;
}

void WordData::incrNumCorrect(void)
{
    numCorrect++;
}

void WordData::incrAnsTime(double incr)
{
    answeringTime += incr;
}
