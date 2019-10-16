/**
    CS-11 Sampler Project
    store.cpp
    Purpose: Allows players of Mastermind2.0 to create and access records.

    @author Russell Hofvendahl
    @version 1.0 11/17/15
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

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

Record::Record() {
    length = 0;
    chars = 0;
    score = 0;
    name = "";
}
Record::Record(int newLength, int newChars, int newScore, string newName) {
    length = newLength;
    chars = newChars;
    score = newScore;
    name = newName;
}

int Record::getLength() const {
    return length;
}

int Record::getChars() const {
    return chars;
}

int Record::getScore() const {
    return score;
}

string Record::getName() const {
    return name;
}

void Record::print() const {
  cout << left << setw(6) << length << setw(6) << chars << setw(6) << score
       << name << endl;
}

void Record::read(ifstream& fin) {
    fin >> length >> chars >> score;
    fin >> ws;
    getline(fin, name);
}

void Record::write(ofstream& fout) const {
    fout << length << endl << chars << endl << score << endl
         << name << endl;
}

/**
    Displays length, chars, score and name for all records.

    @param records The vector of objects.
*/
void display(const vector<Record>& records) {
    cout << "Lngth Chars Score Name\n";
    for (unsigned i = 0; i < records.size(); i++) {
        records[i].print();
    }
    cout << endl;
}

/**
    Displays length, chars, score and name for a given length and chars within
    records.

    @param length A selection criteria.
    @param chars A selection criteria.
    @param records The vector of objects.
*/
void display(int length, int chars, const vector<Record>& records) {
    cout << "Length Chars Score Name\n";
    int sum = 0;
    int hiScore = 0;
    for (unsigned i = 0; i < records.size(); i++) {
        if ((records[i].getLength() == length) && (records[i].getChars() == chars))
            records[i].print();
        sum += records[i].getScore();
        if (records[i].getScore() > records[hiScore].getScore()) hiScore = i;
    }
    cout << fixed << setprecision(2) << "Average score: " << sum / records[hiScore].getLength() << "\nHigh score: "
         << records[hiScore].getScore() << ", " << records[hiScore].getName()
         << endl;
}

/**
    Loads records from mastermind_records.txt and returns the data in a vector
    of Record objects.

    @param records The vector of objects.
*/
void loadRecords(vector<Record>& records) {
    ifstream fin("mastermind_records.txt");
    if (fin.fail()) {
        cout << "Input file failed to open\n";
    }

    Record temp;
    temp.read(fin);
    while (fin) {
        records.push_back(temp);
        temp.read(fin);
    }
    fin.close();
}

/**
    Writes records to an output file.

    @param records The vector of Product objects.
*/
void saveRecords(const vector<Record>& records) {
    ofstream fout("mastermind_records.txt");
    if (fout.fail()) {
        cout << "Output file failed to open\n";
    }

    Record temp;
    for (unsigned i = 0; i < records.size(); i++) {
        temp = records[i];
        temp.write(fout);
    }
    fout.close();
}
