#include<iostream>

using namespace std;
#ifndef HANGMANPROVIP_HINTFUNCTIONS_H
#define HANGMANPROVIP_HINTFUNCTIONS_H

char getCloseword(char &guess, const string &word,string &guessedWord);

char getClue(string guessedWord, const string &word);

string full_word(const string &word, string &guessfull, string &gussedWord, bool &win);

void hint_use_check(bool &hint1, bool &hint2, bool &hint3, bool &hint4, char &guess, int &Play_Option, string word,
                    string mean, string &guessedWord, string &guessfull, bool &win);

#endif
