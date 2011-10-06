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

SmartPicker::SmartPicker()
{
  currentIndex=0;
}



unsigned int SmartPicker::nextIndex(vector<Flashcard> cards)
{
  return (currentIndex++ % cards.size());
}



unsigned int SmartPicker::leastPickedIndex(vector<Flashcard> cards)
{
  srand ( time(0) );
  vector<int> leastAskedIndices;
  int currentLowest=cards[0].data.numAsked;
  int numasked;

  for(int i=1;i<cards.size();i++)
    {
      numasked=cards[i].data.numAsked;
      if(numasked<currentLowest)
	currentLowest=numasked;
    }

  for(int i=0;i<cards.size();i++)
    {
      if(cards[i].data.numAsked==currentLowest)
	leastAskedIndices.push_back(i);
    }

  int indexChoice = leastAskedIndices[rand() % leastAskedIndices.size()];
  
  if(indexChoice==currentIndex)
    setCurrentIndex((indexChoice+1) % leastAskedIndices.size());
  else  setCurrentIndex(indexChoice);
  return currentIndex;  
}

void SmartPicker::setCurrentIndex(int index)
{
  currentIndex=index;
}
