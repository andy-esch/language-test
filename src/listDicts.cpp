/*
 *  listDicts.cpp
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
#include "listDicts.h"
#include "functions.h"

int getTxtFiles(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    string temp;
    if ( (dp  = opendir(dir.c_str())) == NULL )
        return errno;

    while ((dirp = readdir(dp)) != NULL)
    {
        temp = string(dirp -> d_name);
        if ( temp.size() > 4 )
            if ( !temp.compare(temp.size() - 3, 3, "txt") ) // Only store .txt files
                files.push_back(temp);
    }

    closedir(dp);

    return 0;
}

//void listDicts(char dictType[])   

/* Perhaps we could pass a character to denote which type of dictionary we want
 to choose from such as n = nouns, v = sideA, etc. or something fancier
 eventually? and perhaps different types of sorting of output, which is fairly
 easy with strings */

string listDicts(void)
{ 
    string dir("./vocab/"), dictPick;
    vector<string> files;
    vector<string>::iterator iter;
    unsigned short numOfDicts = 1, dictInt = 0, longestName = 0;
    int retValue = getTxtFiles(dir,files);

    // If directory is not found -- do something different instead?
    if ( retValue != 0 )
    {
        cout << "Error " << retValue << ": Could not open the directory '" << dir << "'" << endl;
        cout << "Exiting program." << endl;
        exit(0);
    }

    cout << endl;
    if ( !files.empty() ) // If files are found
    {
        for (iter = files.begin(); iter != files.end(); ++iter)
            if ((*iter).size() > longestName)
                longestName = (*iter).size();

        cout << "The following dictionaries are available: \n" << endl;

        for (iter = files.begin(); iter != files.end(); ++iter)
        {
//            unsigned short strSize = (*iter).size(); // unused

            cout << '\t' << setw(2) << numOfDicts << ". " << *iter \
                 << setw(longestName - (*iter).size() + 9) \
                 << numberOfWords(dir+*iter) << " words" << endl;

            numOfDicts++;
        }
        cout << endl;
        ltest::takeInput(dictPick, "Select a dictionary for more information.  Type 'exit' to exit.");

            // TODO: The following six lines needed to be cleaned up!  dictInt is not well-defined
        dictInt = atoi( &(dictPick.at(0)) );
        
        if ( ltest::exitProg(dictPick.c_str(),cin.eof()) || dictInt <= 0 || dictInt > files.size() )
            exit(0);
        else
            dictPick = dir + files.at(dictInt - 1);
    }
    else    // If files are not found
    {
        // This doesn't handle cases where no files are found... but input() does
        cout << "No dictionaries found.\n" \
             << "Select a dictionary for more information.  " \
             << "Type 'exit' to exit." << endl;        
        ltest::takeInput(dictPick);

        if ( ltest::exitProg(dictPick.c_str(),cin.eof()) )
            exit(0);
    }

    cout << "You picked " << dictPick << endl;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    // returns full path of file, e.g. "./vocab/sideA.txt"
    return dictPick;
}

/* Counts the number of entries in a quiz file */
unsigned short numberOfWords(string fileName)
{
    ifstream inFile(fileName.c_str(),ifstream::in);
    string temp;
    unsigned short size = 0;
    if ( inFile.is_open() )
    {
        while ( !inFile.eof() )     // Have something to skip empty lines?
        {
            getline(inFile,temp);
            if (temp == "")
                continue;
            size++;
            temp.clear();
        }
        inFile.close();
    }
    else
        cout << "could not open file" << endl;

    return size;
}
