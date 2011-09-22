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

int main()
{
    Flashcard fl1;
    std::cout << "Hi!" << std::endl;
    
    return 0;
}

string Flashcard::printLangOneWord(int i, int j)
{
    return langOneWord[i];
}

string Flashcard::printLangTwoWord(int i, int j)
{
    return langTwoWord[i];
}

/*
void Flashcard::summarizeContents(int index1)
{
    cout << "verbs: " << endl;
    for (int jj = 0; jj < verbs.size(); jj++)
        cout << "spen[" << index1 << "].verbs[" << jj << "] = '" << verbs[jj] << "'" << endl;
    cout << endl;
    cout << "verbos: " << endl;
    for (int kk = 0; kk < verbos.size(); kk++)
        cout << "spen[" << index1 << "].verbos[" << kk << "] = '" << verbos[kk] << "'" << endl;
    cout << endl;
}

void Flashcard::clearWS(void)
{
    langOneWord.clear();
    langTwoWord.clear();
}

string Flashcard::outputOne(int i)
{
    return langOneWord[i];
}

string Flashcard::outputTwo(int i)
{
    return langOneWord[i];
}
*/