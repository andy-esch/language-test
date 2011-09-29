/*
 *  Flashcard.h
 *  
 *  Description: I am experimenting with different STL container types.
 *  
 *  See: http://www.cplusplus.com/reference/stl/
 *  or: http://www.sgi.com/tech/stl/Container.html
 *  for more information.
 *
 *  I'm wondering if multiset is the most ideal one?
 *  http://www.cplusplus.com/reference/stl/multiset/
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
    string  metaData;               /* Can be: noun, verb, etc., or what else?
                                       if it knows its a noun, it should know
                                       that the article/gender should be used in
                                       telling how right/wrong the answer is.
                                     */ 
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
    langOneWord.clear();
    langTwoWord.clear();
}

void Flashcard::setInitialInfo(int numEntries)
{
    wordData.setInitProb(numEntries);
}

#endif // _FLASHCARD_H_