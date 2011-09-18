/*
 *  worddata.h
 *  
 *  Description: class definition of worddata
 *
 *
 *  Created by Peter Eschbacher on 9/11/11.
 *
 */
#ifndef _WORDDATA_H_
#define _WORDDATA_H_

class wordData {
public:
    unsigned int numAsked;
    float percentRight;
    float avgTime;
    double probability;
    unsigned int rank;
    void updateScore(int, bool, double, int, wordData *);
    void updateScore(int, int, wordData *, char, unsigned int=0);
private:
    double reweight(int, double, double);
    double weight(bool, double);
    double weight(char, int, double);
    void updateProbs(int, int, double, wordData *);
};
#endif // _WORDDATA_H_