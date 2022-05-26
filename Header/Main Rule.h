//
// Created by Phan Minh Phong on 5/3/2022.
//
#include <iostream>

using namespace std;
#ifndef HANGMANPROVIP_MAIN_RULE_H
#define HANGMANPROVIP_MAIN_RULE_H
string getLowerCaseString(const string& s);
void chooseWord(char *fileName,char *MeaningName,string &cword, string &cmean);
char readAGuess();
bool contains(const string& word, char c);
void updateGuessedWord(string& guessedWord, const string& word, char guess);
double point(bool &hint1,bool &hint2, bool &hint3,bool &hint4,double seconds,bool win);
//char readAGuesslimit(int timeRestrict);
#endif //HANGMANPROVIP_MAIN_RULE_H
