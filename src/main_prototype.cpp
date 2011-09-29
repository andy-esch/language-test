/*
 *  main_prototype.cpp
 *  
 *  Description:
 *      Proto-type of what main() could look like if we implement some of the
 *      other things we are listing in our ToDo list.
 *
 *
 *  Created by Peter Eschbacher on 9/23/11.
 *
 */
#include <iostream>
#include <cstdlib>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int whatDoYouWantToDo();

int main(int argc, char **argv)
{
    int toDoOption = whatDoYouWantToDo();

    do
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
                exit(0);
            default:
                cout << "hmm, that's not an option" << endl;
                break;
        }
    
        whatDoYouWantToDo();

    } while (!cin.eof());

    return 0;
}

int whatDoYouWantToDo()
{
    string options[] = {"flash cards", "conjugations", "fill-in-the-blank", \
                        "multiple choice", "account summary", "exit program"};
    int toDoOption;
    cout << "What do you want to do?" << endl;
    cout << "Here are your options: " << endl;
    for (int ii = 1; ii <= 6; ++ii)
    {
        cout << '\t' << ii << ": " << options[ii-1] << endl;
    }
    cin >> toDoOption;
    return toDoOption;
}