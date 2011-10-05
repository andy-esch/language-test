/*
 *  WordData.h
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
{   // Is there such a thing as 'default class values'? like there are default
    // parameter values for function arguments?  And if so, can they just be
    // defined below, such as float var1 = 3.0?
public:
  WordData();
  unsigned int numAsked;
  unsigned int numCorrect;
  float answeringTime;
  float getPercentCorrect();
  float getAverageTime();
};
#endif // _WORDDATA_H_
