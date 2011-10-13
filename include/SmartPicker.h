/*
 *  SmartPicker.h
 *  
 *  Description:
 *
 *
 *  Created by KEPS 4/10/11.
 *
 */

#ifndef _SMARTPICKER_H_
#define _SMARTPICKER_H_

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <iostream>
#include <vector>
#include <string>   // string members, objects
#include <cmath>    // fma(), fdim(), exp()
#include <ctime>    // time()
#include <cstdlib>
#include <climits> // UINT_MAX

#include "Flashcard.h"
#include "functions.h"

using std::vector;
using std::cout;

class SmartPicker {
protected:
    unsigned int currentIndex;
    void setCurrentIndex(int);
public:
    SmartPicker(void);
    unsigned int nextIndex(int);    // Pass something like cards.size() as the argument?
};

class LeastPicked: public SmartPicker {
public:
    unsigned int leastPickedIndex(const vector<Flashcard> &);
};

class LeastCorrect: public SmartPicker {
public:
    unsigned int leastCorrectIndex(const vector<Flashcard> &);
};

class Adaptive: public SmartPicker {
private:
    vector<double> probability;
    void updateProbs(int,double);
    double weight(bool,double);
public:
    Adaptive(int);
    ~Adaptive();
    unsigned int adaptiveIndex(const vector<Flashcard> &, unsigned int, bool, float);
};

#endif // SMARTPICKER_H
