/*
 *  testResults.cpp
 *  
 *  Description: Summarizes results of language test LanguageTest.cpp
 *
 *
 *  Created by Añdy Eschbacher on 9/15/11.
 *
 */

#include <iomanip>
#include <iostream>
#include <vector>

#include "testResults.h"
#include "Flashcard.h"
#include "wordData.h"

using std::cout;
using std::endl;
using std::ios;
using std::setw;
using std::vector;

void testResults(vector<Flashcard> & spen, wordData wordy[], \
                 int numEntries, int lengthLongestWord, bool verbose)
{
    cout << endl;
    cout << endl;
    cout << setw(lengthLongestWord+13) << "Summary" << endl;
    for (int i = 0; i < lengthLongestWord + 9; i++)
        cout << "=-";
    cout << endl;
    cout << setw(lengthLongestWord) << "Word" << setw(9) << "Score" << setw(13) << "Reaction" << setw(13) << "Probab" << endl;
    cout << setw(lengthLongestWord) << "----" << setw(9) << "-----" << setw(13) << "--------" << setw(13) << "------" << endl;
    cout.setf(ios::fixed);
    cout.precision(2);
    
    for (int i = 0; i < numEntries; i++)
    {
        cout << setw(lengthLongestWord) << spen[i].sideB[0];
        if ( wordy[i].numAsked > 0 )
        {
            cout << setw(6) << static_cast<int> (100*wordy[i].percentRight) \
            << "% (" << wordy[i].numAsked << ")";
            cout << setw(9) << wordy[i].avgTime;
        }
        else
            cout << setw(6) << "   -" << setw(12) << "   -";
        
        cout << setw(15) << wordy[i].probability*100 << "%";
        
        if ( verbose )
        {
            cout << setw(15) << spen[i].sideA.size() << " word" << ((spen[i].sideA.size()>1)?"s:":":");
            for (int k = 0; k < spen[i].sideA.size(); k++)
                cout << setw(15) << spen[i].sideA[k];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}