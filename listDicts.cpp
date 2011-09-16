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
 *  Created by Peter Eschbacher on 9/13/11.
 *
 */


#include <sys/types.h>
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
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        temp = string(dirp->d_name);
        if ( temp.size() > 4 )
        {
            if ( !temp.compare(temp.size() - 3, 3, "txt") )
                files.push_back(temp);
        }
    }

    closedir(dp);

    return 0;
}

//void listDicts(char dictType[])
string listDicts(void)
{ 
    string dir = string("./vocab"); // choose current directory
    vector<string> files = vector<string>();
    int numOfDicts = 1, dictPick;
    getTxtFiles(dir,files);

    cout << endl;
    cout << "The following dictionaries are available: " << endl;
    cout << endl;
    for (unsigned int i = 0; i < files.size(); i++)
    {
        int strSize = files[i].size();
        cout << '\t' << numOfDicts << ": " << files[i] << endl;
        numOfDicts++;
    }
    cout << endl;
    cout << "Select a dictionary for more information." << endl;
    cin >> dictPick;
    cin.ignore(2,'\n');
    cout << "You picked '" << files[dictPick - 1] << "'." << endl;
    
    return files[dictPick - 1];
}
