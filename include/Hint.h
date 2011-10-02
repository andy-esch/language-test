/*
 *  Hint.h
 *  
 *  Description:
 *
 *
 *  Created by KEPS 2/10/11.
 *
 */

#ifndef HINT_H
#define HINT_H
#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;


class Hint {

public:
  string key;
  int hintNum;
  string hint;
  bool verbose;
  bool showLetters;
  //int penalty; //each hint method call can increase this.
  string handle(char,bool);
  Hint(string,bool);
  // private:
  void addLetter();
  void fillLetterPlaces();
  void answer();
  void disableHints();
  string example();
  string synonym();
  string help();
};
#endif
