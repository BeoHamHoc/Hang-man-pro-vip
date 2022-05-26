#include<iostream>
#include <chrono>
#include <thread>
#include "Header/Draw.h"
#include "Header/Main Rule.h"
#include "Header/HintFunctions.h"
#include "Header/Ai_Function.h"

using namespace std;
const int MAX_BAD_GUESSES = 7;

int main() {
    char *DATA_FILE;
    char *MEANING_FILE;
    int choose;
    string z;
    fflush(stdin);
    int Play_Option = 1;
    do {

        do {
            cout << endl
                 << "===== Menu =====" << endl
                 << "1. Campaign" << endl
                 << "2. Play by Topic" << endl
                 << "3. Find Words in Vietnamese Meaning" << endl
                 << "4. Time limit " << endl
                 << "5. AI Play" << endl
                 << "6.Two plays" << endl
                 << "0. Exit" << endl
                 << "Your choice: ";
            cin >> choose;
            switch (choose) {
                case 0: {
                    return 0;
                    break;
                }
                case 1: {
                    Play_Option = 1;
                    cout << "===== Level =====" << endl
                         << "Easy: 1-9" << endl
                         << "Medium : 10-19" << endl
                         << "Hard : >=20" << endl
                         << "Back: 0" << endl
                         << "Enter the lever you want to start:  ";

                    int level = 1;
                    double FinalPoin = 0;
                    cin >> level;
                    if (level == 0) {
                        Play_Option = 0;
                        system("cls");
                        break;
                    }
                    string s;
                    fflush(stdin);
                    int Play_Option_remind = Play_Option;

                    do {
                        Play_Option = Play_Option_remind;
                        fflush(stdin);
                        if (level < 10) {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\easyWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\easyMeaning.txt";
                        } else if (level < 20 && level >= 10) {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\mediumWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\mediumMeaning.txt";
                        } else if (level >= 20) {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\hardWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\hardMeaning.txt";
                        }
                        srand(time(0));
                        string word, mean;
                        fflush(stdin);
                        chooseWord(DATA_FILE, MEANING_FILE, word, mean);
                        if (word.length() < 1) {
                            cout << "Error reading vocabulary file " << DATA_FILE;
                            return -1;
                        }
                        bool hint1 = false;
                        bool hint2 = false;
                        bool hint3 = false;
                        bool hint4 = false;
                        bool win = false; //full word(right:+50% wrong:-40% final result)
                        string guessedWord = string(word.length(), '-');
                        string badGuesses = "";
                        string doneWord = "";
                        int lenbadguesse;
                        time_t start, limit;
                        time(&start);
                        double timelimit;
                        double timeused = 0;
                        do {
                            int k = 1;
                            char guess;
                            string guessfull;
                            renderGame(guessedWord, badGuesses, hint1, hint2, hint3, hint4, Play_Option,
                                       timelimit, timeused, level);
                            guess = readAGuess();
                            hint_use_check(hint1, hint2, hint3, hint4, guess, Play_Option, word, mean, guessedWord,
                                           guessfull, win);
                            if (contains(word, guess)) {
                                if (contains(doneWord, guess)) {
                                    cout << "You already chose this word" << endl;;
                                    this_thread::sleep_for(chrono::milliseconds(500));
                                    timelimit += 1.2;
                                }
                                doneWord += guess;
                                updateGuessedWord(guessedWord, word, guess);

                            } else {
                                if (contains(doneWord, guess)) {
                                    cout << "You already chose this word" << endl;;
                                    this_thread::sleep_for(chrono::milliseconds(500));
                                    timelimit += 1;
                                } else {
                                    badGuesses += guess;
                                    doneWord += guess;
                                }
                            }
                            lenbadguesse = badGuesses.length();

                            time(&limit);
                            timeused = difftime(limit, start);
                            if (timelimit < timeused && Play_Option == 4) {
                                cout << "Time Out! You loss.";
                                lenbadguesse += 7;
                            }


                        } while (lenbadguesse < MAX_BAD_GUESSES && word != guessedWord);
                        time_t end;
                        time(&end);
                        double seconds = difftime(end, start);
                        cout << "You have spent " << seconds << " seconds to complete the turn." << endl;
                        if (word == guessedWord) {
                            double Point = point(hint1, hint2, hint3, hint4, seconds, win);
                            cout << " Your point: " << Point;
                            FinalPoin += Point;
                        }
                        this_thread::sleep_for(chrono::milliseconds(3000));
                        displayFinalResult(word == guessedWord, word);
                        if (word == guessedWord)
                            cout << "Do you want to continue: y/n " << endl
                                 << "Press 0 to back to menu" << endl
                                 << "Your Choice: ";
                        else {
                            cout << "Your final result: " << FinalPoin << endl
                                 << "Back to menu in 5 seconds.";
                            this_thread::sleep_for(chrono::milliseconds(5000));

                            Play_Option = 0;
                            break;
                        }
                        string k;
                        level++;
                        while (k[0] != 'n' && k[0] != 'y' && k[0] != '0')
                            cin >> k;
                        s[0] = k[0];
                    } while (s[0] == 'y');
                    if (s[0] = '0')
                        Play_Option = 0;
                    system("cls");
                    break;
                }
                case 2: {
                    Play_Option = 2;
                    cout << "===== Topic =====" << endl
                         << "1.Fruit" << endl
                         << "2.Jobs" << endl
                         << "3.Subject" << endl
                         << "4.Animals" << endl
                         << "5.Back" << endl
                         << "Your choice: ";
                    int Topic;
                    cin >> Topic;
                    switch (Topic) {
                        case 1: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\fruits.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\fruitsMeaning.txt";
                            break;
                        }
                        case 2: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\jobs.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\jobsMeaning.txt";
                            break;
                        }
                        case 3: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\Subjects.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\SubjectMeaning.txt";
                            break;
                        }
                        case 4: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\Animals.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\AnimalMeaning.txt";
                            break;
                        }
                        case 6: {
                            Play_Option = 0;
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    Play_Option = 3;
                    cout << "===== Level =====" << endl
                         << "1.Easy" << endl
                         << "2.Medium" << endl
                         << "3.Hard" << endl
                         << "4.Back" << endl
                         << "Your choice: ";
                    int Level;
                    cin >> Level;
                    fflush(stdin);
                    switch (Level) {
                        case 1: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\easyWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\easyMeaning.txt";
                            break;
                        }
                        case 2: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\mediumWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\mediumMeaning.txt";
                            break;
                        }
                        case 3: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\hardWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\hardMeaning.txt";
                            break;
                        }
                        case 4: {
                            Play_Option = 0;
                            break;
                        }
                    }
                    break;
                }
                case 4: {
                    Play_Option = 4;
                    cout << "===== Level =====" << endl
                         << "1.Easy" << endl
                         << "2.Medium" << endl
                         << "3.Hard" << endl
                         << "4.Back" << endl
                         << "Your choice: ";
                    int Level;
                    cin >> Level;
                    fflush(stdin);
                    switch (Level) {
                        case 1: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\easyWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\easyMeaning.txt";
                            break;
                        }
                        case 2: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\mediumWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\mediumMeaning.txt";
                            break;
                        }
                        case 3: {
                            DATA_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\hardWordList.txt";
                            MEANING_FILE = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\hardMeaning.txt";
                            break;
                        }
                        case 4: {
                            Play_Option = 0;
                            break;
                        }
                    }
                    break;
                }
                case 5: {
                    do {

                        int wordLength;
                        string secretWord;
                        int incorrectGuess;
                        set<char> previousGuesses;
                        bool stop;
                        bool teachAi = false;
                        initialize(wordLength, secretWord, incorrectGuess, previousGuesses, stop);

                        render(incorrectGuess, previousGuesses, secretWord);
                        do {
                            string filePath = "C:\\Users\\Admin\\OneDrive - vnu.edu.vn\\Desktop\\HangManProVip\\Data\\All word list.txt";
                            vector<string> wordList = readWordListFromFile(filePath);
                            char guess = getNextGuess(previousGuesses, secretWord, wordList);
                            if (guess == 0) {
                                cout << "I give up,I don't know this word, please teach me." << endl;
                                this_thread::sleep_for(chrono::milliseconds(1000));
                                AIstudy();
                                cout << "Thank you!" << endl
                                     << "Reset game to update your word to my dictionary." << endl;
                                this_thread::sleep_for(chrono::milliseconds(1000));
                                stop = true;
                                teachAi = true;
                            } else {
                                do {
                                    try {
                                        string mask = getUserAnswer(guess);
                                        update(guess, mask, incorrectGuess, previousGuesses, secretWord, stop);
                                        break;
                                    } catch (invalid_argument) {
                                        cout << "Invalid mask, try again" << endl;
                                    }
                                } while (true);
                                render(incorrectGuess, previousGuesses, secretWord);
                            }
                        } while (!stop);
                        if (!teachAi)
                            displayFinalResult(incorrectGuess != MAX_BAD_GUESSES, secretWord);
                        cout << "Do you want to play again: y/n " << endl
                             << "Press 0 to back to menu" << endl
                             << "Your Choice: ";
                        string k;
                        while (k[0] != 'n' && k[0] != 'y' && k[0] != '0')
                            cin >> k;
                        z[0] = k[0];
                        if (k[0] == '0') { Play_Option = 0; }
                    } while (z[0] == 'y' || z[0] == 'Y');
                    break;
                }
                case 6: {
                    do {
                        Play_Option = 6;
                        cout << "Enter number of match: " << endl << endl;
                        int match,  playturn = 1;
                        cin >> match;

                        int Play_Option_remind = Play_Option;
                        int Player_1_point=0,Player_2_point=0;

                        do {
                            if (playturn % 2 == 0)
                                cout << "===Match " << playturn / 2 << "===" << endl
                                     << "Play 1 choose word,Player 2 guess" << endl;
                            else
                                cout << "===Match " << playturn / 2 + 1 << "===" << endl
                                     << "Play 2 choose word,Player 1 guess" << endl;
                            Play_Option = Play_Option_remind;
                            fflush(stdin);
                            string word, mean;
                            fflush(stdin);
                            cout << "Enter the word: ";
                            getline(cin, word);
                            cout << "Enter meaning of word: ";
                            getline(cin, mean);
                            bool hint1 = false;
                            bool hint2 = false;
                            bool hint3 = false;
                            bool hint4 = false;
                            bool win = false; //full word(right:+50% wrong:-40% final result)
                            string guessedWord = string(word.length(), '-');
                            string badGuesses = "";
                            string doneWord = "";
                            int lenbadguesse;
                            time_t start, limit;
                            time(&start);
                            double timelimit;
                            if (Play_Option == 4) {
                                cout << "Enter the seconds:";
                                cin >> timelimit;
                            }
                            double timeused = 0;
                            do {
                                int level = 0;
                                int k = 1;
                                char guess;
                                string guessfull;

                                renderGame(guessedWord, badGuesses, hint1, hint2, hint3, hint4, Play_Option, timelimit,
                                           timeused,
                                           level);

                                if (Play_Option == 3) cout << "Vietnamese Meaning : " << mean << endl;
                                guess = readAGuess();
                                //Hint;
                                hint_use_check(hint1, hint2, hint3, hint4, guess, Play_Option, word, mean, guessedWord,
                                               guessfull, win);
                                if (contains(word, guess)) {
                                    if (contains(doneWord, guess)) {
                                        cout << "You already chose this word" << endl;;
                                        this_thread::sleep_for(chrono::milliseconds(500));
                                        timelimit += 1.2;
                                    }
                                    doneWord += guess;
                                    updateGuessedWord(guessedWord, word, guess);

                                } else {
                                    if (contains(doneWord, guess)) {
                                        cout << "You already chose this word" << endl;;
                                        this_thread::sleep_for(chrono::milliseconds(500));
                                        timelimit += 1;
                                    } else {
                                        badGuesses += guess;
                                        doneWord += guess;
                                    }
                                }
                                lenbadguesse = badGuesses.length();

                                time(&limit);
                                timeused = difftime(limit, start);
                                if (timelimit < timeused && Play_Option == 4) {
                                    cout << "Time Out! You loss.";
                                    lenbadguesse += 7;
                                }


                            } while (lenbadguesse < MAX_BAD_GUESSES && word != guessedWord);
                            time_t end;
                            time(&end);
                            double seconds = difftime(end, start);
                            cout << "You have spent " << seconds << " seconds to complete the turn." << endl;
                            if (word == guessedWord) {
                                double Point = point(hint1, hint2, hint3, hint4, seconds, win);
                                cout << " Your point: " << Point;
                                if (playturn % 2 == 0)
                                    Player_2_point+=Point;
                                else
                                    Player_1_point+=Point;

                            }
                            this_thread::sleep_for(chrono::milliseconds(3000));
                            displayFinalResult(word == guessedWord, word);
                            system("cls");
                            playturn++;


                        } while (2 * match >= playturn);
                        if(Player_1_point<Player_2_point)
                        {
                            cout << "==== Player 2 win! ====" << endl;

                        }
                        if(Player_1_point>Player_2_point)
                        {
                            cout << "====Player 1 win! ====";
                            this_thread::sleep_for(chrono::seconds(5));
                        }
                        if(Player_1_point==Player_2_point)
                        {
                            cout << "==== Draw! ====";
                            this_thread::sleep_for(chrono::seconds(5));
                        }
                        cout << "Player 1 : " << Player_1_point << endl
                             << "Player 2 : " << Player_2_point << endl;
                             this_thread::sleep_for(chrono::seconds(5));

                        cout << "Do you want to play again: y/n " << endl
                             << "Press 0 to back to menu" << endl
                             << "Your Choice: ";
                        string k;
                        while (k[0] != 'n' && k[0] != 'y' && k[0] != '0')
                            cin >> k;
                        z[0] = k[0];
                        if (k[0] == '0') { Play_Option = 0; }
                    } while (z[0] == 'y' || z[0] == 'Y');
                    break;
                }
                default: {
                    cout << "Input is false" << endl;
                    Play_Option = 0;
                }

            }
        } while (Play_Option == 0);   // tạo menu

        // play chung cho mode 2 3 4
        string s;
        fflush(stdin);
        int Play_Option_remind = Play_Option;

        do {
            Play_Option = Play_Option_remind;
            fflush(stdin);
            srand(time(0));
            string word, mean;
            fflush(stdin);
            chooseWord(DATA_FILE, MEANING_FILE, word, mean);
            if (word.length() < 1) {
                cout << "Error reading vocabulary file " << DATA_FILE;
                return -1;
            }
            bool hint1 = false;
            bool hint2 = false;
            bool hint3 = false;
            bool hint4 = false;
            bool win = false; //full word(right:+50% wrong:-40% final result)
            string guessedWord = string(word.length(), '-');
            string badGuesses = "";
            string doneWord = "";
            int lenbadguesse;
            time_t start, limit;
            time(&start);
            double timelimit;
            if (Play_Option == 4) {
                cout << "Enter the seconds:";
                cin >> timelimit;
            }
            double timeused = 0;
            do {
                int level = 0;
                int k = 1;
                char guess;
                string guessfull;

                renderGame(guessedWord, badGuesses, hint1, hint2, hint3, hint4, Play_Option, timelimit, timeused,
                           level);

                if (Play_Option == 3) cout << "Vietnamese Meaning : " << mean << endl;
                //if (Play_Option != 4)
                guess = readAGuess();
                //else
                //  guess = readAGuesslimit(timelimit);


                //Hint;
                hint_use_check(hint1, hint2, hint3, hint4, guess, Play_Option, word, mean, guessedWord,
                               guessfull, win);
                if (contains(word, guess)) {
                    if (contains(doneWord, guess)) {
                        cout << "You already chose this word" << endl;;
                        this_thread::sleep_for(chrono::milliseconds(500));
                        timelimit += 1.2;
                    }
                    doneWord += guess;
                    updateGuessedWord(guessedWord, word, guess);

                } else {
                    if (contains(doneWord, guess)) {
                        cout << "You already chose this word" << endl;;
                        this_thread::sleep_for(chrono::milliseconds(500));
                        timelimit += 1;
                    } else {
                        badGuesses += guess;
                        doneWord += guess;
                    }
                }
                lenbadguesse = badGuesses.length();

                time(&limit);
                timeused = difftime(limit, start);
                if (timelimit < timeused && Play_Option == 4) {
                    cout << "Time Out! You loss.";
                    lenbadguesse += 7;
                }


            } while (lenbadguesse < MAX_BAD_GUESSES && word != guessedWord);
            time_t end;
            time(&end);
            double seconds = difftime(end, start);
            cout << "You have spent " << seconds << " seconds to complete the turn." << endl;
            if (word == guessedWord) {
                double Point = point(hint1, hint2, hint3, hint4, seconds, win);
                cout << " Your point: " << Point;
            }
            this_thread::sleep_for(chrono::milliseconds(3000));
            displayFinalResult(word == guessedWord, word);
            cout << "Do you want to play again: y/n " << endl
                 << "Press 0 to back to menu" << endl
                 << "Your Choice: ";
            string k;
            while (k[0] != 'n' && k[0] != 'y' && k[0] != '0')
                cin >> k;
            s[0] = k[0];
        } while (s[0] == 'y');
        if (s[0] = '0')
            Play_Option = 0;
        system("cls");
    } while (Play_Option == 0);
    return 0;
}