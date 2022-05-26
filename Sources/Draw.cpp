//
// Created by Phan Minh Phong on 5/3/2022.
//
#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>

using namespace std;

void Printhint(bool hint1, bool hint2, bool hint3, bool hint4, int Play_option) {
    if (!hint1 && Play_option != 3)
        cout << "Enter number 1 if you want its Vietnamese meaning (-10% point) " << endl;
    if (!hint2)
        cout << "Enter number 2 if you want training wheels (1 word only)(-15% point) " << endl;
    if (!hint3)
        cout << "Enter number 3 if you want one letter off(-20% point) " << endl;
    if (!hint4)
        cout << "Enter number 4 if you want to guess full word. (+50% final point/-40% final point)" << endl;
    if (hint1 && hint2 && hint3)
        cout << "You've run out of hint" << endl;
}

const string &getNextDancingMan() {
    const static string figure[] = {
            "     O     \n"
            "    /|\\   \n"
            "    | |    \n",
            "     O     \n"
            "    /|\\   \n"
            "    / \\   \n",
            "   __O__   \n"
            "     |     \n"
            "    / \\   \n",
            "    \\O/   \n"
            "     |     \n"
            "    / \\   \n",
            "   __O__   \n"
            "     |     \n"
            "    / \\   \n",
            "     O     \n"
            "    /|\\   \n"
            "    / \\   \n",
            "    O      \n"
            "    /|\\   \n"
            "    / \\   \n",
            "     O     \n"
            "    /|\\   \n"
            "    / \\   \n",
            "      O    \n"
            "    /|\\   \n"
            "    / \\   \n",
            "     O     \n"
            "    /|\\   \n"
            "    / \\   \n",


    };
    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

const string &getNextHangMan() {
    const static string figure[] = {
            "   ------------+    \n"
            "   |    /           \n"
            "   |    O      \n"
            "   |   /|\\    \n"
            "   |   / \\    \n"
            "   |        \n"
            " -----      \n",
            "   ------------+     \n"
            "   |     |           \n"
            "   |     O           \n"
            "   |    /|\\         \n"
            "   |    / \\         \n"
            "   |        \n"
            " -----      \n",
            "   ------------+     \n"
            "   |      \\         \n"
            "   |      O          \n"
            "   |     /|\\        \n"
            "   |     / \\        \n"
            "   |      \n"
            " -----    \n",
            "   ------------+     \n"
            "   |     |           \n"
            "   |     O           \n"
            "   |    /|\\         \n"
            "   |    / \\         \n"
            "   |        \n"
            " -----      \n"
    };
    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

void displayFinalResult(bool won, const string &word) {
    for (int i = 0; i < 7; i++) {
        system("cls");
        if (won)
            cout << "Congratulations! You win!" << endl;
        else
            cout << "You lost. The correct word is " << word << endl;
        cout << (won ? getNextDancingMan() : getNextHangMan());
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

string getDrawing(int incorrectGuess) {
    static const string figure[] = {
            "   -------------    \n"
            "   |                \n"
            "   |                \n"
            "   |                \n"
            "   |                \n"
            "   |     \n"
            " -----   \n",
            "   -------------    \n"
            "   |           |    \n"
            "   |                \n"
            "   |                \n"
            "   |                \n"
            "   |     \n"
            " -----   \n",
            "   -------------    \n"
            "   |           |    \n"
            "   |           O    \n"
            "   |                \n"
            "   |                \n"
            "   |     \n"
            " -----   \n",
            "   -------------    \n"
            "   |           |    \n"
            "   |           O    \n"
            "   |           |    \n"
            "   |                \n"
            "   |     \n"
            " -----   \n",
            "   -------------    \n"
            "   |           |    \n"
            "   |           O    \n"
            "   |          /|    \n"
            "   |                \n"
            "   |     \n"
            " -----   \n",
            "   -------------    \n"
            "   |           |    \n"
            "   |           O    \n"
            "   |          /|\\  \n"
            "   |                \n"
            "   |     \n"
            " -----   \n",
            "   -------------    \n"
            "   |           |    \n"
            "   |           O    \n"
            "   |          /|\\  \n"
            "   |          /     \n"
            "   |     \n"
            " -----   \n",
            "   -------------    \n"
            "   |           |    \n"
            "   |           O    \n"
            "   |          /|\\  \n"
            "   |          / \\  \n"
            "   |     \n"
            " -----   \n",
    };

    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    return figure[incorrectGuess % NUMBER_OF_FIGURES];
}

void renderGame(const string &guessedWord, const string &badGuesses, bool hint1, bool hint2, bool hint3, bool hint4,
                int Play_Option, double &timelimit, double timeused, int level) {
    //system("cls");;
    system("cls");
    int badGuessCount = badGuesses.length();
    if (level != 0)
        cout << "===== Level " << level << " =====" << endl;
    Printhint(hint1, hint2, hint3, hint4, Play_Option);
    cout << getDrawing(badGuessCount) << endl;
    cout << "Secret word: " << guessedWord << endl;
    if ((timelimit > timeused && Play_Option == 4))
        cout << "You have " << timelimit - timeused << "  seconds left from last guess." << endl;
    if (badGuessCount > 0) {
        cout << "You've made " << badGuessCount << " wrong ";
        cout << (badGuessCount == 1 ? "guess" : "guesses");
        cout << ": " << badGuesses << endl;

    }
}