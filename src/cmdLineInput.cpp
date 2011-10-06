/*
 *  cmdLineOpts.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 10/6/11.
 *
 */

#include "cmdLineInput.h"

using std::cin;
using std::cerr;
using std::cout;

void cmdLineInput(int argc, char **argv, char * inFile, bool &verbose, bool &debug)
{
    int c;
    extern int optopt;
    while ( (c = getopt(argc, argv, ":i:vhdl")) != -1)
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
                    if ( exitProg(inFile) || cin.eof()) // if 'exit', exit program
                        exit(0);
                }
            case 'v': // Verbose output
                verbose = true;
                break;
            case 'h': // Print usage info then exit
                cout << help(argv[0]);
                exit(0);
            case 'd': // Show debug output info
                debug = true;
                break;
            case 'l': // List available dictionaries
                strcpy(inFile,listDicts().c_str());
                break;
            case '?':
                std::cerr << "Option '-" << static_cast<char> (optopt) << "' is not valid." << endl;
                break;
            default:
                std::cerr << "Invalid commandline options." << endl;
                help(argv[0]);
                exit(0);
                break;
        }
    }
}