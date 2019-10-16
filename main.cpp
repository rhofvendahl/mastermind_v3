/**
cs-11 Sampler Project
mastermind.cpp
Purpose : plays a custom game of Mastermind.

@author Russell Hofvendahl
@version 2.0 12/8/15
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <climits>
using namespace std;

#include "mastermind.h"
#include "mastermind_records.h"

const int MIN_LENGTH = 2;
const int MAX_LENGTH = 36;

/**
Reads and returns length of code with error protection.

@return code length for ensuing game.
*/
int codeLength() {
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

/**
Reads and returns number of possible characters with error protection.

@return number of possible characters.
*/
int posChars() {
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

/**
Generates code.

@param length the length of code to be generated.
@param chars the number of possible characters for each place.
@return a code of desired specifications.
*/
string genCode(int length, int chars) {
    const string CHARS = "0123456789abcdefghijklmnopqrstuvwxyz";
    string code = "";
    for (int i = 0; i < length; i++) {
        code += CHARS[rand() % chars];
    }
    return code;
}

/**
Reads and returns guess with error protection.

@param rounds round number.
@param length proper length of guess.
@param chars proper number of characters in guess.
@return player's guess.
*/
string readGuess(int rounds, int length, int chars, bool& cheatCode, bool& end) {
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

/**
Evaluates guess, prints number of characters correct and misplaced, returns
true if guess matches code.

@param code code generated for game.
@param guess player's guess as to code.
@return 1 if guess matches code.
*/
bool guessEval(string code, string guess) {
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

/**
Plays a game of Mastermind and saves a Record to the records vector.

@param records The object vector.
*/
void play(vector<Record>& records) {
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
        << s << "!\nPlease enter your name for the records:";
        string name;
        cin >> ws;
        getline(cin, name);

        Record temp(length, chars, rounds, name);
        records.push_back(temp);
    }
    cout << endl;
}


int main() {
    srand(time(0));
    vector<Record> records;
    loadRecords(records);

    cout << "Welcome to Mastermind v3!\n\n";

    int choice;

    const int EXIT = 0;
    const int INSTRUCT = 1;
    const int PLAY = 2;
    const int DISPLAY_ALL = 3;
    const int DISPLAY_SELECT = 4;
    do {
        cout << "Please choose from the following menu:\n"
        << "0. Exit\n"
        << "1. Instructions\n"
        << "2. Play\n"
        << "3. Display all records\n"
        << "4. Display selective records\n"
        << "Choice (0-4): ";
        cin >> choice;
        while (!cin || (choice > DISPLAY_SELECT)) {
            cout << "Please enter a number between 0 and 4: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> choice;
        }
        cout << endl;
        switch (choice) {
            case INSTRUCT: {
                cout << "The game of mastermind is played between a code maker\n"
                << "and a code breaker. In this program the code will be\n"
                << "generated automatically and you will play the part of\n"
                << "codebreaker. For each round you must enter a guess as\n"
                << "to the code and will be returned the number of correct\n"
                << "characters as well as the  number of characters included\n"
                << "but misplaced. A single guessed character will not match\n"
                << "multiple code characters nor will multiple guessed\n"
                << "characters match a single code character. Try to guess\n"
                << "the code in as few rounds as possible.\n\n"
                << "Good luck!\n\n";
                break;
            }
            case PLAY: {
                play(records);
                break;
            }
            case DISPLAY_ALL:{
                display(records);
                break;
            }
            case DISPLAY_SELECT: {
                cout << "Please select code length to screen for:";
                int length;
                cin >> length;
                cout << "Please select possible characters to screen for:";
                int chars;
                cin >> chars;
                cout << endl;
                display(length, chars, records);
                break;
            }
        }
    } while (choice != EXIT);

    cout << "Would you like to save records from this session to a permanent"
    << " file? (y/n): ";
    char save;
    cin >> save;
    while (save != 'y' && save != 'n') {
        cout << "Please enter either a \"y\" or an \"n\".\nWould you like to save"
        << " the records from this session to\na permanent file? (y/n): ";
        cin >> save;
    }
    if (save == 'y') saveRecords(records);

    cout << "\nThank you for playing Mastermind!\n";
    return 0;
}
