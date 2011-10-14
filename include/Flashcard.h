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
#include <typeinfo>
#include <stdexcept>    // catch,try, ...
#include <fstream>
#include <cstdlib> // exit()

#include "WordData.h"
#include "functions.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
//using std::float;
using std::vector;
using std::ifstream;

extern bool debug;

class Flashcard {
private:
    vector<string> sideB;
    vector<string> sideA;
public:
    double weight;
    void toScreen();
    void clearWS();
    WordData getWordData();
    void recordPerformance(int,bool,double);
    void setWeight(int);
    string getSideA(int);
    vector<string> getSideA();
    string getSideB(int);
    vector<string> getSideB();
    WordData data;
    int size(char);
    int size(char,int);
    void input(vector<Flashcard> &, char *);
    void insertWords(string, Flashcard &, int);
};
#endif // FLASHCARD_H
