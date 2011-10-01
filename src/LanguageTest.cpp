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
#include "wordSet.h"
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

  string mystr[] = {"Hello"};//{"hello (world)", "I am well (cooked)"};
  string testans = "I am well (cooked)";
  vector<string> testparen (mystr, mystr + sizeof(mystr) / sizeof(string) );
  bool testisWrong = isInvalidAnswer(testans,testparen);
  if(testisWrong)
    std::cout << "******Incorrecto!**********";
  else std::cout << "******Correcto!**********";

    /*****        Initialize Variables        *****/
    srand(time(NULL));
    time_t timeStart, timeEnd;
    string temp;
    char inFile[60];
    vector<wordSet> cards;
    vector<wordSet>::iterator spenit;  // Look into this as helping the q/a pointers
    unsigned int numEntries = 0, lengthLongestWord = 0, lHintNum = 0;
    int c;
    bool verbose = false, isWrong = true;
    bool disableHintMsg = false;
    gen.seed(static_cast<unsigned int>(std::time(0))); // initialize random seed
    extern int optopt; // Command line processing variable

    //  Below: Rough idea on how to implement choosing whether to be quizzed on one
    //  language or the other, but the data structure prevents easy access since
    //  spen's type is vector<wordSet>, where wordSet is composed of two vectors of
    //  strings.  This would be a lot easier to implement if the synonyms weren't
    //  a part of the design.
	//  Update: We could copy the addresses of all the entries of verbs, say,
	//   into an array, and the addresses of all the verbos into another array
	//   and have those as question/answer arrays with more flexibility with
	//   what is currently implemented... hmm...
	//  The following works roughly as expected, but only copies the first entry
	//   in the array
	//	string *answers[numEntries];
	//	for (int kk = 0; kk < numEntries; kk++)
	//	{
	//		answers[kk] = &(spen[kk].verbos[0]);
	//		cout << "answer " << kk << ": " << *answers[kk] << endl;
	//	}

    /*****     Take optional input from command line     *****/
    while ( (c = getopt(argc, argv, ":i:vhdl")) != -1 )
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
    numEntries = cards.size();

    if (debug) 
    {
        cout << "Summary of inputted contents: " << endl;
        for (int ii = 0; ii < numEntries; ii++)
            cards[ii].summarizeContents(ii);
        cout << endl;
    }
    wordData * wordy = new wordData[numEntries];
    // Populate wordData[]
    for (int ii = 0; ii < numEntries; ii++)
    {
        wordy[ii].populate(numEntries);

        // Find longest Spanish word for column spacing
        if (cards[ii].verbos[0].size() > lengthLongestWord)
            lengthLongestWord = cards[ii].verbos[0].size();
    }

    cout << "Okay, it's all read in." << endl;
    if (debug) cout << "Number of entries = " << numEntries << endl;
    cout << "Beginning Quiz." << endl;

    /*****      Language Quiz      *****/
    int i = weightedIndex(wordy, numEntries);
    int jverbos = randIndex(cards[i].verbos.size());	// verbos index
	int jverbs = randIndex(cards[i].verbs.size());	// verbs index
    while ( !cin.eof() )    // Should there be other conditions?
    {
        bool showWordSize = false;
        int numOfTries = 1;
        int verboSize = cards[i].verbos[jverbos].size();
        int verbSize  = cards[i].verbs[jverbs].size();

        if (debug)
        {
            cout << "second indices (jverbs, jverbos) = (" << jverbs << ", " << jverbos << ")" << endl;
            cout << "(verbSize, verboSize) = (" << verbSize << ", " << verboSize << ")" << endl;
            cout << "cin is " << (cin.good()?"":"not so ") << "good (cin = '" << cin.good() << "')" << endl;
            cout << "New word: " << endl;
            
        }
        cout << cards[i].verbs[jverbs] << ": ";
        while (!cin.eof() && isWrong)
        {
            timeStart = time(NULL); // The time diff is only to seconds, should we get a more accurate timing mechanism?
            getline(cin, temp);
            timeEnd = time(NULL);
            if (debug) cout << "You entered: " << temp << endl;
            if (cin.eof()) break;   // Break loop if CTRL-D (EOF) is entered
            if ( temp[0] == '-' )   // This structure feels a bit kludgey
            {
                switch (temp[1])
                {
                    case 'l':
                        if ( lHintNum < verboSize )
                        {
                            unsigned int incr = 1; // Should be moved elsewhere?
                            if (temp[2] == '\0')
                                incr = 1;
                            else if (atoi(&temp[2]) < 10 && atoi(&temp[2]) > 0)
                                incr = atoi(&temp[2]);
                            else
                                incr = 1;

                            lHintNum+=incr;
                            // If white space between current position and incremented position, increment hint
                            for (int ii = lHintNum-incr; ii < lHintNum; ii++)
                                if (cards[i].verbos[jverbos][ii] == ' ')
                                    lHintNum++;
                            
                            if (verbose)
                            {
                                cout << "The " << ordinal(lHintNum);
                                cout << " letter is '" << cards[i].verbos[jverbos][lHintNum-1] << "'" << endl;
                            }
                            wordy[i].updateScore(i, numEntries, \
                                                 wordy, 'l', incr);
                        }
                        else if ( lHintNum >= verboSize )
                            cout << "You have the full word via hints!" << endl;

                        cout << hint(verbSize, showWordSize, \
                                     verboSize, cards[i].verbos[jverbos], lHintNum);
                        break;
                    case 'a':
                        cout << "Answer: " << cards[i].verbos[0];
                        for (int ii = 1; ii < cards[i].verbos.size(); ii++)  // Print other possible answers
                            cout << ", " << cards[i].verbos[ii];
                        cout << endl;
                        timeEnd = timeStart + 100;  // Initial attempt at penalizing -- not effective
                        lHintNum = verboSize;
                        wordy[i].updateScore(i, numEntries, wordy, 'a');
                        break;
                    case 'n':
                        showWordSize = true;
                        cout << hint(verbSize, showWordSize, verboSize, \
                                     cards[i].verbos[jverbos], lHintNum);
                        wordy[i].updateScore(i, numEntries, wordy, 'n');
                        if (verbose)
                            cout << "Number of letters: " << verboSize << endl;
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
                        wordy[i].updateScore(i, numEntries, wordy, 's');
                        isWrong = false;
                        break;
                    case 'y':
                        /* The problem with this is that if they enter the synonym
                           they are using a correct answer -- so getting an answer
                           cheaply versus doing -a */
                        if (cards[i].verbos.size() == 1)
                            cout << "Sorry, no synonyms available for " << cards[i].verbs[jverbs] << endl;
                        else
                        {
                            int synonymIndex = randIndex(cards[i].verbos.size());
                            while (synonymIndex == jverbos)
                                synonymIndex = randIndex(cards[i].verbos.size());
                            cout << "Synonym: " << cards[i].verbos[synonymIndex] << endl;
                        }
                        wordy[i].updateScore(i, numEntries, wordy, 'y');
                        break;
                    case 'h':
                        cout << hintOptions(verbSize);
                        break;
                    default:
                        cout << "'" << temp << "' is not a hint option." << endl;
                        cout << hintOptions(4);
                        break;
                }
            }

            if ( !cin.eof() && (temp[0] != '-') )   // Don't update score here
            {                                       // if EOF or hint is given
	      isWrong = isInvalidAnswer(temp,cards[i].verbos);
                if ( verbose ) cout << "You are " << \
                    (isWrong?"wrong, try again!":"right!") << endl;

                // Update score
                wordy[i].updateScore(i, isWrong, \
                                     reaction(difftime(timeEnd,timeStart), \
                                              cards[i].verbos[jverbos].size()), \
                                     numEntries, wordy);
            }

            if (isWrong)
            {
                if ( (numOfTries % 5) == 0 && !disableHintMsg && temp[0] != '-' )
                {
                    cout << hintOptions(verbSize);
                    cout << endl;
                    cout << cards[i].verbs[jverbs] << ": ";
                }
                else
                    cout << whitespace(verbSize);
            }
            else if (temp[1] == 'a' && temp[0] == '-') whitespace(6); // This seems out of place
            numOfTries++;
        }

        if ( !cin.eof() )
        {
            if ( verbose )
            {
                cout << cards[i].verbos[0] << " has been asked " << wordy[i].numAsked << " times." << endl;
                cout << "You have " << 100.0 * wordy[i].percentRight << "% on \"" << cards[i].verbos[0] << "\"." << endl;
                cout << "With an average time of " << wordy[i].avgTime << "." << endl;
            }

            i = weightedIndex(wordy,numEntries);
            if (debug) cout << "first index = " << i << endl;
            jverbos = randIndex(cards[i].verbos.size()); // This can continue to rely on the randIndex() function?
			jverbs = randIndex(cards[i].verbs.size());
            isWrong = true;
            lHintNum = 0;
        }
    }

    /*****      Summary of Results      ******/
    testResults(cards,wordy,numEntries,lengthLongestWord,verbose);

    /*****      Close program      *****/
    delete[] wordy; // Are there any other clean-up things to do so that we're good programmers?

    return 0;
}
