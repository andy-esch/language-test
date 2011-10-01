input(cards,&inFile[0]);
numEntries = cards.size();

    if (debug) 
    {
        cout << "Summary of inputted contents: " << endl;
        for (int ii = 0; ii < numEntries; ii++)
            cards[ii].summarizeContents(ii);
        cout << endl;
    }


