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
    double strength(bool, double);
    void updateScore(int, bool, double, int, wordData *);
private:
    double reweight(int, double, double);
};
#endif // _WORDDATA_H_