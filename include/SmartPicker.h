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
#include <list>
#include <sstream>  // stringstream type
#include <string>   // string members, objects
#include <cmath>    // fma(), fdim(), exp()
#include <ctime>    // time()
#include <cstdlib>  // exit()
#include <climits>  //   USHRT_MAX

#include "Flashcard.h"
#include "functions.h"
#include "wordCompare.h"

using std::list;
using std::vector;
using std::string;
using std::cout;

class SmartPicker {
protected:
    unsigned short int currentIndex;
    void setCurrentIndex(int=0);
public:
    SmartPicker(void);
    unsigned short int getNextIndex(int);
    unsigned short int getCurrentIndex();
};

/* Should all classes start with a limited set of the vocab and only expand the
 * list if a certain performance level is reached?  For instance, start out with
 * a set of 10, and if, say, all the words have an 70% correctness, add a few
 * more words...
 */

class LeastCorrect: public SmartPicker {
private:
    list<unsigned short int> leastCorrectIndices;
    unsigned short int currLowest;
    void repopulateIndices(const vector<Flashcard> &);
    void leastCorrectIndex(const vector<Flashcard> &);
    unsigned short int findSmallest(const vector<Flashcard> &);
public:
    LeastCorrect();
    unsigned short int getNextIndex(const vector<Flashcard> &);
    void printIndices();
};



class LeastPicked: public SmartPicker {
private:
    list<unsigned short int> leastPickedIndices;
    unsigned short int currLowest;
    void setCurrentLowest(unsigned short int);
    void leastPickedIndex(const vector<Flashcard> &);
    void repopulateIndices(const vector<Flashcard> &);
    unsigned short int findSmallest(const vector<Flashcard> &);
public:
    LeastPicked();
    unsigned short int getNextIndex(const vector<Flashcard> &);
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
    unsigned short int adaptiveIndex(const vector<Flashcard> &);
    void updateProbsAdvanced(int,bool,double, const vector<Flashcard> &);
    void updateProbsBasic(int,bool,double);
    string probabilitySummary(vector<Flashcard> &);
    void setLevDistance(string,string);
};

#endif // SMARTPICKER_H
