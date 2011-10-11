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

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>

#include "WordData.h"
#include "functions.h"
#include "Flashcard.h"
#include "listDicts.h"
#include "testResults.h"
#include "Hint.h"
#include "SmartPicker.h"
#include "cmdLineInput.h"
#include "wordCompare.h"


using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

boost::mt19937 gen;
bool debug = false;

int main(int argc, char **argv)
{
    /*****    Initialize Variables    *****/
    bool verbose = false, isWrong = true;
    srand(time(NULL));
    char inFile[60] = "vocab/test.txt";

    gen.seed(static_cast<unsigned int>(std::time(0))); // initialize random seed

    /*****    Take optional input from command line   *****/
    cmdLineInput(argc,argv,inFile,verbose,debug);

    /****    Language Quiz    *****/
    cout << "Beginning Quiz." << endl;
    time_t timeStart, timeEnd;
    bool disableHintMsg = false;

    vector<Flashcard> cards;
    string response;
    SmartPicker picker;
    Hint myhint = Hint("  ",verbose);

    input(cards,&inFile[0]);

    cout << "Beginning Quiz." << endl;

    while ( !cin.eof() )    // Should there be other conditions? Yes, all probabilities can't be zero.
    {	
        int i = picker.leastAskedIndex(cards);

        string sideBword = cards[i].sideB[randIndex(cards[i].sideB.size())];
        string sideAword = cards[i].sideA[randIndex(cards[i].sideA.size())];

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
                isWrong = isInvalidAnswer(response,cards[i].sideB);

                if (isWrong)
                {
                    if (verbose) cout << correctness(response,cards[i].sideB[0]) << endl;
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
        isWrong = true;
    }

    testResults(cards,verbose);

    cout << goodbye() << endl;

    //clean up goes here

    return 0;
}
