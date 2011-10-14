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

void Flashcard::toScreen(void)
{
    cout << "sideA: " << endl;
    for (int jj = 0; jj < sideA.size()-1; jj++)
      {
	cout << sideA[jj] << ", ";
      }
    cout << sideA[sideA.size()-1] << endl;
    cout << "sideB: " << endl;
    for (int kk = 0; kk < sideB.size()-1; kk++)
      {
	cout << sideB[kk] << ", ";
      }
    cout << sideB[sideB.size()-1] << endl;
}


void Flashcard::recordPerformance(int numOfTries, bool isWrong, double responseTime)
{
    data.numAsked++;
    if (numOfTries==1 && !isWrong)
    {
      data.numCorrect++;
      data.answeringTime+=responseTime;
    }
}

vector<string> Flashcard::getSideA(void)
{
    return sideA;
}

string Flashcard::getSideA(int i)
{
    return sideA[i];
}

vector<string> Flashcard::getSideB(void)
{
    return sideB;
}

string Flashcard::getSideB(int i)
{
    return sideB[i];
}

int Flashcard::size(char x)
{
    if (x == 'A')
        return sideA.size();
    else
        return sideB.size();
}

int Flashcard::size(char x, int ind)
{
    if (x == 'A')
        return sideA[ind].size();
    else
        return sideB[ind].size();
}

void Flashcard::setWeight(int N)
{
    weight = inverse(N);
}


void Flashcard::clearWS(void)
{
    sideB.clear();
    sideA.clear();
}

void Flashcard::input(vector<Flashcard> & ws, char * inFile)
{
    // Do some error-checking to make sure there are the proper number of
    //   columns, proper encoding(? not binary), etc.
    string temp1, temp2;
    size_t delimPos = string::npos;
    ifstream infile(inFile,ifstream::in);   // open file if possible
    Flashcard tempset;
    unsigned short int lineNum = 1, delimWidth = 1;
    string delimiters[] = {"\t","    ","   ","  "};
    
    while ( !infile.is_open() )
    {
        cout << "File '" << inFile << "' does not exist as specified." << endl;
        cout << "Enter another filename (or 'exit' to exit): ";
        cin >> inFile;
        
        if (exitProg(inFile,cin.eof()))
        {
            cout << endl;
            exit(0);
        }
        else
            infile.open(inFile,ifstream::in);
        cin.clear();
        cin.ignore(10,'\n');
    }
    
    cout << "Inputting vocabulary from '" << inFile << "'" << endl;
    while ( !infile.eof() )
    {
        getline(infile, temp1);             // Read in line from file
        
        if (temp1 == "") continue;          // Skip empty lines
        
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
        
        try // This my be redundant with previous if statement
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
        insertWords(temp1, tempset, 1);
        insertWords(temp2, tempset, 2);
        
            // Put tempset into Flashcard vector
        ws.push_back(tempset);
        
            // Clear variables for next time through
        tempset.clearWS();
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
    if (debug) cout << "words are: '" << words << "'" << endl;
    
    while ( words.find(",") != string::npos )   // while comma is found
    {
        found = words.rfind(",");
        string tempWord = words.substr(found+1);
        if (debug) cout << "New word: " << tempWord << endl;
        switch (step)
        {
            case 1:
                if (debug) cout << "case : " << step << endl;
                tempset.sideA.push_back(tempWord);
                break;
            case 2:
                if (debug) cout << "case : " << step << endl;
                tempset.sideB.push_back(tempWord);
                break;
            default:
                break; // What should we do for this case?
        }
        words.erase(found);
    }
    
    if (debug) cout << "New word: " << words << endl;
    
    switch (step)   // Otherwise catch non-comma case
    {
        case 1:
            if (debug) cout << "case : " << step << endl;
            tempset.sideA.push_back(words);
            break;
        case 2:
            if (debug) cout << "case : " << step << endl;
            tempset.sideB.push_back(words);
            break;
        default:
            break;  // What should we do for this case?
    }
}
