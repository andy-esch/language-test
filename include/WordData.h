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
#include "ltest_typedefs.h"

class WordData
{
private:
    usInt numAsked;
    usInt numCorrect;
    double answeringTime;
public:
    WordData();
    double getPercentCorrect() const;
    double getAverageCorrectAnswerTime() const;
    usInt getNumCorrect() const;
    usInt getNumAsked() const;
    void incrNumAsked();
    void incrNumCorrect();
    void incrAnsTime(double);
};

#endif // WORDDATA_H
