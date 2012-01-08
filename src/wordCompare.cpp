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

string wordCompare::correctness(string answer, string key)
{
    stringstream response;
    int rating = levenshtein(answer,key);
    response << "Your word is " << levRater(rating) << endl;

    return response.str();
}

usInt wordCompare::findFirstError(string ans, string cmp)
{
    usInt errorPos = 0;
    for (usInt ii = 0; ii < min(ans.size(),cmp.size()); ii++)
    {
        if (ans.at(ii) == cmp.at(ii))
            errorPos++;
        else
            break;
    }

    return errorPos;
}

string wordCompare::levRater(usInt value)
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
/* TODO: move to valarray instead of m[][] ? */
usInt wordCompare::levenshtein(string str1, string str2)
{
    if ( str1.empty() ^ str2.empty() )
        return max(str1.length(),str2.length());
    else if ( str1.empty() && str2.empty() )
        return 0;
    else
    {
        usInt cost;
        const usInt lenOne = str1.length(), lenTwo = str2.length();
        usInt m[lenOne][lenTwo];

        for (usInt ii = 0; ii < lenOne; ii++)
            m[ii][0] = ii+1;

        for (usInt jj = 0; jj < lenTwo; jj++)
            m[0][jj] = jj+1;

        for (usInt ii = 1; ii < lenOne; ii++)
        {
            for (usInt jj = 1; jj < lenTwo; jj++)
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
}

// Returns a string of the unique letters in string str
string wordCompare::unique(string str)
{
    string temp, uniq;
    uniq.push_back(str.at(0));
    cout << "uniq = '" << uniq << "'" << endl;

    for (usInt ii = 1; ii < str.size(); ii++)
    {
        if (uniq.find(str.at(ii)) == string::npos)    // if not found in uniq, add it
            uniq.push_back(str.at(ii));
    }
    return uniq;
}

float wordCompare::lcsPercent(string answer, string response)
{
    const usInt m = answer.size();
    const usInt n = response.size();
    float percentCorrect;
    usInt c[m+1][n+1];

    for (usInt ii = 1; ii <= m; ii++)
        c[ii][0] = 0;

    for (usInt jj = 0; jj <= n; jj++)
        c[0][jj] = 0;

    for (usInt ii = 1; ii <= m; ii++)
    {
        for (usInt jj = 1; jj <= n; jj++)
        {
            if (answer.at(ii-1) == response.at(jj-1))
                c[ii][jj] = c[ii-1][jj-1] + 1;
            else if (c[ii-1][jj] >= c[ii][jj-1])
                c[ii][jj] = c[ii-1][jj];
            else
                c[ii][jj] = c[ii][jj-1];
        }
    }
    percentCorrect = ltest::frac(c[m][n],m) * 100.0;
//    percentCorrect = static_cast<float> (c[m][n]) / \
//                     static_cast<float> (m) * 100;

    return percentCorrect;
}
