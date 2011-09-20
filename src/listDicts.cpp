/*
 *  readfiles.cpp
 *  
 *  Description: A function that prints out the available dictionaries.  It is
 *               similar to the ls function in *nix operating systems.
 *
 *  Extension:
 *      -- By pressing the dictionary number, the user can get a description of
 *          the dictionary or preview some of the words.
 *      -- by passing an optional argument to the command line (e.g., -l nouns),
 *          the user can specify the type of dictionary he/she is looking for.
 *      -- By pressing the dictionary number, the user can pick that dictionary
 *          and use it in the program -- easily achieved by using a return type
 *          that is just a string or char *.
 *
 *  Created by Añdy Eschbacher on 9/13/11.
 *
 */


#include <sys/types.h>
#include <cstdlib>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

int getTxtFiles(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    string temp;
    if ( (dp  = opendir(dir.c_str())) == NULL )
    {
        cout << "Error(" << errno << "). Could not open the directory '";
        cout << dir << "'." << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        temp = string(dirp->d_name);
        if ( temp.size() > 4 )
        {
            if ( !temp.compare(temp.size() - 3, 3, "txt") ) // Only store .txt files
                files.push_back(temp);
        }
    }

    closedir(dp);

    return 0;
}

//void listDicts(char dictType[])   // Perhaps we could pass a character to denote
                                    // which type of dictionary we want to choose from
                                    // such as n = nouns, v = verbs, etc.
                                    // or something fancier eventually?
                                    // and perhaps different types of sorting of
                                    // output, which is fairly easy with strings
string listDicts(void)
{ 
    string dir = string("./vocab/");
    string temp;
    vector<string> files = vector<string>();
    int numOfDicts = 1, dictPick;
    int retValue = getTxtFiles(dir,files);

    // If directory is not found -- do something different instead?
    if ( retValue != 0 )
    {
        cout << "Exiting program." << endl;
        exit(0);
    }

    cout << endl;
    if ( files.size() > 0 ) // If files are found
    {
        cout << "The following dictionaries are available: " << endl;
        cout << endl;
        for (unsigned int i = 0; i < files.size(); i++)
        {
            int strSize = files[i].size();
            cout << '\t' << numOfDicts << ": " << files[i] << endl;
            numOfDicts++;
        }
        cout << endl;
        cout << "Select a dictionary for more information.  Type 0 to exit." << endl;
        cin >> dictPick;
        if ( cin.eof() || dictPick == 0 )
            exit(0);
    }
    else    // If files are not found
    {   // We could do something where a person specifies a directory
        //  or specifies a specific file?
        
        cout << "No dictionaries found." << endl;
        cout << "Select a dictionary for more information.  Type 'exit' to exit." << endl;        
        cin >> temp;

        if ( cin.eof() || temp == "exit" )
            exit(0);

        files.push_back(temp);
        dictPick = 1;   // ensures return value has correct form
    }

    cin.clear();
    cin.ignore(10,'\n');

    // returns full path of file, e.g. "./vocab/verbs.txt"
    return dir + files[dictPick - 1];
}
