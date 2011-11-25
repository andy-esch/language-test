/*
 *  flcrd_quiz.cpp
 *  
 *  Description:
 *
 *
 *  Created by Peter Eschbacher on 10/19/11.
 *
 */

#include "flcrd_quiz.h"

int flcrd_quiz(bool verbose, char * inFile)
{
    cout << "Beginning Flashcard Quiz." << endl;
    boost::chrono::system_clock::time_point timeStart;
    boost::chrono::duration<double> timeDiff;
    bool disableHintMsg = false;
    unsigned short ii;
    bool isWrong = true;
    vector<Flashcard> cards;
    string response;
    LeastPicked picker;
    Hint myhint = Hint("  ",verbose);

    /* Choose flashcard set */
    strcpy(inFile,listDicts().c_str());

    cards[0].input(cards,inFile);   // wonky -- input() should be a friend
                                    // instead of a Flashcard member function?

    while ( !cin.eof() )    // Should there be other conditions? Yes, all probabilities can't be zero.
    {
        ii = picker.getNextIndex(cards);

        myhint.setKey(cards[ii].getWord('B',ltest::randIndex(cards[ii].size('B'))));
        string sideAword = cards[ii].getWord('A',ltest::randIndex(cards[ii].size('A')));

        int numOfTries = 0;

        cout << sideAword << ": ";

        while (!cin.eof() && isWrong)
        {
            numOfTries++;
            timeStart = boost::chrono::system_clock::now();
            getline(cin, response);
            timeDiff = boost::chrono::system_clock::now() - timeStart;
            if (cin.eof()) break; // Break loop if CTRL-D (EOF) is entered

            /* options processing */
            if ( response[0] == '-' ) /* if hint */
            {
                if(response[1]=='s') break;
                cout << myhint.handle(response,false);
                cout << ltest::whitespace(sideAword.size());
            }
            else /* no hint, check response */
            {
                isWrong = ltest::isInvalidAnswer(response,cards[ii].getSideB());
                if (isWrong)
                {
                    if (verbose) cout << "You are " \
                                      << lcsPercent(cards[ii].getWord('B',0),response) \
                                      << "% correct." \
                                      << endl;
                    if (verbose) cout << correctness(response,cards[ii].getWord('B',0)) << endl;
                    if ( (numOfTries % 5) == 0 && !disableHintMsg)
                    {
                        cout << ltest::hintOptions(sideAword.size()) << endl;
                        cout << sideAword << ": ";
                    }
                    else
                        cout << ltest::whitespace(sideAword.size());
                }
                else if( verbose ) cout << "Right!" << endl;
            }
        }
        /* finish this card */
        cards[ii].recordPerformance(numOfTries,isWrong,timeDiff.count());
        isWrong = true;
    }

    testResults(cards,verbose);

    cin.clear(); // Need to clear away the EOF somehow

    return 0;
}