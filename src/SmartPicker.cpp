/*
 *  SmartPicker.cpp
 *
 *  Description: Algorithms for flashcard selection.
 *      Adaptive: probability of card selection based on past performance
 *      through use of boost random library.
 *
 *  Created by KEPS on 4/10/11.
 *
 */

#include "SmartPicker.h"

/**    SmartPicker members    **/

// Default constructor
SmartPicker::SmartPicker()
            :currentIndex(0)
{
}

void SmartPicker::setCurrentIndex(usInt newValue)
{
    currentIndex = newValue;
}

usInt SmartPicker::getCurrentIndex() const
{
    return currentIndex;
}

usInt WalkThrough::getNextIndex(const vector<Flashcard> & cards)
{
#ifdef DEBUG
    cout << "Index from WalkThrough class" << endl;
#endif // DEBUG
    setCurrentIndex((++currentIndex) % cards.size());
    return currentIndex;
}

/**    LeastCorrect members    **/
LeastCorrect::LeastCorrect()
             :leastCorrectIndices(0), currLowest(0)
{
}

usInt LeastCorrect::getNextIndex(const vector<Flashcard> & cards)
{
#ifdef DEBUG
    cout << "Index from LeastCorrect class" << endl;
#endif // DEBUG
    // generate and set new index
    leastCorrectIndex(cards);

    return currentIndex;
}

void LeastCorrect::leastCorrectIndex(const vector<Flashcard> & cards)
{
    static usInt lastIndex = USHRT_MAX;

    if (lastIndex != USHRT_MAX)
        if (cards[lastIndex].data.getNumCorrect() > currLowest)
            leastCorrectIndices.remove(lastIndex);

    if (leastCorrectIndices.empty())
        repopulateIndices(cards);

    std::list<usInt>::const_iterator it = leastCorrectIndices.begin();
    for (usInt jj = ltest::randIndex(leastCorrectIndices.size()); jj > 0; jj--)
        it++;

    if (*it == currentIndex)
        setCurrentIndex((*it + 1) % leastCorrectIndices.size());
    else
        setCurrentIndex(*it);
    lastIndex = *it;
}

void LeastCorrect::repopulateIndices(const vector<Flashcard> & cards)
{
    currLowest = findSmallest(cards);
    for (usInt i = 0; i < cards.size(); i++)
    {
        if (cards[i].data.getNumCorrect() == currLowest)
            leastCorrectIndices.push_back(i);
    }
}

void LeastCorrect::printIndices()
{
    std::list<usInt>::const_iterator it = leastCorrectIndices.begin();
    cout << *it;
    for (it++; it != leastCorrectIndices.end(); it++ )
        cout << ", " << *it;
    cout << endl;
}

// Is there a way to generalize this to use numCorrect and numAsked for the same
// function?
usInt LeastCorrect::findSmallest(const vector<Flashcard> & deck) const
{
    usInt currentLowest = deck[0].data.getNumCorrect(), temp;
    
    for (usInt ii = 1; ii < deck.size(); ii++)
    {
        temp = deck[ii].data.getNumCorrect();
        if (temp < currentLowest)
            currentLowest = temp;
    }
    
    return currentLowest;
}

/**    LeastPicked members    **/
LeastPicked::LeastPicked()
            :leastPickedIndices(0), currLowest(0)
{
}

usInt LeastPicked::getNextIndex(const vector<Flashcard> & cards)
{
#ifdef DEBUG
    cout << "Index from LeastPicked class" << endl;
#endif // DEBUG
    // generate new index
    leastPickedIndex(cards);

    return currentIndex;
}

void LeastPicked::leastPickedIndex(const vector<Flashcard> & cards)
{
    static usInt lastIndex = USHRT_MAX;

    if (lastIndex != USHRT_MAX)
        if (cards[lastIndex].data.getNumAsked() > currLowest)
            leastPickedIndices.remove(lastIndex);

    if (leastPickedIndices.empty() )
        repopulateIndices(cards);

    list<usInt>::const_iterator it = leastPickedIndices.begin();
    for (int jj = ltest::randIndex(leastPickedIndices.size()); jj > 0; jj--)
        it++;

    if (*it == currentIndex)
        setCurrentIndex((*it + 1) % leastPickedIndices.size());
    else
        setCurrentIndex(*it);

    lastIndex = *it;
}

void LeastPicked::repopulateIndices(const vector<Flashcard> & cards)
{
    currLowest = findSmallest(cards);
    for (usInt i = 0; i < cards.size(); i++)
    {
        if (cards[i].data.getNumAsked() == currLowest)
            leastPickedIndices.push_back(i);
    }
}

void LeastPicked::printIndices()
{
    list<usInt>::const_iterator it = leastPickedIndices.begin();
    cout << *it;
    for (it++; it != leastPickedIndices.end(); it++ )
        cout << ", " << *it;
    cout << endl;
}

// Is there a way to generalize this to use numCorrect and numAsked for the same
// function?
usInt LeastPicked::findSmallest(const vector<Flashcard> & deck)
{
    usInt currentLowest = deck[0].data.getNumAsked(), temp;
    
    for (usInt ii = 1; ii < deck.size(); ii++)
    {
        temp = deck[ii].data.getNumAsked();
        if (temp < currentLowest)
            setCurrentLowest(temp);
    }

    return currentLowest;
}

void LeastPicked::setCurrentLowest(usInt newCurrLow)
{
    currLowest = newCurrLow;
}

/**    Adaptive members    **/

// Default Constructor
Adaptive::Adaptive(int numEntries)
         :probability(0), gen(static_cast<usInt> (std::time(0))), \
          levDistance(0.0), currAnsTime(0.0), isWrong(true)
{
    probability.assign(numEntries,ltest::inverse(numEntries));
}

// Desctructor
Adaptive::~Adaptive()
{
    probability.clear();
}

double Adaptive::weight(bool wrong, double diff)
{   // weight for answering (non-hints)
    double weight = 0.0;

    if (wrong)
        weight = 0.24 * (1.0 - exp(-0.2 * (diff + levDistance)));
    else // if correct
        weight = -0.24 * exp(-0.2 * diff);

    return weight;
}

void Adaptive::updateProbsAdvanced(const double wgt, \
                                   const vector<Flashcard> & cards)
{   // Updates probabilities
    double probUnasked = 0.0;
    const double pStar = probability[currentIndex];
    int numOfNumAskedIs0 = 0;
    double alpha = fdim(1.0,pStar), beta;
    double gamma = 0.01, gamWeight = 1.0;   // Experiment with different gammas

    for (usInt ii = 0; ii < probability.size(); ii++)
    {
        if (cards[ii].data.getNumAsked() == 0 && ii != currentIndex)
        {
            probUnasked += probability[ii];
            numOfNumAskedIs0++;
        }
    }

    // Divide-by-zero guard
    if (numOfNumAskedIs0 < (probability.size() - 2))
    {
        gamma = 0.01;
        beta = (gamma * probUnasked / wgt + pStar * alpha) / (alpha - probUnasked);
        gamWeight = 1.0;
    }
    else
    {
        beta = pStar;
        gamWeight = -wgt;
        gamma = beta;
    }

    for (usInt ii = 0; ii < probability.size(); ii++)
    {
        if ( ii == currentIndex )
            probability[ii] *= fma(wgt,alpha,1.0);
        else if ( cards[ii].data.getNumAsked() != 0 )
            probability[ii] *= fma(-wgt,beta,1.0);
        else
            probability[ii] *= fma(gamWeight,gamma,1.0);
    }
}

void Adaptive::updateProbsBasic(const double wgt)
{
    const double pStar = probability[currentIndex];
    const double alpha = fdim(1.0,pStar), beta = pStar;
    vector<double>::iterator it;
    const vector<double>::const_iterator itIndex = (probability.begin() + currentIndex);

    for (it = probability.begin(); it != probability.end(); it++)
    {
        if ( it == itIndex )
            *it *= fma(wgt,alpha,1.0);
        else
            *it *= fma(-wgt,beta,1.0);
    }
}

usInt Adaptive::getNextIndex(const vector<Flashcard> & cards)
{
#ifdef DEBUG
    cout << "Index from Adaptive class" << endl;
#endif // DEBUG

    Adaptive::updateProbsAdvanced(weight(isWrong,currAnsTime), cards);

    static usInt lastIndex = USHRT_MAX;
    boost::random::discrete_distribution<> dist(probability);

    do
    {
        setCurrentIndex(dist(gen));
    } while (currentIndex == lastIndex);

    lastIndex = currentIndex;

    return currentIndex;
}

string Adaptive::probabilitySummary(vector<Flashcard> & cards)
{
    stringstream ps;
    ps << "Summary:\n";

    for (usInt ii = 0; ii < cards.size(); ii++)
    {
        ps << cards[ii].getWord('B',0) << '\t' << static_cast<int> (100 * probability[ii]) << endl;
    }

    return ps.str();
}

void Adaptive::setLevDistance(string str1, string str2)
{
    unsigned short temp1 = wordCompare::levenshtein(str1,str2);

    levDistance = static_cast<double> (temp1);
}

// EOF
