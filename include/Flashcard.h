/*
 *  Flashcard.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#ifndef WORDSET_H
#define WORDSET_H
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Flashcard {
public:
    vector<string> sideB;
    vector<string> sideA;
    void summarizeContents(int);
    void clearWS();
};
#endif
