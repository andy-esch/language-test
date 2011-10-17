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
#include <string>

#include "testResults.h"
#include "Flashcard.h"
#include "WordData.h"
#include "functions.h"

using std::cout;
using std::endl;
using std::ios;
using std::setw;
using std::vector;

void testResults(vector<Flashcard> cards, bool verbose)
{
    unsigned int lengthLongestWord = 0;
    for (int i = 0; i < cards.size(); i++)
        if (stripParentheses(cards[i].getWord('B',0)).size() > lengthLongestWord)
            lengthLongestWord = cards[i].size('B',0);
  
    cout << endl;
    cout << endl;
    cout << setw(lengthLongestWord+13) << "Summary" << endl;

    for (int i = 0; i < lengthLongestWord + 9; i++)
        cout << "=-";

    cout << endl;
    cout << setw(lengthLongestWord) << "Word" << setw(9) << "Score" << setw(13) << "Reaction" << endl;
    cout << setw(lengthLongestWord) << "----" << setw(9) << "-----" << setw(13) << "--------" << endl;
    cout.setf(ios::fixed);
    cout.precision(2);
  
    for (int i = 0; i < cards.size(); i++)
    {
        cout << setw(lengthLongestWord) << stripParentheses(cards[i].getWord('B',0));
        if ( cards[i].data.numAsked > 0 )
        {
            cout << setw(6) << static_cast<int> (cards[i].data.getPercentCorrect()) \
            << "% (" << cards[i].data.numAsked << ")";
            cout << setw(9) << cards[i].data.getAverageCorrectAnswerTime();
        }
        else
            cout << setw(6) << "   -" << setw(12) << "   -";
      
      
        if ( verbose )
        {
            cout << setw(15) << cards[i].size('A') << " word" << ((cards[i].size('A')>1)?"s:":":");
            for (int k = 0; k < cards[i].size('A'); k++)
                cout << setw(15) << cards[i].getWord('A',k);
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}
