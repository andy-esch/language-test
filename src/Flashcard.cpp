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




string Flashcard::toScreen(void)
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


void Flashcard::clearWS(void)
{
    sideB.clear();
    sideA.clear();
}