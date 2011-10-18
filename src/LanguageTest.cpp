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

#include "functions.h"
#include "Flashcard.h"
#include "testResults.h"
#include "Hint.h"
#include "SmartPicker.h"
#include "cmdLineInput.h"
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
    unsigned short int ii;

    vector<Flashcard> cards;
    string response;
    LeastPicked picker;
    Hint myhint = Hint("  ",verbose);

    cards[0].input(cards,inFile);   // wonky -- input() should be a friend
                                    // instead of a Flashcard member function?

    cout << "Beginning Quiz." << endl;

    // Should this while loop be shifted to its own file flcard_quiz.cpp?
    /**    Flashcard Quiz    **/
    while ( !cin.eof() )    // Should there be other conditions? Yes, all probabilities can't be zero.
    {
        ii = picker.getNextIndex(cards);      // retrieve new index

        string sideBword = cards[ii].getWord('B',randIndex(cards[ii].size('B')));
        string sideAword = cards[ii].getWord('A',randIndex(cards[ii].size('A')));

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
	    
            /* options processing */
            if ( response[0] == '-' )
            {
                if(response[1]=='s') break;
                cout << myhint.handle(response,false);
                cout << whitespace(sideAword.size());
            }
            else /* no hint, check response */
            {
                isWrong = isInvalidAnswer(response,cards[ii].getSideB());
                if (isWrong)
                {
                    if (verbose) cout << correctness(response,cards[ii].getWord('B',0)) << endl;
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
        cards[ii].recordPerformance(numOfTries,isWrong,(timeEnd-timeStart));
        isWrong = true;
    }

    /**    Ask if s/he wants test results    **/
    testResults(cards,verbose);
    
//    cout << picker.probabilitySummary(cards) << endl;

    cout << goodbye(acct.getName()) << endl;

    //clean up goes here

    return 0;
}
