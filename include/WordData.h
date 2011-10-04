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
{
 public:
  WordData();
  unsigned int numAsked;
  unsigned int numCorrect;
  double answeringTime;
  double getPercentCorrect();
  double getAverageTime();
};
#endif // _WORDDATA_H_
