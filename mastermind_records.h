/**
CS-11 Sampler Project
store.cpp
Purpose: Allows players of Mastermind2.0 to create and access records.

@author Russell Hofvendahl
@version 1.0 11/17/15
*/
#ifndef __MASTERMIND_RECORDS_H__
#define __MASTERMIND_RECORDS_H__

#include <vector>

class Record {
public:
    /**
    Default constructor for Record class.
    */
    Record();

    /**
    Overloaded constructor for Record class.

    @param newName desired product name.
    @param newPrice desired product price.
    @param newQuantity desired product quantity.
    */
    Record(int newLength, int newChars, int newScore, string newName);

    /**
    Returns length of record.

    @return length of record.
    */
    int getLength() const;

    /**
    Returns chars of record.

    @return chars of record.
    */
    int getChars() const;

    /**
    Returns score of record.

    @return score of record.
    */
    int getScore() const;

    /**
    Returns name of record holder.

    @return name of record holder.
    */
    string getName() const;

    /**
    Prints length, chars, score and name.
    */
    void print() const;

    /**
    Loads information about this Record from the file stream.

    @param fin an input stream connected to the files with the
    data to load.
    */
    void read(ifstream& fin);

    /**
    Writes information about this Record to the file stream.

    @param fout An output stream connected to the file in
    which to save the data.
    */
    void write(ofstream& fout) const;

private:
    int length;
    int chars;
    int score;
    string name;
};

/**
Displays length, chars, score and name for all records.

@param records The vector of objects.
*/
void display(const vector<Record>& records);

/**
Displays length, chars, score and name for a given length and chars within
records.

@param length A selection criteria.
@param chars A selection criteria.
@param records The vector of objects.
*/
void display(int length, int chars, const vector<Record>& records);

/**
Loads records from mastermind_records.txt and returns the data in a vector
of Record objects.

@param records The vector of objects.
*/
void loadRecords(vector<Record>& records);

/**
Writes records to an output file.

@param records The vector of Product objects.
*/
void saveRecords(const vector<Record>& records);

#endif
