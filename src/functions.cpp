/*
 *  functions.cpp
 *  
 *  Description: Various non-class functions for LanguageTest.cpp
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */


// Header files are in functions.h -- not sure if this is good practice but it's
//  how the all the other header files are here.  
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

string hintOptions(int leftmargin)
{
  std::stringstream hint;
  hint << '\a' << endl;
  hint << whitespace(leftmargin) << "Want a letter?  Type '-l'." << endl;
  hint << whitespace(leftmargin) << "Want more than one letter? Type '-l#', where # = a number 1 - 9." << endl;
  hint << whitespace(leftmargin) << "Want the answer?  Type '-a'." << endl;
  hint << whitespace(leftmargin) << "Want the number of letters?  Type '-n'." << endl;
  hint << whitespace(leftmargin) << "Want to skip this word?  Type '-s'." << endl;
  hint << whitespace(leftmargin) << "Want help?  Type '-h'." << endl;
  hint << whitespace(leftmargin) << "Want out of here?  Type CTRL-D (End of file -- EOF)." << endl;
  hint << whitespace(leftmargin) << "Want to turn these messages off?  Type '-d' to disable." << endl;
  return hint.str();
}

string hint(int verbSize, bool knowWordSize, int verboSize, \
            string hintWord, int lHintNum)
{
  std::stringstream hint;
  hint << whitespace(verbSize-3) << "-> ";
    for (int jj = 0; jj < verboSize; jj++)
    {
        if (hintWord[jj] == ' ')
            hint << ' ';
        else if (jj < lHintNum)
            hint << hintWord[jj];
        else if (knowWordSize)
            hint << '-';
        else
            hint << ' ';
    }
    if (lHintNum >= verboSize)
        hint << " <-";
    hint << endl;
    return hint.str();
}
               
               
void input(vector<wordSet> & ws, char * inFile)
{
    // Do some error-checking to make sure there are the proper number of
    //   columns, proper encoding(? not binary), etc.
    string temp1, temp2;
    size_t found;
    int posWidth = 1;
    ifstream infile(inFile,ifstream::in);
    wordSet tempset;
    long unsigned int j;    // Stores index for repeat entry, given by isnew()

    while (!infile.is_open())
    {
        if (debug) cout << "in input()" << endl;
        cout << "File '" << inFile << "' does not exist as specified." << endl;
        cout << "Enter another filename (or 'exit' to exit): ";
        cin >> inFile;
        if (cin.eof() || !strcmp(inFile,"exit") || !strcmp(inFile,"'exit'"))
        {
            cout << endl;
            exit(0);
        }
        else
            infile.open(inFile,ifstream::in);
    }

    cout << "Inputting vocabulary from '" << inFile << "'" << endl;
    while ( !infile.eof() )
    {
        getline(infile, temp1);
        posWidth = 1;
        found = temp1.find("\t");         // Find delimiter (default is tab)
        if (found == string::npos || temp1 == "")        // Skip empty lines
            continue;
        temp2 = temp1;                      // Make a copy of the line read in
        temp1.erase(0,found+1);      // Cut out one language
        temp2.erase(found,temp1.size()+1);    // Cut out other language

        insertWords(temp1, tempset, 1); // Uhm, this doesn't seem so smart somehow
        insertWords(temp2, tempset, 2);
        ws.push_back(tempset);
        tempset.clearWS();  // Clean for next user
        temp1.clear();
        temp2.clear();
    }

    infile.close();
}

void insertWords(string words, wordSet & tempset, int step)
{
    size_t found;
    cout << "words are: '" << words << "'" << endl;
    while ( words.find(",") != string::npos )
    {
        found = words.rfind(",");
        string tempWord = words.substr(found+1);
        cout << "New word: " << tempWord << endl;
        switch (step)
        {
            case 1:
                cout << "case : " << step << endl;
                tempset.verbs.push_back(tempWord);
                break;
            case 2:
                cout << "case : " << step << endl;
                tempset.verbos.push_back(tempWord);
                break;
        }
        words.erase(found);
    }
    cout << "New word: " << words << endl;
    switch (step)
    {
        case 1:
            cout << "case : " << step << endl;
            tempset.verbs.push_back(words); // Catch non-comma case
            break;
        case 2:
            cout << "case : " << step << endl;
            tempset.verbos.push_back(words);
            break;
    }
}

bool isnew(vector<wordSet> & ws, string test, long unsigned int & index)
{   // Returns true if 'test' is not already in the vector ws (i.e., if its new)
    // Also sets the value where a non-new word occurs
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


string ordinal(int num)
{
  string ords[10] = { "th", "st", "nd", "rd", "th", "th", "th", "th",	\
		      "th", "th"};
  std::stringstream ord;
  ord << num << ords[num%10];
  return ord.str();
}


void populate(wordData * prob, const int size)
{
    double invSize = 1.0 / static_cast<double> (size);
    for (int i = 0; i < size; i++)
        prob[i].probability = invSize;
}

void printHelp(char * prog) // Have a 'help' stream?
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
    cout << "    -l             list available dictionaries" << endl;
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

string whitespace(int length)
{
  string whitespace;
  for (int k = 0; k < length + 2; k++)
      whitespace += " ";
  return whitespace;
}
