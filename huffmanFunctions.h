//
// Created by Leira on 22/12/2021.
//

#ifndef FIRSTC___HUFFMANFUNCTIONS_H
#define FIRSTC___HUFFMANFUNCTIONS_H

#define NUM_MAX_CARATTERI 128

#include <string>
using namespace std;

typedef struct occurence {
    char c;
    int count;
    occurence* father;
    occurence* leftSon;
    occurence* rightSon;
    string path;
} Occurrence;


void acquire(const string&);

void printOccurrencesOnFile();
void printOccurrencesOnTerminal();

void countOccurrences(const string&);
void setOnlyOccurrencesVet();
void orderOnlyOccurrencesVet(int, int);
void createTree();
void encode(Occurrence*);

void printTree(Occurrence*, ostream&);
int getSentenceDimAfter(Occurrence*, int);
int getSentenceDimBefore();

//string switchStringToPrint(int i);

#endif //FIRSTC___HUFFMANFUNCTIONS_H
