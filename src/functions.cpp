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

vector<string> stripParentheses(vector<string> & words)
{ 
    vector<string> strippedWords = words;

    for (int i = 0; i < words.size(); i++)
        strippedWords[i] = stripParentheses(strippedWords[i]);

    return strippedWords;
}

string stripParentheses(string original)
{
    string strippedWord = original;
    string paren(" (");

    if (strippedWord.find(paren) != string::npos)
        strippedWord.erase(strippedWord.begin() + strippedWord.find(paren), \
                           strippedWord.end());
    return strippedWord;
}

// Mimics string compare -- returns 'true' if there is no match
// I don't like to do all this extra work for each case, but for now it works.
// Should we make this a member of the class Flashcard?
bool isInvalidAnswer(string answer, vector<string> ws)
{
    vector<string> strippedws = stripParentheses(ws);
    bool isWrong = true;
    vector<string>::iterator it, it2;

    for (int ii = 0; ii < ws.size(); ii++)
        if ( !answer.compare(ws[ii]) || !answer.compare(strippedws[ii]) )
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

// isnew() is obsolete
//bool isnew(vector<Flashcard> & ws, string test, long unsigned int & index)
//{   // Returns true if 'test' is not already in the vector ws (i.e., if its new)
//    // Also sets the value where a non-new word occurs
//    bool isNew = true;
//
//    if (ws.size() == 0)
//        isNew = true;
//    else
//        for (int i = 0; i < ws.size(); i++)
//            if ( !test.compare(ws[i].sideB[0]) )
//            {
//                isNew = false;
//                index = i;
//                break;
//            }
//
//    return isNew;
//}


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

string goodbye(string name)
{
    string goodbyes[] = {"Goodbye", "Hej då", "Sayonara", "¡Adiós",
                         "Adieu", "Ciao", "Tchüss", "Au revoir",
                         "Namaste"};

    return goodbyes[randIndex(9)] + (name==""?"":", "+name) + "!";
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

double inverse(int num)
{
    if (num != 0)
        return (1.0 / static_cast<double> (num));
    else
        return 0; // return a nan() value?
}
