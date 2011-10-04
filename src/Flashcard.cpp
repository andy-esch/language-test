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

// Flashcard::Flashcard(vector<string> A, vector<string> B)
// {
//   sideA=A;
//   sideB=B;
// }




void Flashcard::summarizeContents(int index1)
{
    cout << "sideA: " << endl;
    for (int jj = 0; jj < sideA.size(); jj++)
        cout << "spen[" << index1 << "].sideA[" << jj << "] = '" << sideA[jj] << "'" << endl;
    cout << endl;
    cout << "sideB: " << endl;
    for (int kk = 0; kk < sideB.size(); kk++)
        cout << "spen[" << index1 << "].sideB[" << kk << "] = '" << sideB[kk] << "'" << endl;
    cout << endl;
}

void Flashcard::clearWS()
{
    sideB.clear();
    sideA.clear();
}
