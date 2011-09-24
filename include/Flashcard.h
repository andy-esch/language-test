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
#include <vector>
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
    vector<string> langOneWord;
    vector<string> langTwoWord;
    string  metaData;
    wordStats wordData;
public:
    Flashcard();
    void output(void);
    void set_prob(int);
    void input(string, string);
    void updateInfo(int);
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

void Flashcard::updateInfo(int numEntries)
{
    wordData.updateProb(numEntries);
}

#endif // _FLASHCARD_H_