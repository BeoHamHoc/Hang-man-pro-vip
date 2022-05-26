//
// Created by Phan Minh Phong on 5/18/2022.
//

#ifndef HANGMANPROVIP_AI_FUNCTION_H
#define HANGMANPROVIP_AI_FUNCTION_H

#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <set>
#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <thread>
#include <chrono>
#include "C:\Users\Admin\OneDrive - vnu.edu.vn\Desktop\HangManProVip\Header\Draw.h"
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

vector<std::string> readWordListFromFile(string filePath);
bool isAllDash(const std::string& s);
bool isAllNotDash(const std::string& s);
int getUserWordLength();

string getUserAnswer(char guess);

void initialize(int &wordLength, string &secretWord,
                int &incorrectGuess, set<char> &previousGuesses,
                bool &stop) ;
bool isGoodMask(char guess, const string& mask, const string& secretWord);
void updateSecretWord(const string& mask, string& secretWord);
void update(char guess, const string& mask,
            int& incorrectGuess, set<char>& previousGuesses,
            string& secretWord, bool& stop);
void render(int incorrectGuess, const set<char>& previousGuesses,
            const string& secretWord);
void playAnimation(bool isLosing, const string& word);
set<char> getRemainingChars(const set<char>& previousGuesses);
char selectRandomChar(const set<char>& s);
char getVowelGuess(const set<char>& remainingChars);
bool isSuitableWord(const string& word, const string& secretWord, const set<char>& remainingChars);
vector<string> getSuitableWords(const vector<string>& wordList,
                                const string& secretWord,
                                const set<char>& remainingChars);
map<char, int> getOccurenceCount(const set<char>& remainingChars, const vector<string>& wordList);
char getMaxOccurenceChar(const set<char>& remainingChars, const map<char, int>& count);
char getNextGuess(const set<char>& previousGuesses, const string& secretWord,vector<string> wordList);
void AIstudy();

#endif //HANGMANPROVIP_AI_FUNCTION_H
