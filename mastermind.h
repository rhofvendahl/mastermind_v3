#ifndef __MASTERMIND_H__
#define __MASTERMIND_H__

#include <vector>

#include "mastermind_records.h"

class Mastermind {
public:
    /**
    Plays a game of Mastermind and saves a Record to the records vector.

    @param records The object vector.
    */
    void play(vector<Record>& records);

private:
    const int MIN_LENGTH = 2;
    const int MAX_LENGTH = 36;
    
    /**
    Reads and returns length of code with error protection.

    @return code length for ensuing game.
    */
    int codeLength();

    /**
    Reads and returns number of possible characters with error protection.

    @return number of possible characters.
    */
    int posChars();

    /**
    Generates code.

    @param length the length of code to be generated.
    @param chars the number of possible characters for each place.
    @return a code of desired specifications.
    */
    string genCode(int length, int chars);

    /**
    Reads and returns guess with error protection.

    @param rounds round number.
    @param length proper length of guess.
    @param chars proper number of characters in guess.
    @return player's guess.
    */
    string readGuess(int rounds, int length, int chars, bool& cheatCode, bool& end);

    /**
    Evaluates guess, prints number of characters correct and misplaced, returns
    true if guess matches code.

    @param code code generated for game.
    @param guess player's guess as to code.
    @return 1 if guess matches code.
    */
    bool guessEval(string code, string guess);
};

#endif
