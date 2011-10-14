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
    void insertWords(string, Flashcard &, int);
public:
    WordData data;
    double weight;      // What is this used for?
    /* public member functions */
    void toScreen();
    void clearWS();         // Clear wordset (used in input())
    WordData getWordData();
    void recordPerformance(int,bool,double);
    void setWeight(int);
    string getWord(char,int);
    vector<string> getSideA();  
    vector<string> getSideB();
    int size(char);         // size of card side
    int size(char,int);     // size of individual word
    void input(vector<Flashcard> &, char *);
};
#endif // FLASHCARD_H
