/*
 *  flcrd_quiz.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 10/19/11.
 *
 */

#include "flcrd_quiz.h"

int flcrd_quiz(char * inFile, Account & acct)
{
    cout << "Beginning Flashcard Quiz." << endl;

    boost::chrono::system_clock::time_point timeStart;
    boost::chrono::duration<double> timeDiff;
    usInt ii;
    bool isWrong = true, disableHintMsg = false;
    vector<Flashcard> cards;
    string response;
    LeastPicked picker;
    Hint myhint("  ",acct.getVerbose());
    char * temp = NULL;
    
    /* Choose flashcard set */
    strcpy(inFile,listDicts().c_str());
    
    cards[0].input(cards,inFile);   // wonky -- input() should be a friend
                                    // instead of a Flashcard member function?
    
    do    // Should there be other conditions? Yes, all probabilities can't be zero.
    {
        ii = picker.getNextIndex(cards);

        // could we conditionally set this instead?
        myhint.setKey(cards[ii].getWord('B',ltest::randIndex(cards[ii].size('B'))));
        string sideAword = cards[ii].getWord('A',ltest::randIndex(cards[ii].size('A')));
        
        int numOfTries = 0;

        string prompt = sideAword;

        while (!cin.eof() && isWrong)
        {
            numOfTries++;

            timeStart = boost::chrono::system_clock::now();
            temp = readline((prompt + ": ").c_str());
            timeDiff = boost::chrono::system_clock::now() - timeStart;

            response = temp;

            if (ltest::exitProg(temp)) break;

            /* options processing */
            if ( response[0] == '-' ) /* if hint */
            {
                if ( response[1]=='s' ) break;

                cout << myhint.handle(response, false);
            }
            else if ( response == "*exit")
                return 0;
            else /* no hint, check response */
            {
                isWrong = ltest::isInvalidAnswer(response,cards[ii].getSideB());
                if (isWrong)
                {
                    if (acct.getVerbose())
                    {
                        cout << "You are " \
                        << wordCompare::lcsPercent(cards[ii].getWord('B',0),response) \
                        << "% correct." << endl \
                        << wordCompare::correctness(response,cards[ii].getWord('B',0)) << endl;
                    }

                    if ( (numOfTries % 5) == 0 && !disableHintMsg)
                    {
                        cout << ltest::hintOptions(sideAword.size()) << endl \
                             << sideAword << ": ";
                    }
                    else
                        prompt = ltest::printWhitespace(sideAword.size()-1);
                }
                else if (acct.getVerbose()) cout << "Right!" << endl;
            }
        }
        /* finish this card */
        cards[ii].recordPerformance(numOfTries,isWrong,timeDiff.count());
        isWrong = true;
    } while ( !ltest::exitProg(temp) );

    testResults(cards,acct.getVerbose());

    cin.clear(); // Need to clear away the EOF somehow

    return 0;
}
