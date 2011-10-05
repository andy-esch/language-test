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




void Flashcard::toScreen()
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


void Flashcard::clearWS()
{
    sideB.clear();
    sideA.clear();
}


void Flashcard::recordPerformance(int numOfTries, double responseTime)
{
  data.numAsked++;
  if(numOfTries==1)
    {
      data.numCorrect++;
      data.answeringTime+=responseTime;
    }
}


void Flashcard::setWeight(int N)
{
  weight=1.0/static_cast<double>(N);
}
