/*
 *  SmartPicker.h
 *  
 *  Description:
 *
 *
 *  Created by KEPS 4/10/11.
 *
 */

#ifndef SMARTPICKER_H
#define SMARTPICKER_H
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
#include "Flashcard.h"
#include <ctime>

using std::vector;

class SmartPicker {
private:
  unsigned int currentIndex;
  void setCurrentIndex(int);
public:
  unsigned int nextIndex(bool sideA, vector<Flashcard>);
  unsigned int leastPickedIndex(bool sideA, vector<Flashcard>);
};
#endif
