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

void progPrefs::cmdLineInput(int argc, char **argv, char * inFile)
{
    int c;
    while ( (c = getopt(argc, argv, ":i:hdl")) != -1)
    {
        switch (c)
        {
            case 'i': // Input non-default dictionary
                strcpy(inFile,argv[optind-1]);
                break;
            case ':':
                if (optopt == 'i')
                {   // Hmm, this is slightly redundant with what input() does
                    cerr << "Warning: Option '-i' must have more than one argument." << endl;
                    cout << "Type a new file name to continue or 'exit' to exit program." << endl;
                    cin >> inFile;
                    if ( ltest::exitProg(inFile,cin.eof()) ) // if 'exit', exit program
                        exit(0);
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                }
                break;
            case 'h': // Print usage info then exit
                cout << ltest::help(argv[0]);
                exit(0);
            case 'l': // List available dictionaries
                strcpy(inFile,listDicts().c_str());
                break;
            case '?':
                cerr << "Option '-" << static_cast<char> (optopt) \
                     << "' is not valid." << endl;
                break;
            default:
                cerr << "Invalid commandline options." << endl;
                ltest::help(argv[0]);
                exit(0);
                break;
        }
    }
}

usInt progPrefs::changeProgOptions(Account & acct)
{
    int option = 0;
    
    while (option != 3)
    {
        cout << "The following variables are set: \n" \
             << "1: verbose = " << (acct.getVerbose()?"on":"off") << '\n' \
             << "2: User = " << acct.getName() << '\n' \
             << "3: return to main screen.\n" \
             << endl \
             << "Enter a number to change its value" << endl;
        // TODO: Change this line to something like option = readint(">> ");
        option = atoi(readline(">> "));

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
