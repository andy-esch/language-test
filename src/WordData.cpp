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
  numAsked=0;
  numCorrect=0;
  answeringTime=0.0;
}


double WordData::getPercentCorrect()
{
  if(numAsked==0)
    return 0.0;
  else
    return 100*(static_cast<double>(numCorrect)/static_cast<double>(numAsked));
}


double WordData::getAverageTime()
{
  if(numAsked==0)
    return 0;
  else
    return (answeringTime/static_cast<double>(numAsked));
}
