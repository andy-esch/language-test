/*
 *  Flashcard.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/19/11.
 *
 */

#include "Flashcard.h"

Flashcard::Flashcard(void)
          :sideA(0), sideB(0), data(), weight(0.0)
{
}

void Flashcard::toScreen(void)
{
    cout << "sideA: " << endl;

    for (usInt jj = 0; jj < sideA.size() - 1; jj++)
        cout << sideA[jj] << ", ";

    cout << sideA[sideA.size()-1] << endl;
    cout << "sideB: " << endl;

    for (usInt kk = 0; kk < sideB.size() - 1; kk++)
        cout << sideB[kk] << ", ";

    cout << sideB[sideB.size() - 1] << endl;
}


void Flashcard::recordPerformance(int numOfTries, bool isWrong, double responseTime)
{
    data.incrNumAsked();
    if (numOfTries == 1 && !isWrong)
    {
        data.incrNumCorrect();
        data.incrAnsTime(responseTime);
    }
}

vector<string> Flashcard::getSideA(void)
{
    return sideA;
}

string Flashcard::getWord(char side, usInt i) const
{
    if (side == 'A')
        return sideA[i];
    else
        return sideB[i];
}

vector<string> Flashcard::getSideB(void)
{
    return sideB;
}

usInt Flashcard::size(char side)
{
    if (side == 'A')
        return sideA.size();
    else
        return sideB.size();
}

usInt Flashcard::size(char side, usInt ind)
{
    if (side == 'A')
        return sideA[ind].size();
    else
        return sideB[ind].size();
}

void Flashcard::setWeight(usInt N)
{
    weight = ltest::inverse(N);
}

void Flashcard::clearWS(void)
{
    sideB.clear();
    sideA.clear();
}

/* TODO: Have a comment character -- ignore input after this character */

void Flashcard::input(vector<Flashcard> & ws, char * inFile)
{
    // Do some error-checking to make sure there are the proper number of
    //   columns, proper encoding(? not binary), etc.
    string temp1, temp2;
    size_t delimPos = string::npos;
    ifstream infile(inFile,ifstream::in);   // open file if possible
    Flashcard tempSet;
    unsigned short lineNum = 1, delimWidth = 1;
    string delimiters[] = {"\t","    ","   ","  "};

#ifdef DEBUG
    cout << "Inputting words from " << inFile << "." << endl;
#endif // DEBUG

    while ( !infile.is_open() )
    {
        cout << "File '" << inFile << "' does not exist as specified." << endl;
        cout << "Enter another filename (or 'exit' to exit): ";
        cin >> inFile;
        
        if (ltest::exitProg(inFile,cin.eof()))
        {
            cout << endl;
            exit(0);
        }
        else
            infile.open(inFile,ifstream::in);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    
    cout << "Inputting vocabulary from '" << inFile << "'" << endl;
    while ( !infile.eof() )
    {
        getline(infile, temp1);             // Read in line from file 
                                            /* Perhaps use
                                             *  getline(infile,temp1,'\t'); \\ gets to tab
                                             *  getline(infile,temp2,); \\ gets after tab
                                             */  
        
        if (temp1.empty()) continue;          // Skip empty lines
        else if (temp1.find('#') != string::npos)
        {
            cout << "Skipping the following line (comment): " << endl;
            cout << '\t' << temp1;
            continue;
        }
        
        // Find the delimiter
        for (int ii = 0; ii < 4 && delimPos == string::npos; ii++)
        {
            delimPos = temp1.find(delimiters[ii]);
            delimWidth = delimiters[ii].size();
        }
        
        if (delimPos == string::npos) // If no delims found, go to next line
        {
            cout << "Skipping: '" << temp1 << "'" << endl;
            temp1.clear();
            continue;
        }
        
        temp2 = temp1;                      // Make a copy of the line read in
        
        try // This may be redundant with previous if statement
        {
            temp1.erase(0,delimPos + delimWidth);
            temp2.erase(delimPos,temp2.size() - delimPos);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << "Caught: '" << e.what() << "' on line " << lineNum << endl;
            std::cerr << "Type: " << typeid(e).name() << endl;
            std::cerr << "Not inputting '" << temp1 << "'" << endl;
            continue;
        }
        catch ( std::exception &e )
        {
            std::cerr << "Caught: " << e.what() << endl;
            std::cerr << "Type: " << typeid(e).name() << endl;
            continue;
        }
        
        // Insert words into tempset
        insertWords(temp1, tempSet, 1);
        insertWords(temp2, tempSet, 2);
        
        // Put tempset into Flashcard vector
        ws.push_back(tempSet);
        
        // Clear variables for next time through
        tempSet.clearWS();
        temp1.clear();
        temp2.clear();
        delimPos = string::npos;
        
        lineNum++;
    }
    cout << endl;
    
    infile.close();
}

void Flashcard::insertWords(string words, Flashcard & tempset, int step)
{
    size_t found;
#ifdef DEBUG
    cout << "words are: '" << words << "'" << endl;
#endif // DEBUG
    
    while ( words.find(",") != string::npos || \
            words.find("|") != string::npos)
    {
        if (words.rfind("|") != string::npos)
            found = words.rfind("|");
        else
            found = words.rfind(",");

        string tempWord = words.substr(found+1);
#ifdef DEBUG
        cout << "New word: " << tempWord << endl;
#endif // DEBUG
        switch (step)
        {
            case 1:
#ifdef DEBUG
                cout << "case : " << step << endl;
#endif // DEBUG
                tempset.sideA.push_back(tempWord);
                break;
            case 2:
#ifdef DEBUG
                cout << "case : " << step << endl;
#endif // DEBUG
                tempset.sideB.push_back(tempWord);
                break;
            default:
                break; // What should we do for this case?
        }
        words.erase(found);
    }
#ifdef DEBUG
    cout << "New word: " << words << endl;
#endif // DEBUG
    
    switch (step)   // Otherwise catch non-comma case
    {
        case 1:
#ifdef DEBUG
            cout << "case : " << step << endl;
#endif // DEBUG
            tempset.sideA.push_back(words);
            break;
        case 2:
#ifdef DEBUG
            cout << "case : " << step << endl;
#endif // DEBUG
            tempset.sideB.push_back(words);
            break;
        default:
            break;  // What should we do for this case?
    }
}

// EOF
