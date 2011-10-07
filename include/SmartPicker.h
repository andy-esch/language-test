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

using std::vector;
using std::cout;

class SmartPicker {
protected:
    int currentIndex;
    void setCurrentIndex(int);
public:
    SmartPicker(void);
    int nextIndex(int);
};

class LeastPicked: public SmartPicker {
public:
    int leastPickedIndex(vector<Flashcard> &);
};

class WeightedIndex: public SmartPicker {
public:
    void print() { cout << "hi"; }
};

#endif // SMARTPICKER_H
