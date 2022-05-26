//
// Created by Phan Minh Phong on 5/3/2022.
//
#ifndef HANGMANPROVIP_DRAW_H
#define HANGMANPROVIP_DRAW_H

#include <iostream>

using namespace std;

void displayFinalResult(bool won, const string &word);

void renderGame(const string &guessedWord, const string &badGuesses, bool hint1, bool hint2, bool hint3, bool hint4,
                int Play_Option, double &timelimit, double timeused, int level);

const string &getNextDancingMan();

const string &getNextHangMan();

string getDrawing(int incorrectGuess);

#endif //HANGMANPROVIP_DRAW_H