/*
 *  readfiles.cpp
 *  
 *  Description:
 *
 *
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
using std::cout;
using std::endl;

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if ( (dp  = opendir(dir.c_str())) == NULL )
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        files.push_back(string(dirp->d_name));
    }

    closedir(dp);

    return 0;
}

//void listDicts(char dictType[])
void listDicts(void)
{
    string dir = string("."); // choose current directory
    vector<string> files = vector<string>();
    int numOfDicts = 1;
    getdir(dir,files);
    
    cout << endl;
    cout << "The following dictionaries are available: " << endl;
    cout << endl;
    for (unsigned int i = 0; i < files.size(); i++)
    {
        int strSize = files[i].size();
        if (strSize > 4)
            if ( !files[i].compare(strSize-3,3,"txt") )
            {
                cout << '\t' << numOfDicts << ": " << files[i] << endl;
                numOfDicts++;
            }
    }
    cout << endl;
}