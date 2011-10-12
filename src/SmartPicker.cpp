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
    /*  Create array of probabilities of size equal to size of quiz entries
     *  Vector or new array[]?
     *  and need desctructor to kill it once quiz exits?
     */
}

Adaptive::Adaptive(int numEntries)
{
    probability.assign(numEntries,inverse(numEntries));
}

void Adaptive::print(void)
{
    cout << "hi" << std::endl;
}

unsigned int Adaptive::adaptiveIndex(wordData * data, int numEntries)
{
    static int lastIndex;
    int currIndex;
    extern boost::mt19937 gen;
    double * prob[numEntries];

     // Copy probabilities to simple array so partial_sum() can use it.
     // It's possible that this step isn't necessary but I cannot figure out
     // a way to use consecutive pointers in the partial_sum() function for
     // the structure data[ii].probability
     // Use an iterator instead?  such as wordData.probability::iterator?
    for (int ii = 0; ii < numEntries; ii++)
        prob[ii] = &(data[ii].probability);

    do
    {
        vector<double> cumulative;
        std::partial_sum(prob[0], prob[0] + numEntries, \
                         std::back_inserter(cumulative));
        if (debug) cout << "partial_sum() calculated" << endl;
        boost::uniform_real<> dist(0.0, cumulative.back());
        boost::variate_generator<boost::mt19937&, boost::uniform_real<> > prob(gen, dist);
        currIndex = std::lower_bound(cumulative.begin(), cumulative.end(), prob()) - cumulative.begin();
    } while (currIndex == lastIndex);

    lastIndex = currIndex;

    return currIndex;
}
