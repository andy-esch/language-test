/*
 *  functions.cpp
 *
 *  Description:
 *   Various non-class functions for LanguageTest.cpp
 *
 *
 *  Created by Añdy Eschbacher on 9/11/11.
 *
 */

#include "functions.h"

void ltest::welcomeMessage()
{
    cout << "\nWelcome to ltest!" << endl;
}

string ltest::readstring(string prompt)
{
    char * temp = NULL;
    temp = readline(prompt.c_str());
    string tempStr(temp);
    free(temp);
    return tempStr;
}

//  To be used to verify if a given test has been passed
//  This is only a prototype
bool ltest::pass(int numOfHints, int numEntries, float totalAvgTime, float totalAvgPercent)
{
    int numUnanswered = 0; // Delete this later, for use as prototype only
    bool passVar = ((numOfHints < (numEntries / 30)) && \
                    (totalAvgTime < 2.0) && \
                    (totalAvgPercent > 0.9) && \
                    (numUnanswered == 0));
    return passVar;
}

float ltest::howWrongIsIt(string test, string compare)
{
    /*
     * This function will tell the user how wrong their word is if they so
     * choose to know...  There are several ways to say how wrong they are, so
     * I don't know how to start... AE
     * Ideas:
     *  - percentage of correct letters? - but in correct order?
     *  - choosing similiar consonant?  b instead of v, etc.
     *  - chose correct gender
     *  - etc.
     *
     *  I think there must be a good algorithm out there we can use.  One in
     *  wordCompare measures the levenshtein distance between two words.
     */
    return 0.0;
}

string ltest::charToStr(char * chars)
{
    stringstream ss;
    ss << chars;
    return ss.str();
}

void ltest::addSpace(string & temp)
{
    if (!temp.empty())
        temp += " ";
}

usInt ltest::isAccented(string str)
{
    vector<string> set = {"á", "é", "í", "ó", "ñ", "ä", "ö", "ü", "å", "ß"};
    usInt accents = 0;

    for (usInt ii = 1; ii < str.length(); ii++)
    {
        for (usInt jj = 0; jj < set.size(); jj++)
//            if (str[ii] == set[jj])
                accents++;
    }
    

    return accents;
}

string ltest::prompt(const char * prmpt)
{
    return prmpt;
}

string ltest::commaAdder(const string str, const bool sign)
{
    string word(str);
    
    for (short jj = word.size() - 3;
         jj > 0;
         jj -= 3)
    {
        word.insert(jj,",");
    }
    
    if (!sign) word.insert(0,"-");
    
    return word;
}

vector<string> ltest::stripParentheses(vector<string> & words)
{
    vector<string> strippedWords = words;

    for (usInt ii = 0; ii < words.size(); ii++)
        strippedWords[ii] = stripParentheses(strippedWords[ii]);

    return strippedWords;
}

string ltest::stripParentheses(string original)
{
    string strippedWord = original;
    string paren(" (");

    if (strippedWord.find(paren) != string::npos)
        strippedWord.erase(strippedWord.begin() + strippedWord.find(paren), \
                           strippedWord.end());
    return strippedWord;
}

bool ltest::containsContraction(string str)
{
    return (str.find('\'') != string::npos);
}

// Mimics string compare -- returns 'true' if there is no match
// I don't like to do all this extra work for each case, but for now it works.
// Should we make this a member of the class Flashcard?

/* TODO: have a contraction converter: if "I'm" is present, convert to "I am", or
         at least score it correctly
 */

/* TODO: Conditionally strip the parenthesis -- only do that operation if necessary
 *
 */

bool ltest::isInvalidAnswer(string answer, vector<string> ws)
{
    vector<string> strippedws = stripParentheses(ws);
    bool isWrong = true;

    for (usInt ii = 0; ii < ws.size() && isWrong; ii++)
        if ( !answer.compare(ws[ii]) || !answer.compare(strippedws[ii]) )
        {
            isWrong = false;
            break;
        }

    return isWrong;
}

/* should be moved to Hint.cpp? */
string ltest::hintOptions(int leftmargin)
{
    stringstream hint;
    string lMargSpace = printWhitespace(leftmargin);
    hint << '\a' << endl; // Ring system bell
    hint << lMargSpace << "Want a letter?  Type '-l'." << endl;
    hint << lMargSpace << "Want more than one letter? Type '-l#', where # = a number 1 - 9." << endl;
    hint << lMargSpace << "Want the answer?  Type '-a'." << endl;
    hint << lMargSpace << "Want the number of letters?  Type '-n'." << endl;
    hint << lMargSpace << "Want to skip this word?  Type '-s'." << endl;
    hint << lMargSpace << "Want help?  Type '-h'." << endl;
    hint << lMargSpace << "Want out of here?  Type CTRL-D (End of file -- EOF)." << endl;
    hint << lMargSpace << "Want to turn these messages off?  Type '-d' to disable." << endl;
    return hint.str();
}

string ltest::ordinal(const int num)
{
    string ords[] = { "th", "st", "nd", "rd", "th", \
                      "th", "th", "th", "th", "th" };
    stringstream ord;
    ord << num << ords[num % 10];
    return ord.str();
}

string ltest::help(char * prog)
{
    stringstream help;
    help << "Commandline language learner. Version 1.0 Beta" << endl;
    help << "Kandy Software. Always wary." << endl;
    help << endl;
    help << "usage:" << endl;
    help << "  " << prog << " [options]" << endl;
    help << endl;
    help << "options:" << endl;
/* TODO: no longer an option? */
    help << "    -i <string>    input file name" << endl; 
    help << "    -l             list available dictionaries" << endl;
    help << "    -h             print out this help menu" << endl;
    help << endl;
    return help.str();
}

//int ltest::randIndex(const int num)
//{
//    return (rand() % num);
//}

/* obsolete? */
double ltest::reaction(const double time, const int numLttrs)
{
    // 0.28 = seconds per letter if wpm = 100 and avg word is 6 letters long
    double reactionTime = time - 0.28 * static_cast<double>(numLttrs);
    if (reactionTime < 0.0)
        reactionTime = 0.0;
#ifdef DEBUG
    cout << "reactionTime = " << reactionTime << endl;
#endif
    return reactionTime;
}

string ltest::goodbye(const string name)
{
    string goodbyes[] = {"Goodbye", "Hej då", "Sayonara", "¡Adiós",
                         "Adieu", "Ciao", "Tchüss", "Au revoir",
                         "Namaste"};

    return goodbyes[randIndex(9)] + (name==""?"":", ") + name + "!";
}

// Returns true if 'exit' or 'quit' is entered
bool ltest::exitProg(const char * test, bool cinEOF)
{
    bool exiting = (!strcmp(test,"exit") || \
                    !strcmp(test,"'exit'") || \
                    !strcmp(test,"quit") || \
                    !strcmp(test,"'quit'") || \
                    cinEOF);
    return exiting;
}

int ltest::whatDoYouWantToDo(const string name)
{
    string options[] = {"flash cards", "numbers", "conjugations", \
                        "fill-in-the-blank", "multiple choice", \
                        "change user", "account summary", \
                        "set program options", "exit program"};

    usInt toDoOption;
    char * temp;

    cout << '\n' \
         << "Hello " << name << ", " \
         << "what do you want to do?\n" \
         << "Here are your options: " << endl;

    for (int ii = 1; ii <= 9; ii++)
        cout << '\t' << ii << ": " << options[ii - 1] << endl;

    // TODO: Change this line to something like option = readint(">> ");
    temp = readline(">> ");
    toDoOption = atoi(temp);
    free(temp);
    return toDoOption;
}

double ltest::inverse(const int num)
{
    if (num != 0)
        return (1.0 / static_cast<double> (num));
    else
        return 0; // return a nan() value?
}

// EOF
