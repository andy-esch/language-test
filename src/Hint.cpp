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


Hint::Hint(string answerKey, bool selectVerbose)
{
  key=answerKey;
  hintNum=0;
  verbose=selectVerbose;
  showLetters=false;
  for(int i=0;i<key.size();i++)
    {
      hint+= " ";
    }
}


void Hint::addLetter()
{
  if(hintNum<=key.size())
    {
      hint.replace(hintNum,1,string(1,key[hintNum]));
      hintNum++;
    }
}


void Hint::fillLetterPlaces()
{
  for(int i=hintNum;i<key.size();i++)
    {
      if(key[i]==' ')
	hint.replace(i,1," ");
      hint.replace(i,1,"-");
    }
}


void Hint::answer()
{
  hint = key;
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
  hint << whitespace(10) << '\a' << endl;
  hint << whitespace(10) << "Want a letter?  Type '-l'." << endl;
  hint << whitespace(10) << "Want more than one letter? Type '-l#', where # = a number 1 - 9." << endl;
  hint << whitespace(10) << "Want the answer?  Type '-a'." << endl;
  hint << whitespace(10) << "Want the number of letters?  Type '-n'." << endl;
  hint << whitespace(10) << "Want to skip this word?  Type '-s'." << endl;
  hint << whitespace(10) << "Want help?  Type '-h'." << endl;
  hint << whitespace(10) << "Want out of here?  Type CTRL-D (End of file -- EOF)." << endl;
  hint << whitespace(10) << "Want to turn these messages off?  Type '-d' to disable." << endl;
  return hint.str();
}


string Hint::buildHint(char hintType, bool verbose)
{
  switch (hintType)
    {
    case 'l':
      addLetter();
      break;
    case 'a':
      answer();
      break;
    case 'n':
      fillLetterPlaces();
      break;
    }
  return hint;//.str();
}

