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
    vector<string> langOneWord;   // old verbos
    vector<string> langTwoWord;   // old verbs
    wordStats wordData;
/*public:
    string output(int);
    void summarizeContents(int);
    void clearWS(void);*/
    void updateProbs(int, int, double, Flashcard *); /* Needs access to all probabilities in Flashcard */
    void updateScore(int, bool, double, int, Flashcard *);
    void updateScore(int, int, Flashcard *, char, unsigned int=0);
public:
    string printWord(int, int);
};
#endif // _FLASHCARD_H_