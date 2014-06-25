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

#include <cmath>    // fma(), fdim(), exp()
#include <cstdlib>  // exit()
#include <ctime>    // time()
#include <iostream>
#include <limits>   // numeric_limits
#include <list>
#include <sstream>  // stringstream type
#include <string>   // string members, objects
#include <vector>

#include <boost/random/mersenne_twister.hpp>        // mt19937_64
#include <boost/random/discrete_distribution.hpp>   // discrete_distribution()

#include "Flashcard.h"
#include "functions.h"
#include "wordCompare.h"
#include "ltest_typedefs.h"

using std::list;
using std::vector;
using std::string;
using std::cout;
using std::numeric_limits;

/*  Should all classes start with a limited set of the vocab and only expand the
 *  list if a certain performance level is reached?  For instance, start out with
 *  a set of 10, and if, say, all the words have an 70% correctness, add a few
 *  more words...
 */

class SmartPicker {
protected:
    usInt currentIndex;
    void setCurrentIndex(usInt=0);
public:
    SmartPicker();
    virtual ~SmartPicker() {};
    virtual void getNextIndex(const vector<Flashcard> &) = 0;
    // Access methods
    usInt getCurrentIndex() const;
};


class WalkThrough: public SmartPicker {
public:    
    void getNextIndex(const vector<Flashcard> &);
};


class LeastCorrect: public SmartPicker {
private:
    list<usInt> leastCorrectIndices;
    usInt currLowest;
    void repopulateIndices(const vector<Flashcard> &);
    void leastCorrectIndex(const vector<Flashcard> &);
    usInt findSmallest(const vector<Flashcard> &) const;
public:
    // Constructor
    LeastCorrect();
    void getNextIndex(const vector<Flashcard> &);
    usInt getNumOfIndices() const;
    void printIndices();
};



class LeastPicked: public SmartPicker {
private:
    list<usInt> leastPickedIndices;
    usInt currLowest;
    void setCurrentLowest(usInt);
    void leastPickedIndex(const vector<Flashcard> &);
    void repopulateIndices(const vector<Flashcard> &);
    usInt findSmallest(const vector<Flashcard> &);
public:
    LeastPicked();
    void getNextIndex(const vector<Flashcard> &);
    void printIndices();
};



class Adaptive: public SmartPicker {
private:
    vector<double> probability;
    boost::mt19937 gen;
    double levDistance;
    double currAnsTime;
    bool isWrong;
    double weight(bool,double);
public:
    Adaptive(int);
    ~Adaptive();
    void getNextIndex(const vector<Flashcard> &);
    void updateProbsAdvanced(const double, const vector<Flashcard> &);
    void updateProbsBasic(const double);
    string probabilitySummary(vector<Flashcard> &);
    void setLevDistance(string,string);
};

#endif // SMARTPICKER_H

// EOF
