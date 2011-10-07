/*
 *  SmartPicker.cpp
 *  
 *  Description:
 *
 *
 *  Created by KEPS on 4/10/11.
 *
 */

#include "SmartPicker.h"

void SmartPicker::setCurrentIndex(int index)
{
    currentIndex = index;
}

SmartPicker::SmartPicker()
{
  currentIndex=0;
}

int SmartPicker::nextIndex(int cardsSize)
{
    currentIndex++;
    return (currentIndex % cardsSize);
}

unsigned int SmartPicker::leastPickedIndex(vector<Flashcard> cards)
{
    srand ( time(0) );
    vector<Flashcard>::iterator it;    
    vector<int> leastAskedIndices;
    int currentLowest=cards[0].data.numAsked;
    int numasked;

    for (it = cards.begin(); it != cards.end(); it++)
    {
        numasked = it->data.numAsked;
        if (numasked < currentLowest)
            currentLowest=numasked;
    }

    for (int ii=0;ii<cards.size();ii++)
        if (it->data.numAsked == currentLowest)
            leastAskedIndices.push_back(ii);

    int indexChoice = leastAskedIndices[rand() % leastAskedIndices.size()];
  
    if (indexChoice == currentIndex)
        setCurrentIndex((indexChoice+1) % leastAskedIndices.size());
    else
        setCurrentIndex(indexChoice);

    return currentIndex;  
}

