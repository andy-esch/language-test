/*
 *  Language quiz program.
 *        Takes in a two-column file, stores it, and then quizzes and then quizzes
 *         the user on the translations.
 *
 *        Future improvements:
 *            *x requiz badly scored words more frequently -- Implemented!
 *            * lets the user choose to be quizzed in english (answer in spanish),
 *                in spanish (answer in english), or randomly (answering in the
 *                opposite language to which the question was asked)
 *                * What is a way to choose what to be quizzed over? Such as just
 *              switching all verbs instances with verbos?
 *            * Support for regular expressions?
 *            * International characters (accents, ñ, oumlaut, etc.)
 *            * More even timing mechanism that takes word length into account
 *            * Punctuation for certain options (. for pause time, : for clue,
 *                $ for skip, etc.) or just the words (hint, pause, etc.) with a
 *                dash in front?
 *          * Name memory!  Something like having an 'account'.  It allows the
 *              the program to load previous performance so you don't always
 *              have to start anew.
 *
 *  Make it so that while it is waiting for input or something like that
 *    an OpenMP section or something like that does the 'smart picker'
 *    algorithm in the background to reweight the probability of being
 *    picked as the next quiz item.
 *
 *
 *  To do:
 *        -- Make everything more organized
 *        -- Better commenting to explain confusing features
 *        -- More-descriptive variable names
 *        -- Think about the complex data structures (worddata and wordSet) and
 *            see if there's one that is smarter, more convenient, or less complex
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

using std::cout;
using std::cin;
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
    int numEntries = 0, lengthLongestWord = 0, c, hintNum;
    bool controlling, verbose = true, isWrong = true;
    gen.seed(static_cast<unsigned int>(std::time(0))); // initialize random seed

//  Below: Rough idea on how to implement choosing whether to be quizzed on one
//  language or the other, but the data structure prevents easy access since
//  spen's type is vector<wordSet>, where wordSet is composed of two vectors of
//  strings.  This would be a lot easier to implement if the synonyms weren't
//  a part of the design.
//  vector<wordSet> * answer = &spen;
//  vector<wordSet> * question = &spen;

    /*****     Take optional input from command line     *****/
    while ( (c = getopt(argc, argv, ":i:vhd")) != -1 )
    {
        switch (c)
        {
            case 'i': // Input non-default dictionary
                strcpy(inFile,argv[optind-1]);
                break;
            case 'v': // Verbose output
                verbose = false;
                break;
            case 'h': // Print usage info then exit
                printHelp(argv[0]);
                exit(0);
            case 'd': // Show debug output info
                debug = true;
                break;
            default:
                break;
        }
    }

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
        if (debug) cout << "New word: " << endl;
        cout << spen[i].verbs[j] << ": ";
        while (!cin.eof() && isWrong)
        {
            timeStart = time(NULL);
            getline(cin, temp);
            timeEnd = time(NULL);
            if (cin.eof()) break;   // Break loop if CTRL-D (EOF) is entered
            if ( temp[0] == '-' )   // This structure feels a bit weak
            {
                if ( temp[1] == 'h' && hintNum != spen[i].verbos[j].size() )
                {
                    cout << "The ";
                    num2ordinal(hintNum+1);
                    cout << " letter is '" << spen[i].verbos[j][hintNum] << "'" << endl;
                    hintNum++;
                }
                else if ( temp[1] == 'h' && (hintNum == spen[i].verbos[j].size()) )
                    cout << "You have the full word via hints!" << endl;
                else if ( temp[1] == 'a' )
                {
                    cout << "Answer: " << spen[i].verbos[j] << endl;
                    timeEnd = timeStart + 100;
                }
            }
            isWrong = compareAll(spen[i].verbos, temp);

            if ( !cin.eof() && (temp[0] != '-') )
            {
                if ( verbose ) cout << " --- You are " << \
                ((isWrong)?("wrong, try again!"):("right!")) << endl;
                wordy[i].wordData::updateScore(i, isWrong, \
                                               reaction(difftime(timeEnd,timeStart), \
                                                        spen[i].verbos[j].size()), \
                                               numEntries, wordy);
            }
            if (isWrong) wordSpaces(spen[i].verbs[j].size());
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
            isWrong = 1;
            hintNum = 0;
        }
    }

    /******      Summary of Results      ******/
    cout << endl;
    cout << endl;
    cout << setw(lengthLongestWord+11) << "Summary" << endl;
    for (int i = 0; i < 16; i++)
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