#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <climits>
using namespace std;

#include "mastermind.h"

int Mastermind::codeLength() {
    int length;
    do {
        cout << "Enter desired code length (2-36): ";
        cin >> length;
        if (cin.fail()) {
            cout << "Please enter digits only.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            length = 0;
        } else if (length < MIN_LENGTH || length > MAX_LENGTH) {
            cout << "Please enter a number between 2 and 36.\n";
        }
    } while (length < MIN_LENGTH || length > MAX_LENGTH);
    return length;
}

int Mastermind::posChars() {
    int chars;
    do {
        cout << "Enter desired number of possible characters (2-36): ";
        cin >> chars;
        if (cin.fail()) {
            cout << "Please enter digits only.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            chars = 0;
        } else if (chars < MIN_LENGTH || chars > MAX_LENGTH) {
            cout << "Please enter a number between 2 and 36.\n";
        }
    } while (chars < MIN_LENGTH || chars > MAX_LENGTH);
    return chars;
}

string Mastermind::genCode(int length, int chars) {
    const string CHARS = "0123456789abcdefghijklmnopqrstuvwxyz";
    string code = "";
    for (int i = 0; i < length; i++) {
        code += CHARS[rand() % chars];
    }
    return code;
}

string Mastermind::readGuess(int rounds, int length, int chars, bool& cheatCode, bool& end) {
    string guess;
    bool bad;
    const int ELEVEN = 11;
    do {
        cout << "Guess " << rounds << ": ";
        cin >> guess;
        bad = 0;
        if (guess == "RH") cheatCode = 1;
        else if (guess == "END") end = 1;
        else if (guess.length() != (unsigned) length) {
            cout << "Please enter " << length << " characters.\n";
            bad = 1;
        } else {
            for (int i = 0; i < length; i++) {
                if (chars < ELEVEN) {
                    if (guess[i] < '0' || guess[i] > ('0' - 1 + chars)) {
                        cout << "Please use only (0-" << chars - 1 << ").\n";
                        bad = 1;
                        i = length;
                    }
                } else {
                    if ((guess[i] < '0') || ((guess[i] > '9') && (guess[i] < 'a'))
                    || guess[i] > ('a' -11 + chars)) {
                        cout << "Please use only (0-9) and (a";
                        if (chars > ELEVEN) {
                            cout << "-" << (char) ('a' + chars - ELEVEN);
                        }
                        cout << ").\n";
                        bad = 1;
                        i = length;
                    }
                }
            }
        }
    } while (bad);
    return guess;
}

bool Mastermind::guessEval(string code, string guess) {
    int length = code.length();
    int correct = 0;
    for (int codeChar = 0; codeChar < length; codeChar++) {
        if (code[codeChar] == guess[codeChar]) {
            correct++;
            code.replace(codeChar, 1, "C");
            guess.replace(codeChar, 1, "G");
        }
    }
    int misplaced= 0;
    for (int codeChar = 0; codeChar < length; codeChar++) {
        for (int guessChar = 0; guessChar < length; guessChar++) {
            if (code[codeChar] == guess[guessChar]) {
                misplaced++;
                code.replace(codeChar, 1, "C");
                guess.replace(guessChar, 1, "G");
                guessChar = length;
            }
        }
    }
    cout << correct << " correct, " << misplaced << " misplaced.\n";
    return (correct == length);
}

void Mastermind::play(vector<Record>& records) {
    int length = codeLength();
    int chars = posChars();
    string code = genCode(length, chars);

    cout << "\nTo end the game enter \"END\"\n";
    int rounds  = 0;
    bool match = 0;
    bool cheatCode = 0;
    bool end = 0;
    do {
        rounds++;
        string guess = readGuess(rounds, length, chars, cheatCode, end);
        match = guessEval(code, guess);
    } while (!match && !cheatCode && !end);

    if (match || cheatCode) {
        string s = "";
        if (rounds > 1)
        s = "s";
        cout << "\nCongratulations, you broke the code in " << rounds << " round"
        << s << "!\nPlease enter your name for the records: ";
        string name;
        cin >> ws;
        getline(cin, name);

        Record temp(length, chars, rounds, name);
        records.push_back(temp);
    }
}
