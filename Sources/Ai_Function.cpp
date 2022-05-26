//
// Created by Phan Minh Phong on 5/18/2022.
//

#include "../Header/Ai_Function.h"
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

vector<string> readWordListFromFile(string filePath)
{
    vector<string> wordList;
    string word;
    fstream wordFile(filePath);
    if (wordFile.is_open()) {
        while (wordFile >> word) {
            wordList.push_back(word);
        }
        wordFile.close();
        return wordList;
    } else {
        throw domain_error("Error: Unable to open vocabulary file " + filePath);
    }
}

bool isAllDash(const string& s)     // kiểm tra xem tất cả có phải dấu "_"
{
    for (char c : s)
        if (c != '-') return false;
    return true;
}

bool isAllNotDash(const string& s)
{
    for (char c : s)
        if (c == '-') return false;
    return true;
}
int getUserWordLength()
{
    int wordLength;
    cout << endl << "Enter your word length: ";
    cin >> wordLength;
    return wordLength;
}

void initialize(int& wordLength, string& secretWord,
                int& incorrectGuess, set<char>& previousGuesses,        //Khoi tao ham
                bool& stop)
{
    wordLength = getUserWordLength();
    secretWord = string(wordLength, '-');
    incorrectGuess = 0;
    previousGuesses = set<char>();
    stop = false;
}

string getUserAnswer(char guess)
{
    string answer;
    cout << endl << "I guess " << guess << ", please enter your mask: ";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer;
}

bool isGoodMask(char guess, const string& mask, const string& secretWord)   // Kiểm tra xem có đúng cách nhập không
{
    if (mask.length() != secretWord.length()) return false;
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-') {
            if (mask[i] != guess)
                return false;
            if (secretWord[i] != '-' && secretWord[i] != mask[i])
                return false;
        }
    return true;
}

void updateSecretWord(const string& mask, string& secretWord)   // thay chữ vào dấu gạch
{
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
            secretWord[i] = mask[i];
}

void update(char guess, const string& mask,
            int& incorrectGuess, set<char>& previousGuesses,
            string& secretWord, bool& stop)
{
    if (!isGoodMask(guess, mask, secretWord))
        throw invalid_argument("mistake entering answer");

    previousGuesses.insert(guess);
    if (isAllDash(mask)) {
        incorrectGuess ++;
        if (incorrectGuess == 7) stop = true;
    } else {
        updateSecretWord(mask, secretWord);
        if (isAllNotDash(secretWord)) stop = true;
    }
}

void render(int incorrectGuess, const set<char>& previousGuesses, // vẽ hình trei cổ
            const string& secretWord)
{
    system("cls");
    cout << endl << "Incorrect guess = " << incorrectGuess
         << "   previous guesses = ";
    for (char c : previousGuesses)
        cout << c;
    cout << "   secretWord = " << secretWord << endl;
    cout << getDrawing(incorrectGuess) << endl;
}

void playAnimation(bool isLosing, const string& word) //vẽ hình win lose
{
    system("cls");
    while (true) {
        if (isLosing){
            cout << endl << "I lost :(. My best word is: " << word << endl;
        this_thread::sleep_for(chrono::milliseconds(500));}
        else{
            cout << endl << "Haha, I win :D. The word is: " << word << endl;}
        cout << (isLosing ? getNextHangMan() : getNextDancingMan());
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
    }
}
set<char> getRemainingChars(const set<char>& previousGuesses) // lọc các chữ còn lại
{
    set<char> remainingChars;
    for (char c = 'a'; c <= 'z'; c++)
        remainingChars.insert(c);
    for (char c: previousGuesses)
        remainingChars.erase(c);
    return remainingChars;
}

char selectRandomChar(const set<char>& s) {           //chọn 1 chữ ngẫu nhiên
    int r = rand() % s.size();
    set<char>::iterator it = s.begin();
    for (; r != 0; r--) it++;
    return *it;
}

char getVowelGuess(const set<char>& remainingChars)         // Đoán các chữ nguyên âm
{
    char vowel[] = {'u', 'a', 'o', 'i', 'e'};
    for (char c : vowel) {
        if (remainingChars.find(c) != remainingChars.end())
            return c;
    }
    return 0;
}

bool isSuitableWord(const string& word, const string& secretWord, const set<char>& remainingChars)  //kiểm tra trong wordlist co tu phu hop
{
    if (word.length() != secretWord.length()) return false;
    for (unsigned int i = 0; i < word.length(); i++) {
        if (secretWord[i] != '-') {
            if (tolower(word[i]) != tolower(secretWord[i])) return false;
        }
        else if (remainingChars.find(word[i]) == remainingChars.end())
            return false;
    }
    return true;
}

vector<string> getSuitableWords(const vector<string>& wordList,          //lọc các chữ hợp vào mảng
                                const string& secretWord,
                                const set<char>& remainingChars)
{
    vector<string> result;
    for (const string& word : wordList)
        if (isSuitableWord(word, secretWord, remainingChars))
            result.push_back(word);
    return result;
}

map<char, int> getOccurenceCount(const set<char>& remainingChars, const vector<string>& wordList) // chọn chữ cái có số lần lặp cao nhất
{
    map<char, int> count;
    for (char c: remainingChars) count[c] = 0;

    for (const string& word : wordList) {
        for (char c : word)
            if (count.find(c) != count.end())
                count[c]++;
    }
    return count;
}

char getMaxOccurenceChar(const set<char>& remainingChars, const map<char, int>& count)      //lay ra chu suot hien nhieu nhat
{
    char best = 0;
    int best_count = 0;
    for (auto p : count)
        if (p.second > best_count) {
            best = p.first;
            best_count = p.second;
        }
    return best;
}

char getNextGuess(const set<char>& previousGuesses, const string& secretWord,vector<string> wordList)
{
    set<char> remainingChars = getRemainingChars(previousGuesses);
    if (remainingChars.size() == 0)
        return 0;

    if (isAllDash(secretWord))
        return getVowelGuess(remainingChars);

    vector<string> filteredWordList = getSuitableWords(wordList, secretWord, remainingChars);
    map<char, int> occurenceCount = getOccurenceCount(remainingChars, filteredWordList);
    return getMaxOccurenceChar(remainingChars, occurenceCount);
}
