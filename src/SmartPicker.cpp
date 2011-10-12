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

/**    SmartPicker members    **/
void SmartPicker::setCurrentIndex(int index)
{
    currentIndex = index;
}

SmartPicker::SmartPicker(void)
{
    currentIndex = 0;
}

unsigned int SmartPicker::nextIndex(int cardsSize)
{
    return (currentIndex++ % cardsSize); // What's the order of operations here?
                                         // Should currentIndex be increment before the mod is taken?
}

/**    LeastCorrect members    **/
unsigned int LeastCorrect::leastCorrectIndex(const vector<Flashcard> & cards)
{
    srand(time(0));
    vector<int> leastCorrectIndices;
    unsigned int currentLowest = findSmallest(cards);

    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].data.numCorrect == currentLowest)
            leastCorrectIndices.push_back(i);
    }
    
    int indexChoice = leastCorrectIndices[rand() % leastCorrectIndices.size()];

    if (indexChoice == currentIndex)
        setCurrentIndex((indexChoice+1) % leastCorrectIndices.size());
    else
        setCurrentIndex(indexChoice);

    return currentIndex;  
}

/**    LeastPicked members    **/
unsigned int LeastPicked::leastPickedIndex(const vector<Flashcard> & cards)
{
    srand(time(0));
    vector<Flashcard>::iterator it;    
    vector<unsigned int> leastAskedIndices;
    unsigned int currentLowest = findSmallest(cards);

    for (int ii = 0; ii < cards.size(); ii++)
        if ( it->data.numAsked == currentLowest )
            leastAskedIndices.push_back(ii);

    int indexChoice = leastAskedIndices[rand() % leastAskedIndices.size()];
  
    if (indexChoice == currentIndex)
        setCurrentIndex((indexChoice+1) % leastAskedIndices.size());
    else
        setCurrentIndex(indexChoice);

    return currentIndex;  
}

/**    WeightedIndex members    **/

// Default Constructor
WeightedIndex::WeightedIndex(void)
{
    /* not sure what to put here yet */
}

void WeightedIndex::print(void)
{
    cout << "hi" << std::endl;
}
