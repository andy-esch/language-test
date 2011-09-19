/*
 *  wordSet.cpp
 *  
 *  Description:
 *
 *
 *  Created by Añdy Eschbacher on 9/19/11.
 *
 */

#include "wordSet.h"

void wordSet::summarizeContents(int index1)
{
    cout << "verbs: " << endl;
    for (int jj = 0; jj < verbs.size(); jj++)
        cout << "spen[" << index1 << "].verbs[" << jj << "] = '" << verbs[jj] << "'" << endl;
    cout << endl;
    cout << "verbos: " << endl;
    for (int kk = 0; kk < verbos.size(); kk++)
        cout << "spen[" << index1 << "].verbos[" << kk << "] = '" << verbos[kk] << "'" << endl;
    cout << endl;
}

void wordSet::clearWS()
{
    verbos.clear();
    verbs.clear();
}