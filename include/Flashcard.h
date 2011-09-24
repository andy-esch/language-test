/*
 *  Flashcard.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#ifndef _FLASHCARD_H_
#define _FLASHCARD_H_

#include <list>
#include <string>
#include <iostream>

#include "wordStats.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Flashcard
{
private:
    list<string> langOneWord;
    list<string> langTwoWord;
    string  metaData;               // Can be: 
    wordStats wordData;
public:
    Flashcard();
    void output(void);
    void set_prob(int);
    void input(string, string);
    void clear(void);
    void setInitialInfo(int);
};

Flashcard::Flashcard()
{
    wordData;
}

void Flashcard::output(void)
{
    // Initialize wordStats values
    wordData.wordStats::output();
    cout << "wordOne: " << langOneWord[0] << endl;
    cout << "wordTwo: " << langTwoWord[0] << endl;
}

void Flashcard::input(string str1, string str2)
{
    langOneWord.push_back(str1);
    langTwoWord.push_back(str2);
}

void Flashcard::clear(void)
{
    langOneWord.pop_back();
    langTwoWord.pop_back();
}

void Flashcard::setInitialInfo(int numEntries)
{
    wordData.setInitProb(numEntries);
}

#endif // _FLASHCARD_H_