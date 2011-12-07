/*
 *  SmartPicker.cpp
 *
 *  Description: Algorithms for flashcard selection.
 *      Adaptive: probability of card selection based on past performance
 *      through use of boost random library.  Algorithm inspired by
 *      http://www.boost.org/doc/libs/1_47_0/doc/html/boost_random/tutorial.html
 *
 *  Created by KEPS on 4/10/11.
 *
 */

#include "SmartPicker.h"

/**    SmartPicker members    **/

// Default constructor
SmartPicker::SmartPicker(void)
            :currentIndex(0)
{
}

void SmartPicker::setCurrentIndex(int index)
{
    currentIndex = index;
}


usInt SmartPicker::getCurrentIndex(void)
{
    return currentIndex;
}

usInt SmartPicker::getNextIndex(int cardsSize)
{
    setCurrentIndex((++currentIndex) % cardsSize);
    return currentIndex;
}

/**    LeastCorrect members    **/
LeastCorrect::LeastCorrect(void)
             :leastCorrectIndices(0), currLowest(0)
{
}

usInt LeastCorrect::getNextIndex(const vector<Flashcard> & cards)
{
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

    if (leastCorrectIndices.empty() )
        repopulateIndices(cards);

    std::list<usInt>::iterator it = leastCorrectIndices.begin();
    for (int jj = ltest::randIndex(leastCorrectIndices.size()); jj > 0; jj--)
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

void LeastCorrect::printIndices(void)
{
    std::list<usInt>::iterator it = leastCorrectIndices.begin();
    cout << *it;
    for (it++; it != leastCorrectIndices.end(); it++ )
        cout << ", " << *it;
    cout << endl;
}

// Is there a way to generalize this to use numCorrect and numAsked for the same
// function?
usInt LeastCorrect::findSmallest(const vector<Flashcard> & deck)
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

    std::list<usInt>::iterator it = leastPickedIndices.begin();
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

void LeastPicked::printIndices(void)
{
    list<usInt>::iterator it = leastPickedIndices.begin();
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
         :probability(0), gen(static_cast<usInt> (std::time(0))), levDistance(0.0)
{
    probability.assign(numEntries,ltest::inverse(numEntries));
//    gen.seed(static_cast<usInt>(std::time(0))); // initialize random seed
}

// Desctructor
Adaptive::~Adaptive(void)
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

void Adaptive::updateProbsAdvanced(int index, bool isWrong, double ansTime, \
                                   const vector<Flashcard> & cards)
{   // Updates probabilities
    double wgt = weight(isWrong,ansTime);
    double probUnasked = 0.0;
    double pStar = probability[index];
    int numOfNumAskedIs0 = 0;
    double alpha = fdim(1.0,pStar), beta;
    double gamma = 0.01, gamWeight = 1.0;   // Experiment with different gammas
//    vector<double>::iterator it, itIndex = (probability.begin() + index);

    for (usInt ii = 0; ii < probability.size(); ii++)
    {
        if (cards[ii].data.getNumAsked() == 0 && ii != index)
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
        if ( ii == index )
            probability[ii] *= fma(wgt,alpha,1.0);
        else if ( cards[ii].data.getNumAsked() != 0 )
            probability[ii] *= fma(-wgt,beta,1.0);
        else
            probability[ii] *= fma(gamWeight,gamma,1.0);
    }
}

void Adaptive::updateProbsBasic(int index, bool isWrong, double ansTime)
{
    const double wgt = weight(isWrong,ansTime);
    const double pStar = probability[index];
    const double alpha = fdim(1.0,pStar), beta = pStar;
    vector<double>::iterator it;
    const vector<double>::iterator itIndex = (probability.begin() + index);

    for (it = probability.begin(); it != probability.end(); it++)
    {
        if ( it == itIndex )
            *it *= fma(wgt,alpha,1.0);
        else
            *it *= fma(-wgt,beta,1.0);
    }
}

usInt Adaptive::adaptiveIndex(const vector<Flashcard> & cards) ///uhm is this func arg needed?
{
    // ansTime is a float and weight is a double -- does the precision difference matter?
//    updateProbs(index, weight(isWrong,ansTime));

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
