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
    bool verbose = false, isWrong = true;
    //srand(time(NULL));
    char inFile[60] = "vocab/sample.txt";
    int c;
    //gen.seed(static_cast<unsigned int>(std::time(0))); // initialize random seed
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

    /*****  Take optional input from command line   *****/
    cmdLineInput(argc,argv,inFile,verbose,debug);


    //****** Language Quiz **********//
    time_t timeStart, timeEnd;
    bool disableHintMsg = false;

    vector<Flashcard> cards;
    string response;
    SmartPicker picker;
    Hint myhint = Hint("  ",verbose);

    input(cards,&inFile[0]);

    cout << "Beginning Quiz." << endl;

    while ( !cin.eof() )    // Should there be other conditions? 
                            // --Yes - all probabilities can't be zero.
      {	
	int i = picker.leastPickedIndex(cards);
	
        string sideBword = cards[i].sideB[randIndex(cards[i].sideB.size())];
        string sideAword = cards[i].sideA[randIndex(cards[i].sideA.size())];
	
	myhint.setKey(sideBword);
        
	int numOfTries = 0;
	
        cout << sideAword << ": ";

        while (!cin.eof() && isWrong)
	  {
	    numOfTries++;
            timeStart = time(NULL); //yep - lets use more accurate timer
            getline(cin, response);
            timeEnd = time(NULL);
            if (cin.eof()) break; // Break loop if CTRL-D (EOF) is entered
	    
	    /* options switch */
            if ( response[0] == '-' )
	      { 
		if(response[1]=='s') break;
		cout << myhint.handle(response,false);
	      }
            /* else check response */
	    else
	      {
		isWrong=isInvalidAnswer(response,cards[i].sideB);
		
		if (isWrong)
		  {
		    if( verbose ) cout << "Wrong!" << endl;
		    if ( (numOfTries % 5) == 0 && !disableHintMsg)
		      {
			cout << hintOptions(sideAword.size()) << endl;
			cout << sideAword << ": ";
		      }
		    else
		      cout << whitespace(sideAword.size());
		  }
		else if( verbose ) 
		  {
		    cout << "Right!" << endl;
		  }
	      }
	  }
	//ready to move onto next word!
	cards[i].recordPerformance(numOfTries,isWrong,(timeEnd-timeStart));
	isWrong = true;
      }

    testResults(cards,verbose);

    cout << goodbye() << endl;

    //clean up goes here

    return 0;
}
