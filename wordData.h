/*
 *  worddata.h
 *  
 *  Description: class definition of worddata
 *
 *
 *  Created by Peter Eschbacher on 9/11/11.
 *
 */
#include <iostream>
#ifndef WORDDATA_H
#define WORDDATA_H
using std::cout;
using std::endl;

class worddata {
public:
    unsigned int numAsked;
    float percentRight;
    float avgTime;
    double probability;
    unsigned int rank;
    double strength(bool, double);
    void updateScore(int, bool, double, int, worddata *);
private:
    double reweight(int, double, double);
};
#endif