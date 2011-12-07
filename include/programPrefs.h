/*
 *  programPrefs.h
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 10/6/11.
 *
 */

#ifndef PROGRAMPREFS_H
#define PROGRAMPREFS_H

#include <iostream>
#include <cstdlib>

#include "functions.h"
#include "listDicts.h"

using std::cin;
using std::cerr;
using std::cout;

namespace progPrefs {
    void cmdLineInput(int, char **, char *, bool &, bool &);
    void changeProgOptions(Account &);
} // progPrefs

#endif // PROGRAMPREFS_H

// EOF
