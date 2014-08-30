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

int flcrd_quiz(Account & acct)
{
    cout << "Beginning Flashcard Quiz." << endl;

    chr::system_clock::time_point timeStart;
    boost::chrono::duration<float> timeDiff;
    bool isWrong = true, disableHintMsg = false;
    vector<Flashcard> cards;
    string response, prompt;
    SmartPicker * picker;
    Hint myhint("  ", acct.getVerbose());

    /* Choose flashcard set, then input */
    cards[0].input(cards,listDicts());

    {
        int index = 1;
        cout << "Pick how you're quizzed:\n"
             << "   1. LeastPicked\n"
             << "   2. Adaptive\n"
             << "   3. LeastCorrect\n" 
             << "   4. Walk Through\n"
             << endl;
        index = ltest::readint<usInt>(">> ");

        switch (index)
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
    }

    do
    {
        picker->getNextIndex(cards);

        // could we conditionally set this instead?
        myhint.setKey(cards[picker->getCurrentIndex()].getWord('B',ltest::randIndex(cards[picker->getCurrentIndex()].size('B'))));
        string sideAword = cards[picker->getCurrentIndex()].getWord('A',ltest::randIndex(cards[picker->getCurrentIndex()].size('A')));

        usInt numOfTries = 0;

        prompt = sideAword;

        while (isWrong)
        {
            numOfTries++;
            timeStart = chr::system_clock::now();
            response = ltest::readstring(prompt + ": ");
            timeDiff = chr::system_clock::now() - timeStart;

            /* options processing */
            if ( response[0] == '-' ) /* if hint */
            {
                if ( response[1] == 's' ) break;
                else
                    cout << myhint.handle(response, disableHintMsg);
            }
            else if ( response == "exit" )
            {
                exitToMain = true;
                break;
            }
            else /* no hint, check response */
            {
/* TODO: if noun, and beginning with el or la (or los or las), and user
 *  gets the article correct, do not require them to keep typing that...
 */
                isWrong = ltest::isInvalidAnswer(response,cards[picker->getCurrentIndex()].getSideB());
                if (isWrong)
                {
                    if (acct.getVerbose())
                    {
                        cout << "You are " \
                             << wordCompare::lcsPercent(cards[picker->getCurrentIndex()].getWord('B',0),response) \
                             << "% correct.\n" \
                             << wordCompare::correctness(response,cards[picker->getCurrentIndex()].getWord('B',0)) << endl;
                    }

                    if ( (numOfTries % 5) == 0 && !disableHintMsg)
                    {
                        cout << myhint.help(sideAword.size())
                             << '\n';
                        prompt = sideAword;
                    }
                    else
                        prompt = ltest::printWhitespace(sideAword.size()-1);
                }
                else if (acct.getVerbose()) cout << "Right!" << endl;
            }
        }
        /* finish this card */
        cards[picker->getCurrentIndex()].recordPerformance(numOfTries,isWrong,timeDiff.count());
        isWrong = true;
//        cout << response << " has " << ltest::isAccented(response) << " accents" << endl;
    } while (!exitToMain);

    testResults(cards,acct.getVerbose());

    delete picker;

    return 0;
}

// EOF
