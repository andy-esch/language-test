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

#include <boost/random/mersenne_twister.hpp>        // mt19937
#include <boost/random/discrete_distribution.hpp>   //discrete_distribution()
#include <iostream>
#include <vector>
#include <sstream>
#include <string>   // string members, objects
#include <cmath>    // fma(), fdim(), exp()
#include <ctime>    // time()
#include <cstdlib>
#include <climits> // UINT_MAX

#include "Flashcard.h"
#include "functions.h"
#include "wordCompare.h"

using std::vector;
using std::string;
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
    boost::mt19937 gen;
    double levDistance;
    double weight(bool,double);
public:
    Adaptive(int);
    ~Adaptive();
    unsigned int adaptiveIndex(const vector<Flashcard> &);
    void updateProbs(int,bool,double);
    string probabilitySummary(const vector<Flashcard> &);
    void setLevDistance(string,string);
};

#endif // SMARTPICKER_H
