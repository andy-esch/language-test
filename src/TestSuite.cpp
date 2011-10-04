input(cards,&inFile[0]);
numEntries = cards.size();

    if (debug) 
    {
        cout << "Summary of inputted contents: " << endl;
        for (int ii = 0; ii < numEntries; ii++)
            cards[ii].summarizeContents(ii);
        cout << endl;
    }


    int jsideB = randIndex(cards[i].sideB.size());	// sideB index
    int jsideA = randIndex(cards[i].sideA.size());	// sideA index
if (debug)
  {
    cout << "second indices (jsideA, jsideB) = (" << jsideA << ", " << jsideB << ")" << endl;
    cout << "(sideAsize, sideBsize) = (" << sideAsize << ", " << sideBsize << ")" << endl;
    cout << "cin is " << (cin.good()?"":"not so ") << "good (cin = '" << cin.good() << "')" << endl;
    cout << "New word: " << endl;
    
  }


