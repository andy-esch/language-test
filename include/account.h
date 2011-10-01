/*
 *  account.h
 *  
 *  Description:
 *
 *
 *  Created by Peter Eschbacher on 9/29/11.
 *
 */

#include <string>

class summary {
    string dictionary;
    float score;
    string datePassed;
    int numOfTimesAttempted;
public:
    void output(string, float, string, int);
    void accountExporter(string);
    void accountLoader();
    
};