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

class WordData
{
public:
    unsigned int numAsked;
    unsigned int numCorrect;
    double answeringTime;
    WordData();
    double getPercentCorrect();
    double getAverageCorrectAnswerTime();
};
#endif // _WORDDATA_H_
