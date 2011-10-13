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

// Default constructor
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

/**    Adaptive members    **/

// Default Constructor
Adaptive::Adaptive(int numEntries)
{
    probability.assign(numEntries,inverse(numEntries));
}

Adaptive::~Adaptive(void)
{
    probability.clear();
}

double Adaptive::weight(bool wrong, double diff)
{   // weight for answering (non-hints)
    double weight = 0.0;

    if (wrong)
        weight = 0.24 * (1 - exp(-0.2 * diff));
    else // if correct
        weight = -0.24 * exp(-0.2 * diff);

    return weight;
}

void Adaptive::updateProbs(int index, double weight)
{
    double pStar = probability[index];
    double alpha = fdim(1.0,pStar), beta = pStar;
    vector<double>::iterator it, itIndex = (probability.begin() + index);

    for (it = probability.begin(); it != probability.end(); it++)
    {
        if ( it == itIndex )
            *it *= fma(weight,alpha,1.0);
        else
            *it *= fma(-weight,beta,1.0);
    }
}

unsigned int Adaptive::adaptiveIndex(const vector<Flashcard> & cards, \
                                     unsigned int index, bool isWrong, float ansTime)
{
    // ansTime is a float and weight is a double -- does the precision difference matter?
    updateProbs(index, weight(isWrong,ansTime));

    static unsigned int lastIndex = UINT_MAX;
    unsigned int currentIndex;
    extern boost::mt19937 gen;

    do
    {
        vector<double> cumulative;
        std::partial_sum(probability.begin(), probability.end(), \
                         std::back_inserter(cumulative));
        boost::uniform_real<> dist(0.0, cumulative.back());
        boost::variate_generator<boost::mt19937&, boost::uniform_real<> > prob(gen, dist);
        currentIndex = std::lower_bound(cumulative.begin(), \
                                     cumulative.end(), \
                                     prob()) - cumulative.begin();
    } while (currentIndex == lastIndex);

    lastIndex = currentIndex;

    return currentIndex;
}
