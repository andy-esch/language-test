/*
 *  main_prototype.cpp
 *  
 *  Description:
 *
 *
 *  Created by Peter Eschbacher on 9/23/11.
 *
 */
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

char whatDoYouWantToDo();

int main(int argc, char **argv)
{
    char toDoOption;
    /* take in command line options */
    
    toDoOption = whatDoYouWantToDo();
    do
    {
        switch (toDoOption)
        {
            case 'f':
                cout << "you chose flash cards" << endl;
                /* run flashcard program */
                break;
            case 'c':
                cout << "you chose conjugations!" << endl;
                /* run conjugations program */
                break;
            case 's':
                cout << "you chose to see your account summary" << endl;
                break;
            default:
                cout << "hmm, that's not an option" << endl;
                break;
        }
    
        whatDoYouWantToDo();

    } while (!cin.eof());





    return 0;
}

char whatDoYouWantToDo()
{
    char toDoOption;
    cout << "What do you want to do?" << endl;
    cin >> toDoOption;
}