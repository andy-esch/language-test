/*
 *  worddata.h
 *  
 *  Description: class definition of WordData
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */
#ifndef WORDDATA_H
#define WORDDATA_H

#include <cmath>
#include <iostream>

#include "functions.h"

class WordData
{
private:
    unsigned short int numAsked;
    unsigned short int numCorrect;
    double answeringTime;
public:
    WordData();
    double getPercentCorrect() const;
    double getAverageCorrectAnswerTime() const;
    unsigned short int getNumCorrect() const;
    unsigned short int getNumAsked() const;
    void incrNumAsked();
    void incrNumCorrect();
    void incrAnsTime(double);
};
#endif // WORDDATA_H
