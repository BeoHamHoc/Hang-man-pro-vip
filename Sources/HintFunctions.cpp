#include<iostream>
#include <cmath>
#include "C:\Users\Admin\OneDrive - vnu.edu.vn\Desktop\HangManProVip\Header\Main Rule.h"

using namespace std;

void getCloseword(char &guess, const string &word,string &guessedWord) {
    cout << "Choose the word you want to guess: ";
    cin >> guess;
    for (int i = 0; i < word.length(); i++) {
        int distance = abs(guess - word[i]);
        if (distance <= 2) {
            guess = word[i];
            updateGuessedWord(guessedWord, word, guess);
        }
    }
}

char getClue(string guessedWord, const string &word) {
    int i = 0;
    while (i <= word.size())
        if (guessedWord[i] != word[i]) return word[i];
        else i++;
}

string full_word(const string &word, string &guessfull, string &guessedWord, bool &win) {
    cout << "Choose the word you want to guess: ";
    cin >> guessfull;
    if (guessfull == word) {
        guessedWord = word;
        win = true;
    }
    return word;
}

void hint_use_check(bool &hint1, bool &hint2, bool &hint3, bool &hint4, char &guess, int &Play_Option, string word,
                   string mean, string &guessedWord, string &guessfull, bool &win) {
    if (guess == '1' && hint1 == false) {
        cout << "Vietnamese Meaning : " << mean << endl;
        guess = readAGuess();
        Play_Option = 3;
        hint1 = true;
    } else if (guess == '1' && hint1 == true) {
        cout << "You already used this function" << endl;
        guess = readAGuess();
    }
    if (guess == '2' && hint2 == false) {
        cout << word << endl;
        getCloseword(guess, word,guessedWord);
        hint2 = true;
    } else if (guess == '2' && hint2 == true) {
        cout << "You already used this function" << endl;
        guess = readAGuess();
    }
    if (guess == '3' && hint3 == false) {
        guess = getClue(guessedWord, word);
        hint3 = true;
    } else if (guess == '3' && hint3 == true) {
        cout << "You already used this function" << endl;
        guess = readAGuess();
    }
    if (guess == '4' && hint4 == false) {
        guessfull = full_word(word, guessfull, guessedWord, win);
        if (!win)
            guess = readAGuess();
        hint4 = true;
    } else if (guess == '4' && hint4 == true) {
        cout << "You already used this function" << endl;
        guess = readAGuess();
    }
}