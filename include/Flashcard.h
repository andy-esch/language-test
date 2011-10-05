/*
 *  Flashcard.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#ifndef FLASHCARD_H
#define FLASHCARD_H
#include <vector>
#include <string>
#include <iostream>
#include "WordData.h"

using std::cout;
using std::endl;
using std::string;
//using std::float;
using std::vector;

class Flashcard {
public:
    vector<string> sideB;
    vector<string> sideA;
    double weight;
    void toScreen();
    void clearWS();
    WordData getWordData();
    void recordPerformance(bool,double);
    void setWeight(int);
    WordData data;
private:

};
#endif
