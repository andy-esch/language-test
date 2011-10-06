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

using std::cout;
using std::endl;
using std::string;
using std::vector;


class Hint {
public:
    string key; 
    int hintNum;    // Counts the number of hints (i.e., # letters + # answers + ...?)
    bool verbose;
    //int penalty; //each hint method call can increase this.
    string handle(string, bool);
    Hint(string, bool);
    Hint();
    void setKey(string);
private:
    string hint;
    void addLetter(int=1);
    void fillLetterPlaces();
    void answer(void);
    void disableHints(void);
    string example();
    string synonym();
    string help();
};
#endif