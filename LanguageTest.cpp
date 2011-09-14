/*
 *  LanguageTest.cpp
 *
 *  Language quiz program.
 *        Takes in a two-column file, stores it, and then quizzes and then quizzes
 *         the user on the translations.
 *
 *  Future improvements:
 *      * requiz badly scored words more frequently -- Implemented!
 *      * lets the user choose to be quizzed in english (answer in spanish), in
 *        spanish (answer in english), or randomly (answering in the opposite
 *        language to which the question was asked)
 *      * What is a way to choose what to be quizzed over? Such as just
 *        switching all verbs instances with verbos?
 *      * Support for regular expressions?
 *      * International characters (accents, ñ, oumlaut, etc.)
 *      * More even timing mechanism that takes word length into account
 *      * Name memory!  Something like having an 'account'.  It allows the
 *        the program to load previous performance so you don't always
 *        have to start anew.
 *
 *  Make it so that while it is waiting for input or something like that an 
 *  OpenMP section or something like that does the 'smart picker' algorithm in
 *  the background to reweight the probability of being picked as the next quiz
 *  item.
 *
 *
 *  To do:
 *      -- Penalize for taking hints -- perhaps more severe as more letters are
 *          gotten.  A big whack if a whole word is revealed.  Minimal for
 *          numbers.  One way to easily implement this could be overloading
 *          the updateScores function
 *      -- Hints that are synonyms but in the language you are less familiar
 *          with -- in this case, only give spanish synonyms
 *      -- Make everything more organized
 *      -- Better commenting to explain confusing features
 *      -- More-descriptive variable names
 *      -- Think about the complex data structures (worddata and wordSet) and
 *          see if there's one that is smarter, more convenient, or less complex
 *      -- Sort summary differently by user request (ws by spanish word, we by
 *          english word, sc by score, re by reaction, pr by probability, etc.)
 *      -- Ask what the user wants to do at the beginning of the program (once
 *          new features are added other than the flash card one currently)
 *      -- Verb conjugations!
 *      -- Add multiple lists as a combined vocab
 *      -- Keep adding words as time goes by if test-taker is doing well enough
 *          I.e., start with as smaller set, keep increasing it's size.  Perhaps
 *          there could be an '-s' option to say initial and final test size
 *      -- Command line option to find available dictionaries... Something
 *          like 'ls *.txt'
 *      -- An antonym quiz
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
#include <iomanip>
#include <iostream>
#include <vector>

#include "wordData.h"
#include "functions.h"
#include "wordSet.h"
#include "listDicts.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::setw;
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
    char inFile[] = "verbs.txt";
    vector<wordSet> spen;
    unsigned int numEntries = 0, lengthLongestWord = 0, lHintNum = 0;
    int c;
    bool controlling, verbose = false, isWrong = true;
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
                {
                    cerr << "Error: Option '-i' must have more than one argument." << endl;
                    cout << "Type a new file name to continue or 'exit' to exit program." << endl;
                    cin >> inFile;
                    if ( !strcmp(inFile,"exit") ) // if are equal, exit program
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
            case 'l': // List available dictionaries and exit
                strcpy(inFile,listDicts().c_str()); // Eventually add it so it'll show a specific type of dictionary
                cout << "inFile = '" << inFile << "'" << endl;
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

    if ( cin.fail() )
        cout << "cin failed in LanguageTest.cpp" << endl;
    /*****      Input Dictionary     *****/
    cout << "Inputting vocabulary from '" << inFile << "'" << endl;
    input(spen,&inFile[0]);
    numEntries = spen.size();
    wordData * wordy = new wordData[numEntries];
    // Populate wordData arrays
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
                                cout << "The ";
                                num2ordinal(lHintNum);
                                cout << " letter is '" << spen[i].verbos[j][lHintNum-1] << "'" << endl;
                            }
                            wordy[i].updateScore(i, numEntries, wordy, \
                                                 'l', verbSize);
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
                        if (verbose) cout << "Number of letters: " << verboSize << endl;
                        wordy[i].updateScore(i, numEntries, wordy, 'n');
                        break;
                    case 'd':
                        disableHintMsg = !disableHintMsg;
                        cout << (disableHintMsg?"Disabled":"Enabled");
                        cout << " hint messages. Pass '-d' again to ";
                        cout << (!disableHintMsg?"enable.":"disable.") << endl;
                        break;
                    case 's':
                        cout << "This will allow you to skip a word eventually." << endl;
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
            isWrong = compareAll(spen[i].verbos, temp);

            if ( !cin.eof() && (temp[0] != '-') )   // Don't update score here if hint is given
            {
                if ( verbose ) cout << "You are " << \
                    ((isWrong)?("wrong, try again!"):("right!")) << endl;

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
                    wordSpaces(verbSize);
            }
            else if (temp[1] == 'a' && temp[0] == '-') wordSpaces(6); // This seems oddly out of place
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

    /******      Summary of Results      ******/
    cout << endl;
    cout << endl;
    cout << setw(lengthLongestWord+11) << "Summary" << endl;
    for (int i = 0; i < lengthLongestWord + 16; i++)
        cout << "=-";
    cout << endl;
    cout << setw(lengthLongestWord) << "Word" << setw(9) << "Score" << setw(13) << "Reaction" << setw(13) << "Probab" << endl;
    cout << setw(lengthLongestWord) << "----" << setw(9) << "-----" << setw(13) << "--------" << setw(13) << "------" << endl;
    cout.setf(ios::fixed);
    cout.precision(2);

    for (int i = 0; i < numEntries; i++)
    {
        cout << setw(lengthLongestWord) << spen[i].verbos[0];
        if ( wordy[i].numAsked > 0 )
        {
            cout << setw(6) << static_cast<int> (100*wordy[i].percentRight) \
            << "% (" << wordy[i].numAsked << ")";
            cout << setw(9) << wordy[i].avgTime;
        }
        else
            cout << setw(6) << "   -" << setw(12) << "   -";

        cout << setw(15) << wordy[i].probability*100 << "%";

        if ( verbose )
        {
            cout << setw(15) << spen[i].verbs.size() << " word" << ((spen[i].verbs.size()>1)?"s:":":");
            for (int k = 0; k < spen[i].verbs.size(); k++)
                cout << setw(15) << spen[i].verbs[k];
        }
        cout << endl;
    }

    return 0;
}