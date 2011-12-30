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

#include <boost/random/mersenne_twister.hpp>        // mt19937
#include <boost/random/discrete_distribution.hpp>   //discrete_distribution()
#include <iostream>
#include <vector>
#include <list>
#include <sstream>  // stringstream type
#include <string>   // string members, objects
#include <cmath>    // fma(), fdim(), exp()
#include <ctime>    // time()
#include <cstdlib>  // exit()
#include <climits>  // USHRT_MAX

#include "Flashcard.h"
#include "functions.h"
#include "wordCompare.h"
#include "ltest_typedefs.h"

using std::list;
using std::vector;
using std::string;
using std::cout;


/*  Should all classes start with a limited set of the vocab and only expand the
 *  list if a certain performance level is reached?  For instance, start out with
 *  a set of 10, and if, say, all the words have an 70% correctness, add a few
 *  more words...
 */

class SmartPicker {
protected:
    usInt currentIndex;
    void setCurrentIndex(int=0);
public:
    virtual ~SmartPicker() {};
    SmartPicker();
    virtual usInt getNextIndex(const vector<Flashcard> &) =0;
    // Access methods
    usInt getCurrentIndex();
};


class WalkThrough : public SmartPicker {
public:    
    usInt getNextIndex(const vector<Flashcard> &);
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
    usInt getNextIndex(const vector<Flashcard> &);
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
    usInt getNextIndex(const vector<Flashcard> &);
    void printIndices();
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
    usInt getNextIndex(const vector<Flashcard> &);
    void updateProbsAdvanced(const double, const vector<Flashcard> &);
    void updateProbsBasic(const double);
    string probabilitySummary(vector<Flashcard> &);
    void setLevDistance(string,string);
};

#endif // SMARTPICKER_H

// EOF
