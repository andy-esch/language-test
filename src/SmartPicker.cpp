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

<<<<<<< HEAD
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





=======

unsigned int SmartPicker::nextIndex(vector<Flashcard> cards)
{
  if(currentIndex==cards.size()-1)
    return 0;
  return currentIndex++
}


unsigned int SmartPicker::leastPickedIndex(vector<Flashcard> cards)
{
  vector<int> asked;
  srand(time(0));
  for(int i=0;i<card.size();i++)
    {
      asked.push_back(cards[i].numAsked);
    }
  std::sort(asked.begin(), asked.end());
  int leastPicked = asked[0];
  int count=0;
  while(asked[count]<=leastPicked){
    count++;
  }
  int indexChoice = rand()%count;
  if(indexChoice==currentIndex)
    return nextIndex();
  setCurrentIndex(indexChoice);
  return indexChoice;  
}


>>>>>>> upstream/master
void SmartPicker::setCurrentIndex(int index)
{
  currentIndex=index;
}
