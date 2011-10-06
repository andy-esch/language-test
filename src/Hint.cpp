/*
 *  Hint.cpp
 *  
 *  Description:
 *
 *
 *  Created by KEPS on 2/10/11.
 *
 */

#include "functions.h"
#include "Hint.h"

Hint::Hint(string answerKey, bool selectVerbose)
{
    key = answerKey;
    hintNum = 0;
    verbose = selectVerbose;
    hint = "";
    while (hint.size() <= key.size())
        hint += " ";
}

// Default constructor
Hint::Hint()
{
    key = " ";
    hintNum = 0;
    verbose = false;
    hint = " ";
}


void Hint::setKey(string answerKey)
{
    key = answerKey;
    hint = "";
    while (hint.size() <= key.size())
        hint += " ";
}

void Hint::addLetter(int numLetters)
{// This is moving toward offering multiple letters (hence numLetters)
    if ( hintNum < key.size() )
    {
        if (hintNum + numLetters > key.size()) numLetters = key.size() - hintNum;
        hint.replace(hintNum,numLetters,string(key,hintNum,numLetters));
        hintNum += numLetters;
    }
    if (key[hintNum] == ' ')
        addLetter(1);
    if (hintNum == key.size())
        hint += " <-";
}


void Hint::fillLetterPlaces()
{
    for (int i = hintNum; i < key.size(); i++)
    {
        if(key[i] == ' ')
            hint.replace(i,1," ");

        hint.replace(i,1,"-");
    }
}

void Hint::answer(void)
{
    hint = key;
}


void Hint::disableHints(void)
{
}


string Hint::example(void)
{
    string hint = "an example of usage";
    return hint;
}



string Hint::help()
{
    stringstream hint;
    string ws10 = whitespace(10);
    hint << ws10 << '\a' << endl;
    hint << ws10 << "Want a letter?  Type '-l'." << endl;
    hint << ws10 << "Want more than one letter? Type '-l#', where # = a number 1 - 9." << endl;
    hint << ws10 << "Want the answer?  Type '-a'." << endl;
    hint << ws10 << "Want the number of letters?  Type '-n'." << endl;
    hint << ws10 << "Want to skip this word?  Type '-s'." << endl;
    hint << ws10 << "Want help?  Type '-h'." << endl;
    hint << ws10 << "Want out of here?  Type CTRL-D (End of file -- EOF)." << endl;
    hint << ws10 << "Want to turn these messages off?  Type '-d' to disable." << endl;
    return hint.str();
}


string Hint::handle(string hintType, bool verbose)
{
    stringstream out;
    switch (hintType[1])
    {
        case 'l':
            if (hintType[2] == '\0')
                addLetter(1);
            else if (atoi(&hintType[2]) < 10 && atoi(&hintType[2]) > 0)
                addLetter(atoi(&hintType[2]));
            else
                addLetter(1);
            out << "-> " << hint;
            break;
        case 'a':
            answer();
            out << "-> " << hint;
            break;
        case 'n':
            fillLetterPlaces();
            out << "-> " << hint;
            break;
        case 'h':
            out << help();
            break;
    }

    out << endl;
    return out.str();
}


// string Hint::skipWord()
// help()
// if synonym hint is selected, create new Hint object with new key
// and perform answer() on it.
// string Hint::synonym()
