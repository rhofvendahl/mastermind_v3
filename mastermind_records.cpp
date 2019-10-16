#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

#include "mastermind_records.h"

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

void display(const vector<Record>& records) {
    cout << "Lngth Chars Score Name\n";
    for (unsigned i = 0; i < records.size(); i++) {
        records[i].print();
    }
    cout << endl;
}

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
