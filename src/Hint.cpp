/*
 *  Hint.cpp
 *  
 *  Description:
 *
 *
 *  Created by KEPS on 2/10/11.
 *
 */

#include "functions.h"
#include "Hint.h"


void Hint::init(string answerKey, bool selectVerbose)
{
  key=answerKey;
  hintNum=0;
  verbose=selectVerbose;
}



char Hint::nextLetter()
{
  char letter;
  if(hintNum<key.size()){
    letter=key[hintNum];
    hintNum++;
    return letter;
  }
  else return NULL;
}


string Hint::fillLetterPlaces()
{
  stringstream hint;
  int i=0;

  while (i<hintNum)
    {
      hint << key[i];
      i++;
    }
  
  while (i<key.size())
    {      
      if (key[i] != ' ')
	hint << '-';
      else
	hint << ' ';
      i++;
    }

  hint << endl;
  return hint.str();
}



string Hint::answer()
{
  return key;
}


void Hint::disableHints()
{
}


string Hint::example()
{
  string hint = "an example of usage";
  return hint;
}

// This belongs elsewhere
// string Hint::skipWord()
// {
// }

// if synonym hint is selected, create new Hint object with new key
// and perform answer() on it.
// string Hint::synonym()
// {
//   string hint;
//   return hint;
// }


string Hint::help()
{
  stringstream hint;
  hint << '\a' << endl;
  hint << "Want a letter?  Type '-l'." << endl;
  hint << "Want more than one letter? Type '-l#', where # = a number 1 - 9." << endl;
  hint << "Want the answer?  Type '-a'." << endl;
  hint << "Want the number of letters?  Type '-n'." << endl;
  hint << "Want to skip this word?  Type '-s'." << endl;
  hint << "Want help?  Type '-h'." << endl;
  hint << "Want out of here?  Type CTRL-D (End of file -- EOF)." << endl;
  hint << "Want to turn these messages off?  Type '-d' to disable." << endl;
  return hint.str();
}

string Hint::handle(char hintType, bool verbose)
{
  // if (hintNum >= key.size())
  //   hint << " <-";
  return "handle";


}
