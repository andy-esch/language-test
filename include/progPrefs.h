/*
 *  progPrefs.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 10/6/11.
 *
 */

#ifndef PROGPREFS_H
#define PROGPREFS_H

#include <iostream>
#include <cstdlib>

#include <readline/readline.h>
#include <getopt.h>

#include "functions.h"
#include "listDicts.h"
#include "ltest_typedefs.h"
#include "Account.h"

using std::cin;
using std::cerr;
using std::cout;

namespace progPrefs {
    string help(char *);
    void cmdLineInput(int, char **);
    usInt changeProgOptions(Account &);
} // progPrefs

#endif // PROGPREFS_H

// EOF
