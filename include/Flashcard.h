/*
 *  wordSet.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#ifndef _WORDSET_H_
#define _WORDSET_H_
#include <vector>
#include <string>
#include <iostream>

#include "wordData.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class wordSet
{
public:
    vector<string> verbos;
    vector<string> verbs;
    wordData stats;
    void summarizeContents(int);
    void clearWS();
};
#endif // _WORDSET_H_