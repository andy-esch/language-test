/*
 *  Language quiz program.
 *      Takes in a two-column file, stores it, and then quizzes and then quizzes
 *      the user on the translations.
 *
 *  Future improvements: 
 *      * requiz badly scored words more frequently -- Implemented!
 *      * lets the user choose to be quizzed in english (answer in spanish), 
 *        in spanish (answer in english), or randomly (answering in the 
 *        opposite language to which the question was asked)
 *      * What is a way to choose what to be quizzed over? Such as just 
 *        switching all verbs instances with verbos?
 *      * Support for regular expressions?
 *      * International characters (accents, ñ, oumlaut, etc.)
 *      * More even timing mechanism that takes word length into account
 *      * Punctuation for certain options (. for pause time, : for clue, 
 *        $ for skip, etc.) or just the words (hint, pause, etc.) with a 
 *        dash in front?
 *      * Name memory!  Something like having an 'account'.  It allows the
 *        the program to load previous performance so you don't always have to
 *        start anew.
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
 *        -- Think about the complex data structures (worddata and wordset) and 
 *            see if there's one that is smarter, more convenient, or less complex
 *
 *  Created by Otto Hasselblad on 4/29/11.
 *  Edited by Otto Sep. 9.  Added weightedIndex function
 *
 */

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ios;
using std::setw;
using std::string;
using std::vector;

boost::mt19937 gen;

class wordset {
public:
    vector<string> verbos;
    vector<string> verbs;
};

class worddata {
public:
    unsigned int numAsked;
    float percentRight;
    float avgTime;
    double probability;
    unsigned int rank;
    void updateScore(int, bool, double, int, worddata *);
private:
    double reweight(int, double, double);
};

int randIndex(int);
void input(vector<wordset> &, char *);
bool compareAll(vector<string> & ws, string test);
bool isnew(vector<wordset> &, string, long unsigned int &);
double reaction(double, int);
void printHelp(char * progName);
void wordSpaces(int wordLength);
double strength(bool ans, double diff);
void populate(worddata *, const int);
int weightedIndex(worddata *, int);
void num2ordinal(int num);

bool debug = false;

int main(int argc, char **argv)
{
    /*****        Initialize Variables        *****/
    srand(time(NULL));
    time_t timeStart, timeEnd;
    string temp;
    char inFile[] = "verbs.txt";
    vector<wordset> spen;
    int numEntries = 0, longestWord = 0, c, hintNum;
    bool controlling, verbose = true, isWrong = true;
    gen.seed(static_cast<unsigned int>(std::time(0))); // initialize random seed

//    vector<wordset> * answer = &spen;
//    vector<wordset> * question = &spen;

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
    input(spen,&inFile[0]);        // Take entries from the file inFile, put into spen
    numEntries = spen.size();
    worddata * wordy = new worddata[numEntries];
    for (int i = 0; i < numEntries; i++)
    {
        wordy[i].numAsked = 0;
        wordy[i].percentRight = 0.0;
        if (spen[i].verbos[0].size() > longestWord)    // Find longest Spanish word for column spacing
            longestWord = spen[i].verbos[0].size();    // Store it's size (used to set column widths)
    }
    /*****     Initialize other things     *****/
    populate(wordy,numEntries);

    cout << "Okay, it's all read in." << endl;
    if (debug) cout << "Number of entries = " << numEntries << endl;
    if (debug) cout << "spen[" << numEntries << "].verbs.size() = " << spen[numEntries-1].verbs.size() << endl;
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
            if (cin.eof()) break;        // Break loop if CTRL-D (EOF) is entered
            if ( temp[0] == '-' )
            {
                if ( temp[1] == 'h' && hintNum != spen[i].verbos[j].size() )
                {
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
                wordy[i].worddata::updateScore(i, isWrong, \
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
    cout << setw(longestWord+11) << "Summary" << endl;
    for (int i = 0; i < 16; i++)
        cout << "=-";
    cout << endl;
    cout << setw(longestWord) << "Word" << setw(9) << "Score" << setw(13) << "Reaction" << setw(13) << "Probab" << endl;
    cout << setw(longestWord) << "----" << setw(9) << "-----" << setw(13) << "--------" << setw(13) << "------" << endl;
    cout.setf(ios::fixed);
    cout.precision(2);

    for (int i = 0; i < numEntries; i++)
    {
        cout << setw(longestWord) << spen[i].verbos[0];
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

int randIndex(int num)
{
    return (rand() % num);
}

void worddata::updateScore(int pos, bool wrong, double timeDiff, int numOfEntries, worddata * wordSet)
{
    double weight = ( wrong ? 1.0 : -1.0 ) * strength(wrong,timeDiff);
    if (debug) cout << "weight = " << weight << endl;
    double beta = 1.0 - weight * wordSet[pos].probability;
    double alpha = beta + weight;
    if (debug)
    {
        cout << "Since the word is " << (wrong?"wrong":"right") << " its probability ";
        cout << (wordSet[pos].probability > (alpha*wordSet[pos].probability)?"decreases":"increases") << endl;
        cout << "beta = " << beta << ", alpha = " << alpha << endl;
    }

    // Update probability of this word coming up again
    for (int ii = 0; ii < numOfEntries; ii++)
    {
        if ( ii != pos )
            wordSet[ii].probability *= beta;
        else
            wordSet[ii].probability *= alpha;
    }

    // Update number of individual queries of word
    numAsked++;

    // Update scoring percentage
    if (numAsked == 1)
        (wrong)?(percentRight = 0.0):(percentRight = 1.0);
    else if (!wrong && numAsked > 1)
        percentRight = reweight(numAsked,percentRight,1.0);
    else if (wrong && numAsked > 1)
        percentRight = reweight(numAsked,percentRight,0.0);

    // Update timing information
    avgTime = reweight(numAsked,avgTime,timeDiff);
}

double worddata::reweight(int num, double old, double newish)
{
    double nd = static_cast<double> (num);
    return ((nd - 1.0) * old + newish)/nd;
}

// Copies text file inFilename into memory for use in this program
void input(vector<wordset> & ws, char * inFilename)
{
    // Do some error-checking to make sure there are the proper number of 
    //   columns, proper encoding(? not binary), etc.
    string temp1, temp2;
    int pos, posWidth = 1;
    ifstream infile(inFilename,ifstream::in);
    struct wordset tempset;
    long unsigned int j;        // Stores index for repeat entry, given by isnew()

    if (!infile.is_open())
    {
        cout << "File '" << inFilename << "' does not exist as specified." << endl;
        cout << "Enter another filename (enter 0 to exit): ";
        cin >> inFilename;
        if (inFilename[0] == '0')
            exit(0);
        else
            infile.open(inFilename,ifstream::in);
    }

    while ( !infile.eof() )
    {
        getline(infile, temp1);
        posWidth = 1;
        pos = temp1.find("\t");                // Default delimiter
        if (pos == -1 || temp1 == "")        // Skip empty lines
            continue;
        else if (temp1.find(",") != -1)        // Is the delimiter ","?
            pos = temp1.find(",");
        else if (temp1.find("  ") != -1)    // Is the delimiter "  "?
        {
            pos = temp1.find("  ");
            posWidth = 2;
        }
        temp2 = temp1;
        temp1.erase(pos,temp1.size());
        temp2.erase(0,pos+posWidth);

        if ( isnew(ws,temp1,j) )
        {
            tempset.verbos.push_back(temp1);
            tempset.verbs.push_back(temp2);
            ws.push_back(tempset);
            tempset.verbos.erase(tempset.verbos.begin());
            tempset.verbs.erase(tempset.verbs.begin());
        }
        else // is not new
        {
            ws[j].verbos.push_back(temp1);
            ws[j].verbs.push_back(temp2);
        }
    }

    infile.close();
}
// Returns true if 'test' is not already in the vector ws
bool isnew(vector<wordset> & ws, string test, long unsigned int & index)
{
    bool isNew = true;

    if (ws.size() == 0)
        isNew = true;
    else
    {
        for (int i = 0; i < ws.size(); i++)
        {
            if ( !test.compare(ws[i].verbos[0]) )
            {
                isNew = false;
                index = i;
                break;
            }
        }
    }
    return isNew;
}
// Mimics string compare -- returns 1 if there is no match
bool compareAll(vector<string> & ws, string test)
{
    bool isWrong = true;

    for (int i = 0; i < ws.size(); i++)
        if ( !test.compare(ws[i]) )
            isWrong = false;

    return isWrong;
}

double reaction(double time, int wrdsz)
{
    // 0.28 = seconds per letter if wpm = 100 and avg word is 6 letters long
    double reactionTime = time - 0.28 * wrdsz;
    if (reactionTime < 0.0)
        reactionTime = 0.0;
    if (debug) cout << "reactionTime = " << reactionTime << endl;

    return reactionTime;
//    return time;
//    return ( ( time - 0.3 ) / ( (double) wrdsz ) );
}

void wordSpaces(int wordLength)
{
    for (int k = 0; k < wordLength + 2; k++)
        cout << " ";
}

double strength(bool wrong, double diff)
{
    double score;
    // Replace inner if-structures with an exponential function?
    if (wrong)
    {    // Probability increase with response time for wrong answers 
        // Quick responses are proportional to smaller probability differentials
        if (diff < 2.0)
            score = 0.03;
        else if (diff < 4.0)
            score = 0.06;
        else if (diff < 8.0)
            score = 0.12;
        else if (diff < 16.0)
            score = 0.18;
        else
            score = 0.24;
    }
    else
    {    // Probability decreases with response times for correct answers
        // Quick responses are proportional to larger probabilty differentials
        if (diff < 1.0)
            score = 0.24;
        else if (diff < 2.0)
            score = 0.18;
        else if (diff < 4.0)
            score = 0.12;
        else if (diff < 8.0)
            score = 0.06;
        else if (diff < 16.0)
            score = 0.03;
        else
            score = 0.015;
    }

    return score;
}

void populate(worddata * prob, const int size)
{
    double invSize = 1.0 / static_cast<double> (size);
    for (int i = 0; i < size; i++)
        prob[i].probability = invSize;
}

int weightedIndex(worddata * data, int numEntries)
{
    double prob[numEntries];
    // Copy probabilities to simple array so partial_sum() can use it.
    // It's possible that this step isn't necessary but I cannot figure out a
    // way to use consecutive pointers in the partial_sum() function for the
    // structure data[ii].probability...
    for (int ii = 0; ii < numEntries; ii++)
        prob[ii] = data[ii].probability;

    vector<double> cumulative;
    std::partial_sum(&prob[0], &prob[0] + numEntries, \
                     std::back_inserter(cumulative));
    if (debug) cout << "partial sum calculated" << endl;
    boost::uniform_real<> dist(0.0, cumulative.back());
    boost::variate_generator<boost::mt19937&, boost::uniform_real<> > die(gen, dist);
    return (std::lower_bound(cumulative.begin(), cumulative.end(), die()) - cumulative.begin());
}

void num2ordinal(int num)
{
    if (num == 1)
        cout << "first";
    if (num == 2)
        cout << "second";
    if (num == 3)
        cout << "third";
    if (num == 4)
        cout << "fourth";
    if (num == 5)
        cout << "fifth";
    if (num == 6)
        cout << "sixth";
    if (num == 7)
        cout << "seventh";
    if (num == 8)
        cout << "eigth";
    if (num == 9)
        cout << "ninth";
    if (num == 10)
        cout << "tenth";
}

void printHelp(char * prog)
{
    cout << "Commandline language learner. Version something." << endl;
    cout << "Kandy Software. Always wary." << endl;
    cout << endl;
    cout << "usage:" << endl;
    cout << "  " << prog << " [options]" << endl;
    cout << endl;
    cout << "options:" << endl;
    cout << "    -i <string>    input file name" << endl;
    cout << "    -v             turn off verbose output" << endl;
    cout << "    -h             print out this help menu" << endl;
    cout << "    -d             print debugging information to troubleshoot" << endl;
    cout << endl;

}