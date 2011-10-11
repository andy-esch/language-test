/*
 *  listfiles.h
 *  
 *  Description: Lists txt files in the specified directory.  Similar to the
 *                  ls function in Linux
 *  
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
#include <fstream>
#include <iomanip>

#include "functions.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::ifstream;
using std::setw;

int getTxtFiles(string, vector<string> &);
//void listDicts(char[]);
string listDicts();
int numberOfWords(string);
