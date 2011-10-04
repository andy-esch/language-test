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
  Hint(string,bool);
  Hint();
  string handle(char,bool);
  void setKey(string);
private:
  string key;
  int hintNum;
  bool verbose;
  string hint;
  void addLetter();
  void fillLetterPlaces();
  void answer();
  void disableHints();
  string example();
  string synonym();
  string help();
};
#endif
//could add an int penalty so that each hint results in penalty points.
