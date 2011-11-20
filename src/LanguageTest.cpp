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
 *
 *  Create an alternate mode called 'direct feedback' where the user
 *  instantly learns her/his wrong answer -- or even slighly delayed -- kind of
 *  learning-machine like, and not being in the dark and moving onto another
 *  word instead, which could lead to some mental muddiness and focus on
 *  trouble words.
 *
 *  Contained lessons/quizzes.  Lessons that have a clear ending point so
 *  the student will feel a sense of satisfaction on completing a unit.
 *  They can be performance-related, time-related, number-of-items-related,
 *  or more...
 *
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include "functions.h"
#include "cmdLineInput.h"
#include "Account.h"

/* Quizzes */
#include "flcrd_quiz.h"
#include "numbers.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool debug = false;

int main(int argc, char **argv)
{
    /*****    Initialize Variables    *****/
    bool verbose = false;
    srand(time(NULL));                      // does this need to be initialized?
    char inFile[60] = "vocab/test.txt";
    Account acct;
    int score;

    /*****    Take optional input from command line   *****/
    cmdLineInput(argc,argv,inFile,verbose,debug);

    acct.establishAccount();
    
    int toDoOption = whatDoYouWantToDo();
    
    while (!cin.eof())
    {
        switch (toDoOption)
        {
            case 1:
                cout << "you chose flash cards" << endl;
                score = flcrd_quiz(verbose,inFile);
                cin.clear();
                break;
            case 2:
                cout << "you chose number quiz" << endl;
                score = numbers();
                cin.clear();
                break;
            case 3:
                cout << "you chose conjugations!" << endl;
                /* run conjugations program */
                break;
            case 4:
                cout << "you chose fill-in-the-blank" << endl;
                /* run fill-in-the-blank program */
                break;
            case 5:
                cout << "you chose the multiple choice quiz!" << endl;
                /* run multiple-choice program */
                break;
            case 6:
                cout << "you chose to see your account summary" << endl;
                /* print account summary */
                break;
            case 7:
                cout << "you chose to exit the program" << endl;
                cout << goodbye(acct.getName()) << endl;
                exit(0);
            default:
                cout << "hmm, that's not an option" << endl;
                break;
        }

        toDoOption = whatDoYouWantToDo();
    }

    cout << goodbye(acct.getName()) << endl;

    return 0;
}
