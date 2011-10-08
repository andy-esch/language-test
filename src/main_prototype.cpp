/*
 *  main_prototype.cpp
 *  
 *  Description:
 *      Proto-type of what main() could look like if we implement some of the
 *      other things we are listing in our ToDo list.
 *
 *
 *  Created by Añdy Eschbacher on 9/23/11.
 *
 */

#include <iostream>
#include <cstdlib>
#include <string>

#include "functions.h"
#include "account.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool debug;

int main(int argc, char **argv)
{
    Account acct1;
    /** Find out if new or existing user -- load past info accordingly **/
    acct1.establishAccount();
    
    int toDoOption = whatDoYouWantToDo();

    while (!cin.eof())
    {
        switch (toDoOption)
        {
            case 1:
                cout << "you chose flash cards" << endl;
                /* run flashcard program */
                break;
            case 2:
                cout << "you chose conjugations!" << endl;
                /* run conjugations program */
                break;
            case 3:
                cout << "you chose fill-in-the-blank" << endl;
                /* run fill-in-the-blank program */
                break;
            case 4:
                cout << "you chose the multiple choice quiz!" << endl;
                /* run multiple-choice program */
                break;
            case 5:
                cout << "you chose to see your account summary" << endl;
                /* print account summary */
                break;
            case 6:
                cout << "you chose to exit the program" << endl;
                cout << "Goodbye!" << endl;
                exit(0);
            default:
                cout << "hmm, that's not an option" << endl;
                break;
        }
    
        whatDoYouWantToDo();

    }

    return 0;
}
