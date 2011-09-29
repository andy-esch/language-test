/*
 *  class-test.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/23/11.
 *
 */

#include <iostream>
#include <string>
#include <vector>

#include "Flashcard.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

int main(int argc, char **argv)
{
    vector<Flashcard> cards;
    vector<Flashcard>::iterator it;
    Flashcard fl1;
    string str1("banksy"), str2("andy");
    int numEntries;

    for (int ii = 0; ii < 4; ii++)
    {
        fl1.input(str1,str2);
        cards.push_back(fl1);
        str1 += "*";
        str2 += "*";
        fl1.clear();
    }
    numEntries = cards.size();
    for (it = cards.begin(); it != cards.end(); it++)
    {
        static int ii = 0;
        it->setInitialInfo(numEntries);
        cout << "Card " << ii++ << ": " << endl;
        it->output();
        cout << "-------------------" << endl;
    }
    

    return 0;
}