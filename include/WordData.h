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

using std::cout;
using std::endl;

class WordData
{
public:
    unsigned int numAsked;
    unsigned int numCorrect;
    float answeringTime;
    float percentRight;
    WordData();
    double getPercentCorrect() { return percentRight; };
    double getAnsweringTime() { return answeringTime; };
};
#endif // _WORDDATA_H_
