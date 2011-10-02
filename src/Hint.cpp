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


void Hint::init(string answerKey, bool selectVerbose);
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
  else return null;
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
      if (key[jj] != ' ')
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
  string hint;
  return hint;
}

string Hint::handle()
{
  if (hintNum >= key.size())
    hint << " <-";



}
