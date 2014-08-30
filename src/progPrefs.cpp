/*
 *  progPrefs.cpp
 *  
 *  Description:
 *     Functions to control the environment variables of ltest
 *
 *
 *  Created by Añdy Eschbacher on 10/6/11.
 *
 */

#include "progPrefs.h"

string progPrefs::help(char * progName)
{
    stringstream help;

    help << "Commandline language learner. Version 1.0 Beta\n"
         << "Kandy Software. Always wary.\n\n"
         << "usage:\n"
         << "  " << progName << " [options]\n"
         << "\n"
         << "options:\n"
         << "    -h             print out this help menu\n"
         << endl;

    return help.str();
}

void progPrefs::cmdLineInput(int argc, char **argv)
{
    int c;
    while ( (c = getopt(argc, argv, ":hdl")) != -1)
    {
        switch (c)
        {
            case 'h': // Print usage info then exit
                cout << help(argv[0]);
                exit(0);
            case '?':
                cerr << "Option '-" << static_cast<char> (optopt)
                     << "' is not valid." << endl;
                break;
            default:
                cerr << "Invalid commandline options." << endl; 
                help(argv[0]);
                exit(0);
                break;
        }
    }
}

usInt progPrefs::changeProgOptions(Account & acct)
{
    usInt option = 0;
    
    while (option != 3)
    {
        cout << "The following variables are set: \n" \
             << "1: verbose = " << (acct.getVerbose()?"on":"off") << '\n' \
             << "2: User = " << acct.getName() << '\n' \
             << "3: return to main screen.\n" \
             << "\n" \
             << "Enter a number to change its value." << endl;

        option = ltest::readint<usInt>(">> ");

        switch (option)
        {
            case 1:
                acct.setVerbose();
                break;
            case 2:
                acct.establishAccount();
                break;
            case 3:
                break;
            default:
                cerr << option << " is not a valid option." << endl;
                break;
        }
    }
    
    return 0;
}

// EOF
