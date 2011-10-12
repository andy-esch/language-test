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

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

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
public:
    Adaptive();
    void print();
    
};

#endif // SMARTPICKER_H
