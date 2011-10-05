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
  if(currentIndex==cards.size())
    {
      currentIndex=0;
      return currentIndex;
    }
  else return currentIndex++;
}


unsigned int SmartPicker::leastPickedIndex(vector<Flashcard> cards)
{
  srand ( time(0) );
  vector<int> leastAskedIndices;
  int currentLowest=cards[0].data.numAsked;
  for(int i=0;i<cards.size();i++)
    {
      if(cards[i].data.numAsked<currentLowest)
	currentLowest=i;
    }
  for(int i=0;i<cards.size();i++)
    {
      if(cards[i].data.numAsked==currentLowest)
	leastAskedIndices.push_currentLowest=i;
    }
  
  std::sort(asked.begin(), asked.end());
  int leastPicked = asked[0];
  int count=0;
  while(count < cards.size() && asked[count]<=leastPicked){
    count++;
  }
  int indexChoice = rand() % count;
  if(indexChoice==currentIndex)
    return nextIndex(cards);
  setCurrentIndex(indexChoice);
  return indexChoice;  
}


void SmartPicker::setCurrentIndex(int index)
{
  currentIndex=index;
}
