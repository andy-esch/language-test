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
};

Flashcard::Flashcard()
{
    langOneWord.push_back("sample1");
    langTwoWord.push_back("sample2");
    metaData = "This is the metadata.";
    wordData;
}

void Flashcard::output(void)
{
    cout << "langOneword: ";
    for (int ii = 0; ii < langOneWord.size(); ii++)
        cout << langOneWord[ii] << ' ';
    cout << endl;

    cout << "langTwoword: ";
    for (int jj = 0; jj < langTwoWord.size(); jj++)
        cout << langTwoWord[jj] << ' ';
    cout << endl;

    cout << "metaData: " << metaData << endl;
    wordData.wordStats::output();
}

#endif // _FLASHCARD_H_