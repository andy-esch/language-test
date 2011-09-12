/*
 *  functions.cpp
 *  
 *  Description:
 *
 *
 *  Created by Peter Eschbacher on 9/11/11.
 *
 */

#include "functions.h"

extern bool debug;

// Mimics string compare -- returns 1 if there is no match
bool compareAll(vector<string> & ws, string test)
{
    bool isWrong = true;

    for (int i = 0; i < ws.size(); i++)
        if ( !test.compare(ws[i]) )
            isWrong = false;

    return isWrong;
}

void hintOptions(void)
{
    cout << '\a';
    cout << "\tWant a letter?  Type '-letter' or '-l'." << endl;
    cout << "\tWant the answer?  Type '-answer' or '-a'." << endl;
    cout << "\tWant the number of letters?  Type '-number' or '-n'" << endl;
}    

void input(vector<wordSet> & ws, char * inFilename)
{
    // Do some error-checking to make sure there are the proper number of
    //   columns, proper encoding(? not binary), etc.
    string temp1, temp2;
    int pos, posWidth = 1;
    ifstream infile(inFilename,ifstream::in);
    struct wordSet tempset;
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

bool isnew(vector<wordSet> & ws, string test, long unsigned int & index)
{   // Returns true if 'test' is not already in the vector ws (i.e., if its new)
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

void num2ordinal(int num)
{   // Takes an integer, prints its ordinal
    if (num == 1)
        cout << "first";
    else if (num == 2)
        cout << "second";
    else if (num == 3)
        cout << "third";
    else if (num == 4)
        cout << "fourth";
    else if (num == 5)
        cout << "fifth";
    else if (num == 6)
        cout << "sixth";
    else if (num == 7)
        cout << "seventh";
    else if (num == 8)
        cout << "eigth";
    else if (num == 9)
        cout << "ninth";
    else if (num == 10)
        cout << "tenth";
    else if (num == 11)
        cout << "eleventh";
    else if (num == 12)
        cout << "twelfth";
    else if ( (num % 10) == 1)
        cout << num << "st";
    else if ( (num % 10) == 2)
        cout << num << "nd";
    else if ( (num % 10) == 3)
        cout << num << "rd";
    else
        cout << num << "th";
}

void populate(wordData * prob, const int size)
{
    double invSize = 1.0 / static_cast<double> (size);
    for (int i = 0; i < size; i++)
        prob[i].probability = invSize;
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

int randIndex(int num)
{
    return (rand() % num);
}

double reaction(double time, int wrdsz)
{
        // 0.28 = seconds per letter if wpm = 100 and avg word is 6 letters long
    double reactionTime = time - 0.28 * wrdsz;
    if (reactionTime < 0.0)
        reactionTime = 0.0;
    if (debug) cout << "reactionTime = " << reactionTime << endl;

    return reactionTime;
}

int weightedIndex(wordData * data, int numEntries)
{
    extern boost::mt19937 gen;
    double prob[numEntries];
        // Copy probabilities to simple array so partial_sum() can use it.
        // It's possible that this step isn't necessary but I cannot figure out a
        // way to use consecutive pointers in the partial_sum() function for the
        // structure data[ii].probability
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

void wordSpaces(int wordLength)
{
    for (int k = 0; k < wordLength + 2; k++)
        cout << " ";
}