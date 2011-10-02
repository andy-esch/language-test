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

#include "wordData.h"
#include "functions.h"
#include "Flashcard.h"
#include "listDicts.h"
#include "testResults.h"

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


    /*****        Initialize Variables        *****/
    srand(time(NULL));
    time_t timeStart, timeEnd;
    char inFile[60] = "vocab/sample.txt";
    vector<Flashcard> cards;
    vector<Flashcard>::iterator spenit;  // Look into this as helping the q/a pointers
    unsigned int numFlashcards = 0, lHintNum = 0;
    int c;
    bool verbose = false, isWrong = true;
    bool disableHintMsg = false;
    gen.seed(static_cast<unsigned int>(std::time(0))); // initialize random seed
    extern int optopt; // Command line processing variable

    //  Below: Rough idea on how to implement choosing whether to be quizzed on one
    //  language or the other, but the data structure prevents easy access since
    //  spen's type is vector<Flashcard>, where Flashcard is composed of two vectors of
    //  strings.  This would be a lot easier to implement if the synonyms weren't
    //  a part of the design.
	//  Update: We could copy the addresses of all the entries of sideA, say,
	//   into an array, and the addresses of all the sideB into another array
	//   and have those as question/answer arrays with more flexibility with
	//   what is currently implemented... hmm...
	//  The following works roughly as expected, but only copies the first entry
	//   in the array
	//	string *answers[numFlashcards];
	//	for (int kk = 0; kk < numFlashcards; kk++)
	//	{
	//		answers[kk] = &(spen[kk].sideB[0]);
	//		cout << "answer " << kk << ": " << *answers[kk] << endl;
	//	}



    /*****     Take optional input from command line     *****/
    cout << "argc = " << argc << endl;
    while ( (c = getopt(argc, argv, ":i:vhdl")) != -1)
    {
        switch (c)
        {
            case 'i': // Input non-default dictionary
                strcpy(inFile,argv[optind-1]);
                break;
            case ':':
                if (optopt == 'i')
                {   // Hmm, this is slightly redundant with what input() does
                    cerr << "Warning: Option '-i' must have more than one argument." << endl;
                    cout << "Type a new file name to continue or 'exit' to exit program." << endl;
                    cin >> inFile;
                    if ( !strcmp(inFile,"exit") || !strcmp(inFile,"quit") || cin.eof()) // if 'exit', exit program
                        exit(0);
                }
            case 'v': // Verbose output
                verbose = true;
                break;
            case 'h': // Print usage info then exit
                cout << help(argv[0]);
                exit(0);
            case 'd': // Show debug output info
                debug = true;
                break;
            case 'l': // List available dictionaries
                strcpy(inFile,listDicts().c_str());
                break;
            case '?':
                std::cerr << "Option '-" << static_cast<char> (optopt) << "' is not valid." << endl;
                break;
            default:
                std::cerr << "Invalid commandline options." << endl;
                help(argv[0]);
                exit(0);
                break;
        }
    }

    



    /*****      Input Dictionary     *****/
    input(cards,&inFile[0]);
    cout << "Okay, it's all read in." << endl;



    /*****  Prepare an array of wordData objects **********/
    /*****  WordData can become a field in Flashcard ******/
    numFlashcards = cards.size();
    wordData * wordy = new wordData[numFlashcards];
    for (int i = 0; i < numFlashcards; i++)
    {
        wordy[i].populate(numFlashcards);
    }



    /******* Prepare variable for formatting purposes **********/
    unsigned int lengthLongestWord = 0;
    for (int i = 0; i < numFlashcards; i++)
    {
        if (cards[i].sideB[0].size() > lengthLongestWord)
            lengthLongestWord = cards[i].sideB[0].size();
    }




    /*****      Language Quiz      *****/
    cout << "Beginning Quiz." << endl;


    /************  Initialise response variable   *******************/
    string response;


    /************  Begin quiz execution ****************************/ 
    while ( !cin.eof() )    // Should there be other conditions?
    {

        /********     Choose a flashcard    ************/    
        int i = weightedIndex(wordy, numFlashcards);


        /************  Select synonym from flashcards  *****************/
	int synIndexB = randIndex(cards[i].sideB.size());
	int synIndexA = randIndex(cards[i].sideA.size());
        string sideBword = cards[i].sideB[synIndexB];
        string sideAword = cards[i].sideA[synIndexA];

        bool showWordSize = false;
        int numOfTries = 1;
        int sideBsize = sideBword.size();
        int sideAsize  = sideAword.size();

        cout << sideAword << ": ";

        while (!cin.eof() && isWrong)
        {
            timeStart = time(NULL); // The time diff is only to seconds, should we get a more accurate timing mechanism?
            getline(cin, response);
            timeEnd = time(NULL);
            if (cin.eof()) break;   // Break loop if CTRL-D (EOF) is entered


	    //**************** begin options switch **********************//
            if ( response[0] == '-' )   // This structure feels a bit kludgey
            {
	      // this can all be included in a getHints(response) method;
	      // variables that are required are:
	      // lJintNum, sideBsize, sideBword, wordy,
	      // First break into smaller methods...


	      // each hint needs to do some of the same things:
	      // 1. create a "next hint" string to output to screen
	      // 2. update score for flashcard
	      // 3. track how many hints have been given





                switch (response[1])
                {
                    case 'l':
		      //cout << letterHint(int lHintNum, bool verbose);
                      //uses: lHintNum, sideBsize, sideBword, response, functions::ordinal

		      if ( lHintNum < sideBsize )
                        {
                            unsigned int incr = 1; // Should be moved elsewhere?
                            if (response[2] == '\0')
                                incr = 1;
                            else if (atoi(&response[2]) < 10 && atoi(&response[2]) > 0)
                                incr = atoi(&response[2]);
                            else
                                incr = 1;

                            lHintNum+=incr;
                            // If white space between current position and incremented position, increment hint
                            for (int ii = lHintNum-incr; ii < lHintNum; ii++)
                                if (sideBword[ii] == ' ')
                                    lHintNum++;
                            
                            if (verbose)
                            {
                                cout << "The " << ordinal(lHintNum);
                                cout << " letter is '" << sideBword[lHintNum-1] << "'" << endl;
                            }
                            wordy[i].updateScore(i, numFlashcards, \
                                                 wordy, 'l', incr);
                        }
                        else if ( lHintNum >= sideBsize )
                            cout << "You have the full word via hints!" << endl;

                        cout << hint(sideAsize, showWordSize, \
                                     sideBsize, sideBword, lHintNum);
                        break;


                    case 'a':
                        cout << "Answer: " << cards[i].sideB[0];
                        for (int ii = 1; ii < cards[i].sideB.size(); ii++)  // Print other possible answers
                            cout << ", " << cards[i].sideB[ii];
                        cout << endl;
                        timeEnd = timeStart + 100;  // Initial attempt at penalizing -- not effective
                        lHintNum = sideBsize;
                        wordy[i].updateScore(i, numFlashcards, wordy, 'a');
			break;

                    case 'n':
                        showWordSize = true;
                        cout << hint(sideAsize, showWordSize, sideBsize, \
                                     sideBword, lHintNum);
                        wordy[i].updateScore(i, numFlashcards, wordy, 'n');
                        if (verbose)
                            cout << "Number of letters: " << sideBsize << endl;
                        break;

                    case 'd':
                        disableHintMsg = !disableHintMsg;
                        cout << (disableHintMsg?"Disabled":"Enabled");
                        cout << " hint messages. Pass '-d' again to ";
                        cout << (disableHintMsg?"enable.":"disable.") << endl;
                        break;

                    case 'e':
                        break;  // This hint will give an example usage?
                                //  Should it show it used in the language that
                                //  the answer is expected to be in?
                    case 's':
                        if (verbose) cout << "You skipped a word." << endl;
                        wordy[i].updateScore(i, numFlashcards, wordy, 's');
                        isWrong = false;
                        break;

                    case 'y':
                        /* The problem with this is that if they enter the synonym
                           they are using a correct answer -- so getting an answer
                           cheaply versus doing -a */
                        if (cards[i].sideB.size() == 1)
                            cout << "Sorry, no synonyms available for " << sideAword << endl;
                        else
                        {
                            int synonymIndex = randIndex(cards[i].sideB.size());
                            while (synonymIndex == synIndexB)
                                synonymIndex = randIndex(cards[i].sideB.size());
                            cout << "Synonym: " << cards[i].sideB[synonymIndex] << endl;
                        }
                        wordy[i].updateScore(i, numFlashcards, wordy, 'y');
                        break;

                    case 'h':
                        cout << hintOptions(sideAsize);
                        break;

                    default:
                        cout << "'" << response << "' is not a hint option." << endl;
                        cout << hintOptions(4);
                        break;
                }
            }


	    //***********************end of hints options ***************************//



	    if ( !cin.eof() && (response[0] != '-') )   // Don't update score here
            {                                       // if EOF or hint is given
	      isWrong = isInvalidAnswer(response,cards[i].sideB);
                if ( verbose ) cout << "You are " << \
                    (isWrong?"wrong, try again!":"right!") << endl;

                // Update score
                wordy[i].updateScore(i, isWrong, \
                                     reaction(difftime(timeEnd,timeStart), \
                                              sideBword.size()), \
                                     numFlashcards, wordy);
            }


            if (isWrong)
            {
                if ( (numOfTries % 5) == 0 && !disableHintMsg && response[0] != '-' )
                {
                    cout << hintOptions(sideAsize);
                    cout << endl;
                    cout << sideAword << ": ";
                }
                else
                    cout << whitespace(sideAsize);
            }
	    //else if (response[1] == 'a' && response[0] == '-') whitespace(6); // This seems out of place
	    numOfTries++;

        }


	//************************** end of isWrong and !cin.eof conditional while **************************************//

        if ( !cin.eof() )
        {
            if ( verbose )
            {
                cout << cards[i].sideB[0] << " has been asked " << wordy[i].numAsked << " times." << endl;
                cout << "You have " << 100.0 * wordy[i].percentRight << "% on \"" << cards[i].sideB[0] << "\"." << endl;
                cout << "With an average time of " << wordy[i].avgTime << "." << endl;
            }

            // i = weightedIndex(wordy,numFlashcards); //not understanding why this is here, so comment out for now.
            // if (debug) cout << "first index = " << i << endl;
            // synIndexB = randIndex(cards[i].sideB.size()); // This can continue to rely on the randIndex() function?
	    // synIndexA = randIndex(cards[i].sideA.size());

	 
	    /*********** reset values so that quiz continues   **************/

            isWrong = true;
            lHintNum = 0;
        }
    }

    //***************** end of quiz    *********************************/



    /*****      Summary of Results      ******/
    testResults(cards,wordy,numFlashcards,lengthLongestWord,verbose);


    /******    Clean up   ********************/
    delete[] wordy; // Are there any other clean-up things to do so that we're good programmers?


    /*****      Close program      *****/
    cout << goodbye() << endl;

    return 0;
}
