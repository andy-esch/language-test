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

Flashcard::Flashcard()
          :sideA(0), sideB(0), data(), weight(0.0)
{
}

void Flashcard::toScreen()
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


void Flashcard::recordPerformance(usInt numOfTries, bool isWrong, double responseTime)
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

void Flashcard::input(vector<Flashcard> & ws, string inFile)
{
    string temp1, temp2;
    size_t delimPos = string::npos;
    ifstream inputFile(inFile.c_str(),ifstream::in);   // open file if possible
    Flashcard tempSet;
    usInt lineNum = 1, delimWidth = 1;
    string delimiters[] = {"\t","    ","   ","  "};

    while ( !inputFile.is_open() ) // Get rid of this since listDicts guarantees files?
    {
        cout << "File '" << inFile << "' does not exist as specified.\n"
             << "Enter another filename (or 'exit' to exit): ";
        cin >> inFile;
        
        if (ltest::exitProg(inFile.c_str(),cin.eof()))
        {
            cout << endl;
            exit(0);
        }
        else
            inputFile.open(inFile.c_str(),ifstream::in);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    
    cout << "Inputting vocabulary from '" << inFile << "'" << endl;
    while ( !inputFile.eof() )
    {
        getline(inputFile, temp1);
/* TODO: Perhaps use
 *  getline(inputFile,temp1,'\t'); \\ gets to tab
 *  getline(inputFile,temp2,); \\ gets after tab
 *  and do some error checking (what if no delimiter? Skip line)
 */  

        if (temp1.empty()) continue;          // Skip empty lines
        else if (temp1.find('#') != string::npos)
        {
            cout << "Skipping the following line (comment): \n"
                 << '\t' << temp1;
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
            cerr << "Caught: '" << e.what() << "' on line " << lineNum << '\n'
                 << "Type: " << typeid(e).name() << '\n'
                 << "Not inputting '" << temp1 << "'" << endl;
            continue;
        }
        catch ( std::exception &e )
        {
            cerr << "Caught: " << e.what() << '\n'
                 << "Type: " << typeid(e).name() << endl;
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
    
    inputFile.close();
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
