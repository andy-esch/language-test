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
  showLetters=false;
  for(int i=0;i<key.size();i++)
    hint[i]=" ";
}


string Hint::letters()
{
  stringstream hint;
  hint << "-> ";
  if(hintNum >= key.size())
    {
      hint << key << " <-" << endl;
      return hint.str();
    }
  
  int i=0;  
  while(i<=hintNum)
    {
      if (key[i] == ' ')
	{
	  hint << " ";
	  i++;
	}
      hint << key[i];
      i++;
    }
  hintNum++;
  return hint.str();
}


string Hint::fillLetterPlaces()
{
  stringstream hint;
  int i=0;
  showLetters=true;
  while (i<hintNum)
    {
      hint << key[i];
      i++;
    }
  
  while (i<key.size())
    {      
      if (key[i] == ' ')
	hint << ' ';
      else
	hint << '-';
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


string Hint::handle(char hintType, bool verbose)
{
  stringstream hint;
  switch (hintType)
    {
    case 'l':
      hint << letters();
      break;
    case 'a':
      hint << answer();
      break;
    case 'n':
      hint << fillLetterPlaces();
      break;
    case 'h':
      hint << help();
      break;
    }
  return hint.str();
}

