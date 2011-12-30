/*
 *  Hint.h
 *  
 *  Description:
 *
 *
 *  Created by KEPS 2/10/11.
 *
 */

#ifndef HINT_H
#define HINT_H

#include <string>
#include <iostream>
#include <vector>

#include "functions.h"
#include "ltest_typedefs.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Hint {
public:
    string key; 
    usInt hintNum;    // keeps track of where in the word the hint is at.
    bool verbose;
    string handle(string,bool);
    Hint(string, bool);
    Hint();
    void setKey(string);
private:
    string hint;
    void addLetter(usInt);
    void addLetter();
    int numOfSpaces(string,int);
    void fillLetterPlaces();
    void answer(void);
    void disableHints(void);
    string example();
    string synonym();
    string help();
    bool isAccented(string);
};

#endif // HINT_H
//could add an int penalty so that each hint results in penalty points.
