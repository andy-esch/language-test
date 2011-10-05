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
#include "wordData.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Flashcard {
public:
    vector<string> sideB;
    vector<string> sideA;
    //    Flashcard(vector<string>,vector<string>);
    //    Flashcard();
    void toScreen();
    void clearWS();
    wordData getWordData();
private:
    wordData stats;
};
#endif
