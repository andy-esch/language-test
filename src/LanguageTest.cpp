/*
 *  LanguageTest.cpp
 *
 *  Language quiz program.
 *        Takes in a two-column file, stores it, and then quizzes and then quizzes
 *         the user on the translations.
 *
 *
 *  Created by Añdy Eschbacher on 4/29/11.
 *
 */

#include <cstdlib>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <climits>

#include "WordData.h"
#include "functions.h"
#include "Flashcard.h"
#include "listDicts.h"
#include "testResults.h"
#include "Hint.h"
#include "SmartPicker.h"
#include "cmdLineInput.h"
#include "wordCompare.h"
#include "Account.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

bool debug = false;

int main(int argc, char **argv)
{
    /*****    Initialize Variables    *****/
    bool verbose = false, isWrong = true;
    srand(time(NULL));
    char inFile[60] = "vocab/test.txt";
    Account acct;

    /*****    Take optional input from command line   *****/
    cmdLineInput(argc,argv,inFile,verbose,debug);

    /****    Language Quiz    *****/
    cout << "Beginning Quiz." << endl;
    time_t timeStart, timeEnd;
    bool disableHintMsg = false;

    vector<Flashcard> cards;
    string response;
    LeastCorrect picker;
    Hint myhint = Hint("  ",verbose);

//    Adaptive picker(cards.size());
    Flashcard temp;// uh, now we have to reference input like below... we need to change this
    temp.input(cards,inFile);   // wonky

    cout << "Beginning Quiz." << endl;
    unsigned short int i = USHRT_MAX;

    // Should this while loop be shifted to its own file flcard_quiz.cpp?
    /**    Flashcard Quiz    **/
    while ( !cin.eof() )    // Should there be other conditions? Yes, all probabilities can't be zero.
    {
        i = picker.leastCorrectIndex(cards,i);
        //unsigned int i = picker.adaptiveIndex(cards);

        string sideBword = cards[i].getWord('B',randIndex(cards[i].size('B')));
        string sideAword = cards[i].getWord('A',randIndex(cards[i].size('A')));

        myhint.setKey(sideBword);

        int numOfTries = 0;

        cout << sideAword << ": ";

        while (!cin.eof() && isWrong)
        {
            numOfTries++;
            timeStart = time(NULL); // let's use more accurate timer
            getline(cin, response);
            timeEnd = time(NULL);
            if (cin.eof()) break; // Break loop if CTRL-D (EOF) is entered
	    
            /* options switch */
            if ( response[0] == '-' )
            {
                if(response[1]=='s') break;     // Should this be 'continue' instead of 'break'?
                cout << myhint.handle(response,false);
            }
            else /* no hint, check response */
            {
                isWrong = isInvalidAnswer(response,cards[i].getSideB());
//                picker.setLevDistance(response,sideBword);

                if (isWrong)
                {
                    if (verbose) cout << correctness(response,cards[i].getWord('B',0)) << endl;
                    if ( (numOfTries % 5) == 0 && !disableHintMsg)
                    {
                        cout << hintOptions(sideAword.size()) << endl;
                        cout << sideAword << ": ";
                    }
                    else
                        cout << whitespace(sideAword.size());
                }
                else if( verbose ) cout << "Right!" << endl;
            }
        }
        /* finish this card */
        cards[i].recordPerformance(numOfTries,isWrong,(timeEnd-timeStart));
//        picker.updateProbsBasic(i,isWrong,static_cast<double> (timeEnd-timeStart));
        if (debug) cout << "updatedProbsAdvanced " << endl;
        isWrong = true;
        picker.printIndices(cards);
    }

    /**    Ask if s/he wants test results    **/
    testResults(cards,verbose);
    
//    cout << picker.probabilitySummary(cards) << endl;

    cout << goodbye(acct.getName()) << endl;

    //clean up goes here

    return 0;
}
