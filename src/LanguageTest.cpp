/*
 *  LanguageTest.cpp
 *
 *  Language quiz program.
 *        Takes in a two-column file, stores it, and then quizzes and then quizzes
 *         the user on the translations.
 *
 *
 *  Created by Otto Hasselblad on 4/29/11.
 *
 */

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <cstdlib>
#include <cstring>
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
    /*****        Initialize Variables        *****/
    srand(time(NULL));
    time_t timeStart, timeEnd;
    string temp;
    char inFile[30];
    vector<wordSet> spen;
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

//    vector< vector<string> > * answer = &(spen.verbs);
//    vector< vector<string> > * question = &spen.verbos;

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
                printHelp(argv[0]);
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
                printHelp(argv[0]);
                exit(0);
                break;
        }
    }

    /*****      Input Dictionary     *****/
    input(spen,&inFile[0]);
    numEntries = spen.size();
    wordData * wordy = new wordData[numEntries];
    // Populate wordData arrays -- turn this into a class function somehow?
    for (int i = 0; i < numEntries; i++)
    {
        wordy[i].numAsked = 0;
        wordy[i].percentRight = 0.0;

        // Find longest Spanish word for column spacing
        if (spen[i].verbos[0].size() > lengthLongestWord)
            lengthLongestWord = spen[i].verbos[0].size();
    }
    /*****     Initialize other things     *****/
    populate(wordy,numEntries);

    cout << "Okay, it's all read in." << endl;
    if (debug) cout << "Number of entries = " << numEntries << endl;
    cout << "Beginning Quiz." << endl;

    /*****      Language Quiz      *****/
    int i = weightedIndex(wordy, numEntries);
    int j = randIndex(spen[i].verbs.size());
    while ( !cin.eof() )
    {
        int numOfTries = 1;
        int verboSize = spen[i].verbos[j].size();
        int verbSize = spen[i].verbs[j].size();
        bool knowWordSize = false;
        if (debug) cout << "New word: " << endl;
        cout << spen[i].verbs[j] << ": ";
        while (!cin.eof() && isWrong)
        {
            timeStart = time(NULL);
            getline(cin, temp);
            timeEnd = time(NULL);
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
                            for (int ii = lHintNum-incr; ii < lHintNum; ii++)
                            { // If white space between current position and incremented position, increment hint
                                if (spen[i].verbos[j][ii] == ' ')
                                    lHintNum++;
                            }
                            
                            if (verbose)
                            {
			      cout << "The " << ordinal(lHintNum);
			      cout << " letter is '" << spen[i].verbos[j][lHintNum-1] << "'" << endl;
                            }
                            wordy[i].updateScore(i, numEntries, wordy, \
                                                 'l', incr);
                        }
                        else if ( lHintNum >= verboSize )
                            cout << "You have the full word via hints!" << endl;

                        hintPrint(verbSize, knowWordSize, \
                                  verboSize, spen[i].verbos[j], lHintNum);
                        break;
                    case 'a':
                        cout << "Answer: " << spen[i].verbos[j] << endl;
                        timeEnd = timeStart + 100;  // Initial attempt at penalizing -- not effective
                        lHintNum = verboSize;
                        wordy[i].updateScore(i, numEntries, wordy, 'a');
                        break;
                    case 'n':
                        if (knowWordSize) // Hmm, is this necessary?
                            cout << "You already got this answer." << endl;
                        else
                        {
                            knowWordSize = true;
                            hintPrint(verbSize, knowWordSize, verboSize, \
                                      spen[i].verbos[j], lHintNum);
                        }
                        if (verbose)
                            cout << "Number of letters: " << verboSize << endl;
                        wordy[i].updateScore(i, numEntries, wordy, 'n');
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
                    case 'h':
                        hintOptions(verbSize);
                        break;
                    default:
                        cout << "'" << temp << "' is not a hint option." << endl;
                        hintOptions(4);
                        break;
                }
            }

            if ( !cin.eof() && (temp[0] != '-') )   // Don't update score here
            {                                       // if EOF or hint is given
                isWrong = compareAll(spen[i].verbos, temp);
                if ( verbose ) cout << "You are " << \
                    (isWrong?"wrong, try again!":"right!") << endl;

                // Update score
                wordy[i].updateScore(i, isWrong, \
                                     reaction(difftime(timeEnd,timeStart), \
                                              spen[i].verbos[j].size()), \
                                     numEntries, wordy);
            }

            if (isWrong)
            {
                if ( (numOfTries % 5) == 0 && !disableHintMsg && temp[0] != '-' )
                {
                    hintOptions(verbSize);
                    cout << endl;
                    cout << spen[i].verbs[j] << ": ";
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
                cout << spen[i].verbos[0] << " has been asked " << wordy[i].numAsked << " times." << endl;
                cout << "You have " << 100.0 * wordy[i].percentRight << "% on \"" << spen[i].verbos[0] << "\"." << endl;
                cout << "With an average time of " << wordy[i].avgTime << "." << endl;
            }

            i = weightedIndex(wordy,numEntries);
            if (debug) cout << "first index = " << i << endl;
            j = randIndex(spen[i].verbs.size()); // This can continue to rely on the randIndex() function?
            if (debug) cout << "second index = " << j << endl;
            isWrong = true;
            lHintNum = 0;
        }
    }

    /*****      Summary of Results      ******/
    testResults(spen,wordy,numEntries,lengthLongestWord,verbose);

    /*****      Close program      *****/
    delete[] wordy;
    
    return 0;
}
