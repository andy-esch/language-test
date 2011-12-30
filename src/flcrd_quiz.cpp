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
    usInt ii = 0;
    bool isWrong = true, disableHintMsg = false;
    vector<Flashcard> cards;
    string response, prompt;
    SmartPicker * picker;

    Hint myhint("  ", acct.getVerbose());
    char * temp = NULL;

    /* Choose flashcard set */
    strcpy(inFile,listDicts().c_str());

    cards[0].input(cards,inFile);   // wonky -- input() should be a friend instead of a Flashcard member function?

    cout << "Pick how you're quizzed:\n" \
         << "   1. for LeastPicked\n" \
         << "   2. for Adaptive\n" \
         << "   3. for LeastCorrect\n" << endl;
    cin >> ii;

    switch (ii)
    {
        case 1:
            cout << "You picked LeastPicked" << endl;
            picker = new LeastPicked;
            break;
        case 2:
            cout << "You picked Adaptive" << endl;
            picker = new Adaptive(cards.size());
            break;
        case 3:
            cout << "You picked LeastCorrect" << endl;
            picker = new LeastCorrect;
            break;
        case 4:
            cout << "You picked WalkThrough" << endl;
            picker = new WalkThrough;
            break;
        default:
            cout << "Your choice isn't valid, so you're getting LeastPicked" << endl;
            picker = new LeastPicked;
            break;
    }

    do
    {
        ii = picker->getNextIndex(cards);

        // could we conditionally set this instead?
        myhint.setKey( cards[ii].getWord('B',ltest::randIndex(cards[ii].size('B'))) );
        string sideAword = cards[ii].getWord('A',ltest::randIndex(cards[ii].size('A')));

        int numOfTries = 0;

        prompt = sideAword;

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
            else if ( response == "exit") break;
            else /* no hint, check response */
            {
                isWrong = ltest::isInvalidAnswer(response,cards[ii].getSideB());
                if (isWrong)
                {
                    if (acct.getVerbose())
                    {
                        cout << "You are " \
                             << wordCompare::lcsPercent(cards[ii].getWord('B',0),response) \
                             << "% correct.\n" \
                             << wordCompare::correctness(response,cards[ii].getWord('B',0)) << endl;
                    }

                    if ( (numOfTries % 5) == 0 && !disableHintMsg)
                        cout << ltest::hintOptions(sideAword.size()) << '\n' << sideAword << ": ";
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

    delete picker;

    return 0;
}

// EOF
