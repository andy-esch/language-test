/*
 *  wordCompare.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on Oct. 2011.
 *
 */

#include "wordCompare.h"

string correctness(string answer, string key)
{
    stringstream response;
    int rating = levenshtein(answer,key);
    response << "Your word is " << levRater(rating) << endl;

    return response.str();
}

string levRater(unsigned int value)
{
    string howGood;
    if (value == 1)
        howGood = "very close!";
    else if (value == 2)
        howGood = "a little off!";
    else if (value == 3)
        howGood = "off by a few letters!";
    else if (value >= 4 && value < 8)
        howGood = "not so great!";
    else
        howGood = "terrible, honestly.";

    return howGood;
}

// Levenshtein Distance Edit calculator for two strings
unsigned int levenshtein(string str1, string str2)
{
    unsigned int cost;
    unsigned const int lenOne = str1.length(), lenTwo = str2.length();
    int m[lenOne][lenTwo];
    for (int ii = 0; ii < lenOne; ii++)
        m[ii][0] = ii+1;
    for (int jj = 0; jj < lenTwo; jj++)
        m[0][jj] = jj+1;

    for (int ii = 1; ii < lenOne; ii++)
    {
        for (int jj = 1; jj < lenTwo; jj++)
        {
            if (str1[ii] == str2[jj])
                cost = 0;
            else
                cost = 1;
            m[ii][jj] = min(m[ii-1][jj] + 1, \
                            min(m[ii][jj-1] + 1, \
                                m[ii-1][jj-1] + cost) \
                            );
        }
    }

    return m[lenOne-1][lenTwo-1];
}

// Don't know what's going on here...
float wordCompare(string known, string test)
{
    char currLetter = known[0];
    
    for (int ii = 0; ii < known.size(); ++ii)
    {
        if ( test.find(currLetter) == string::npos )
        {
            
        }
    }
}

// Returns a string of the unique letters in string str
string unique(string str)
{
    string temp, uniq;
    uniq.push_back(str[0]);
    cout << "uniq = '" << uniq << "'" << endl;
    
    for (int ii = 1; ii < str.size(); ii++)
    {
        if (uniq.find(str[ii]) == string::npos)    // if not found in uniq, add it
            uniq.push_back(str[ii]);
    }
    return uniq;
}