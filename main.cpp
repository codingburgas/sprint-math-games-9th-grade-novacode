#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

void PrintMessage(string message, bool printTop = true, bool printBottom = true) {
    if (printTop) {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else {
        cout << "|";
    }

    bool front = true;
    while (message.length() < 33) {
        if (front) message = " " + message;
        else message = message + " ";
        front = !front;
    }

    cout << message << "|" << endl;

    if (printBottom)
        cout << "+---------------------------------+" << endl;
}

void DrawHangman(int wrong) {
    string head = (wrong >= 6) ? " " : "O";
    string armLeft = (wrong >= 4) ? " " : "/";
    string armRight = (wrong >= 5) ? " " : "\\";
    string body = (wrong >= 3) ? " " : "|";
    string legLeft = (wrong >= 1) ? " " : "/";
    string legRight = (wrong >= 2) ? " " : "\\";
    string rope = "|";
    string poleTop = "|";
    string poleDown = "|";
    string base = "+----+";

    PrintMessage("HANGMAN");
    PrintMessage(poleTop);
    PrintMessage(rope);
    PrintMessage(head);
    PrintMessage(armLeft + body + armRight);
    PrintMessage(body);
    PrintMessage(legLeft + string(" ") + legRight);
    PrintMessage(poleDown);
    PrintMessage(base);
}

void PrintLetters(string taken, char from, char to) {
    string s;
    for (char c = from; c <= to; c++) {
        if (taken.find(c) == string::npos)
            s += c, s += " ";
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}

void PrintAvailableLetters(string taken) {
    PrintMessage("Available letters");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
    PrintMessage("", false, true);
}

bool PrintWordAndCheckWin(string word, string guessed) {
    bool won = true;
    string s;

    for (char c : word) {
        if (guessed.find(c) == string::npos) {
            won = false;
            s += "_ ";
        }
        else {
            s += c;
            s += " ";
        }
    }

    PrintMessage(s, false);
    return won;
}

string LoadRandomWord() {
    vector<string> words = {
        "APPLE", "BANANA", "COMPUTER", "DOG", "HANGMAN",
        "PUZZLE", "SCHOOL", "WATER", "HOUSE", "PROGRAM",
        "ELEPHANT", "GUITAR", "PIZZA", "ORANGE", "WINDOW"
    };

    return words[rand() % words.size()];
}

int CountWrong(string word, string guessed) {
    int wrong = 0;
    for (char g : guessed)
        if (word.find(g) == string::npos)
            wrong++;
    return wrong;
}

int main() {
    srand(time(NULL));

    string word = LoadRandomWord();
    string guessed = "";

    int wrong = 0;
    bool win = false;

    while (wrong < 6) {

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        DrawHangman(wrong);
        PrintAvailableLetters(guessed);
        PrintMessage("Guess the word");
        win = PrintWordAndCheckWin(word, guessed);

        if (win) break;

        cout << "> ";
        char x;
        cin >> x;
        x = toupper(x);

        if (guessed.find(x) == string::npos)
            guessed += x;

        wrong = CountWrong(word, guessed);
    }

    if (win)
        PrintMessage("YOU WON!");
    else {
        PrintMessage("GAME OVER");
        PrintMessage("You Lost!");
        PrintMessage("Word was: " + word);
    }

    return 0;
}
