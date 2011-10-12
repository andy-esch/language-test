/*
 *  functions.cpp
 *  
 *  Description: Various non-class functions for LanguageTest.cpp
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#include "functions.h"

extern bool debug;

unsigned int findSmallest(const vector<Flashcard> &deck)
{
    unsigned int currentLowest = deck[0].data.numCorrect, temp;

    for (int ii = 1; ii < deck.size(); ii++)
    {
        temp = deck[ii].data.numCorrect;
        if (temp < currentLowest)
            currentLowest = temp;
    }
    return currentLowest;
}

//  To be used to verify if a given test has been passed
//  This is only a prototype
bool pass(int numOfHints, int numEntries, float totalAvgTime, float totalAvgPercent)
{
    int numUnanswered = 0; // Delete this later, for use as prototype only
    bool passVar = ((numOfHints < (numEntries / 30)) && \
                    (totalAvgTime < 2.0) && \
                    (totalAvgPercent > 0.9) && \
                    (numUnanswered == 0));
    return passVar;
}

float howWrongIsIt(string test, string compare)
{
    /* 
     * This function will tell the user how wrong their word is if they so
     * choose to know...  There are several ways to say how wrong they are, so
     * I don't know how to start... AE
     * Ideas:
     *  - percentage of correct letters? - but in correct order?
     *  - choosing similiar consonant?  b instead of p, etc.
     *  - chose correct gender
     *  - etc.
     *
     *  I think there must be a good algorithm out there we can use
     */
    return 0.0;
}

// Let's rewrite this as a pass by reference function instead so we don't have
// to pass all this info across memory, etc.
vector<string> stripParentheses(vector<string> words)
{ 
    vector<string> strippedWords = words;
    string paren(" (");
    size_t it;

    for (int i = 0; i < words.size(); i++)
    {
       it = strippedWords[i].find(paren);
       if (it != string::npos)
       {
         strippedWords[i].erase(strippedWords[i].begin() + strippedWords[i].find(paren), \
                                strippedWords[i].end());
       }
    }

    return strippedWords;
}

// Mimics string compare -- returns 1 if there is no match
// I don't like to do all this extra work for each case, but for now it works.
bool isInvalidAnswer(string answer, vector<string> & ws)
{
    vector<string> strippedws = stripParentheses(ws);
    bool isWrong = true;
    vector<string>::iterator it = ws.begin();

    for (it = ws.begin(); it != ws.end(); it++)
        if ( !answer.compare(*it) )
            isWrong = false;

    for (it = strippedws.begin(); it != strippedws.end(); it++)
        if ( !answer.compare(*it) )
            isWrong = false;

    return isWrong;
}


string hintOptions(int leftmargin)
{
    stringstream hint;
    hint << '\a' << endl; // Ring system bell
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

void input(vector<Flashcard> & ws, char * inFile)
{
    // Do some error-checking to make sure there are the proper number of
    //   columns, proper encoding(? not binary), etc.
    string temp1, temp2;
    size_t delimPos = string::npos;
    ifstream infile(inFile,ifstream::in);
    Flashcard tempset;
    int lineNum = 1, delimWidth = 1;
    string delimiters[] = {"\t","    ","   ","  "};

    while ( !infile.is_open() )
    {
        if (debug) cout << "in input()" << endl;
        cout << "File '" << inFile << "' does not exist as specified." << endl;
        cout << "Enter another filename (or 'exit' to exit): ";
        cin >> inFile;

        if (exitProg(inFile,cin.eof()))
        {
            cout << endl;
            exit(0);
        }
        else
            infile.open(inFile,ifstream::in);
        cin.clear();
        cin.ignore(10,'\n');
    }

    cout << "Inputting vocabulary from '" << inFile << "'" << endl;
    while ( !infile.eof() )
    {
        getline(infile, temp1);             // Read in line from file

        if (temp1 == "") continue;          // Skip empty lines

        // Find the delimiter
        for (int ii = 0; ii < 4 && delimPos == string::npos; ii++)
        {
            delimPos = temp1.find(delimiters[ii]);
            delimWidth = delimiters[ii].size();
        }

        if (delimPos == string::npos) // If no delims found, go to next line
        {
            cout << "Skipping: '" << temp1 << "'" << endl;
            temp1.clear();
            continue;
        }

        temp2 = temp1;                      // Make a copy of the line read in

        try // This my be redundant with previous if statement
        {
            temp1.erase(0,delimPos + delimWidth);
            temp2.erase(delimPos,temp2.size() - delimPos);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << "Caught: '" << e.what() << "' on line " << lineNum << endl;
            std::cerr << "Type: " << typeid(e).name() << endl;
            std::cerr << "Not inputting '" << temp1 << "'" << endl;
            continue;
        }
        catch ( std::exception &e )
        {
            std::cerr << "Caught: " << e.what() << endl;
            std::cerr << "Type: " << typeid(e).name() << endl;
            continue;
        }

        // Insert words into tempset
        insertWords(temp1, tempset, 1);
        insertWords(temp2, tempset, 2);

        // Put tempset into Flashcard vector
        ws.push_back(tempset);

        // Clear variables for next time through
        tempset.clearWS();
        temp1.clear();
        temp2.clear();
        delimPos = string::npos;

        lineNum++;
    }
    cout << endl;

    infile.close();
}



void insertWords(string words, Flashcard & tempset, int step)
{
    size_t found;
    if (debug) cout << "words are: '" << words << "'" << endl;

    while ( words.find(",") != string::npos )   // while comma is found
    {
        found = words.rfind(",");
        string tempWord = words.substr(found+1);
        if (debug) cout << "New word: " << tempWord << endl;
        switch (step)
        {
            case 1:
                if (debug) cout << "case : " << step << endl;
                tempset.sideA.push_back(tempWord);
                break;
            case 2:
                if (debug) cout << "case : " << step << endl;
                tempset.sideB.push_back(tempWord);
                break;
            default:
                break; // What should we do for this case?
        }
        words.erase(found);
    }

    if (debug) cout << "New word: " << words << endl;

    switch (step)   // Otherwise catch non-comma case
    {
        case 1:
            if (debug) cout << "case : " << step << endl;
            tempset.sideA.push_back(words);
            break;
        case 2:
            if (debug) cout << "case : " << step << endl;
            tempset.sideB.push_back(words);
            break;
        default:
            break;  // What should we do for this case?
    }
}

// isnew() is obsolete
bool isnew(vector<Flashcard> & ws, string test, long unsigned int & index)
{   // Returns true if 'test' is not already in the vector ws (i.e., if its new)
    // Also sets the value where a non-new word occurs
    bool isNew = true;

    if (ws.size() == 0)
        isNew = true;
    else
        for (int i = 0; i < ws.size(); i++)
            if ( !test.compare(ws[i].sideB[0]) )
            {
                isNew = false;
                index = i;
                break;
            }

    return isNew;
}


string ordinal(int num)
{
    string ords[10] = { "th", "st", "nd", "rd", "th", \
                        "th", "th", "th", "th", "th"};
    stringstream ord;
    ord << num << ords[num % 10];
    return ord.str();
}

int min(int val1, int val2)
{
    return (val1 > val2 ? val2 : val1);
}

string help(char * prog)
{
    stringstream help;
    help << "Commandline language learner. Version 1.0 Beta" << endl;
    help << "Kandy Software. Always wary." << endl;
    help << endl;
    help << "usage:" << endl;
    help << "  " << prog << " [options]" << endl;
    help << endl;
    help << "options:" << endl;
    help << "    -i <string>    input file name" << endl;
    help << "    -v             turn off verbose output" << endl;
    help << "    -l             list available dictionaries" << endl;
    help << "    -h             print out this help menu" << endl;
    help << "    -d             print debugging information to troubleshoot" << endl;
    help << endl;
    return help.str();
}

int randIndex(int num)
{
    return (rand() % num);
}

double reaction(double time, int numLttrs)
{
    // 0.28 = seconds per letter if wpm = 100 and avg word is 6 letters long
    double reactionTime = time - 0.28 * static_cast<double>(numLttrs);
    if (reactionTime < 0.0)
        reactionTime = 0.0;
    if (debug) cout << "reactionTime = " << reactionTime << endl;

    return reactionTime;
}

string whitespace(int length)
{
    string whitespace("");
    for (int k = 0; k < length + 2; k++)
        whitespace += " ";
    return whitespace;
}

string goodbye(void)
{
    string goodbyes[] = {"Goodbye", "Hej då", "Sayonara", "¡Adiós",
                         "Adieu", "Ciao", "Tchüss", "Au revoir",
                         "Namaste"};

    return goodbyes[randIndex(9)] + "!";
}

bool exitProg(const char * test, bool cinEof)
{
    bool exiting = (!strcmp(test,"exit") || \
                    !strcmp(test,"'exit'") || \
                    !strcmp(test,"quit") || \
                    !strcmp(test,"'quit'") || \
                    cinEof);
    return exiting;
}

int whatDoYouWantToDo(void)
{
    string options[] = {"flash cards", "conjugations", "fill-in-the-blank", \
        "multiple choice", "account summary", "exit program"};
    string languages[] = {"spanish/english", "french/english", "robot/english"};
    
    int toDoOption, lang;
    
    cout << "What do you want to do?" << endl;
    cout << "Here are your options: " << endl;
    for (int ii = 1; ii <= 6; ii++)
        cout << '\t' << ii << ": " << options[ii - 1] << endl;

    cin >> toDoOption;

    if (toDoOption != 6)
    {
        cout << "Which language do you want to work on?" << endl;
        for (int ii = 1; ii <= 3; ii++)
            cout << '\t' << ii << ": " << languages[ii - 1] << endl;
        cin >> lang;
    }

    return toDoOption;
}
