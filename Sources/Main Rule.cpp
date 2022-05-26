#include<iostream>
#include<iomanip>
#include <thread>
#include <conio.h>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;
string getLowerCaseString(const string &s) {    // chuyển từ trong file thành chữ thường
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}   //chuyển tất cả chữ sang

void chooseWord(char *fileName,char *MeaningName, string &cword,
                string &cmean) {   // chọn từ từ 1 file và chọn nghĩa từ file
    vector<string> wordList;
    ifstream file(fileName);
    if (file.is_open()) {
        string word;
        while (file >> word) {
            wordList.push_back(word);
        }
        file.close();
    }
    vector<string> MeaningList;
    ifstream mfile(MeaningName);
    if (mfile.is_open()) {
        string Meaning;
        while (getline(mfile, Meaning)) {
            MeaningList.push_back(Meaning);
        }
        mfile.close();
    }
    if (wordList.size() > 0) {
        int randomIndex = rand() % wordList.size();
        cword = getLowerCaseString(wordList[randomIndex]);
        cmean = MeaningList[randomIndex];
    }
}

char readAGuess() {   //nhập chữ vào và chuyển thành chữ viết thường
    char input;
    cout << "Your guess: ";
    cin >> input;
    return tolower(input);
}

bool contains(const string &word, char c) {                        // Kiểm tra xem chữ đó có trong từ đoán hay không
    return (word.find_first_of(c) != string::npos);
}

void updateGuessedWord(string &guessedWord, const string &word, char guess) {  // Thêm chữ vào ô vừa đoán trúng
    for (int i = word.length() - 1; i >= 0; i--) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}

double point(bool &hint1, bool &hint2, bool &hint3,bool &hint4, double seconds,bool win) {
    double point;
    double percent = 1;
    if (hint1) {
        percent -= 0.1;
    }
    if (hint2) {
        percent -= 0.15;
    }
    if (hint3)
        percent -= 0.2;
    if (hint4 && win) {
        percent *= 1.5;
    }
    else if(hint4 && !win)
    {
        percent *=0,6;
    }
    double maxpoint = 1000;
    if (seconds <= 90) {
        point = (maxpoint - 10 * seconds) * percent;
    } else {
        point = (maxpoint - 900) * percent;
    }
    return point;
}

void AIstudy() {
    fstream a, b;
    string newword, newmean;
    cout << "Your word: " << endl;
    fflush(stdin);
    getline(cin, newword);
    cout << "Word meaning: ";
    getline(cin, newmean);
    a.open("C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\All word list.txt", ios::app);
    b.open("C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\All word list meaning.txt",
           ios::app);
    a << endl << newword;
    b << endl << newmean;
    a.close();
    b.close();
}
/*char readAGuesslimit(int timeRestrict)
{
    int countdown = timeRestrict;
    char guess;
    while(countdown-=5){
        cout <<"\rTime remaining: " << setfill('0') << setw(2) << countdown;
        cout <<"\t Enter your guess: ";
        this_thread::sleep_for(5000ms);
        if(kbhit()){
            cout << endl;
            guess = getch();
            //cout<<guess;
            break;
        }
        guess = '0';
    }
    return tolower(guess);
}
*/