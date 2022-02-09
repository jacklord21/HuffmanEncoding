//
// Created by Leira on 26/12/2021.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "huffmanFunctions.h"

using namespace std;

Occurrence** onlyFoundOccurrencesVet;
Occurrence* allPossibleOccurrencesVet[NUM_MAX_CARATTERI] = {};
int onlyFoundOccurrencesDim;


void acquire(const string& flag) {

    string frase;

    if(flag=="terminal") {
        cout << "Insert sentence: "; cin.ignore(); getline(cin, frase);
    }
    else if(flag=="file") {
        string path;
        char* buffer = (char*)malloc(sizeof(char)*1024);

        cout << "Insert file path: "; //cin.ignore(); getline(cin, path);
        cin >> path;


        FILE* file = fopen(path.c_str(), "r");
        while(fread(buffer, sizeof(char), 1024, file)!=0)
            frase+=buffer;
        fclose(file);
    }

    countOccurrences(frase); cout << "\n\nINFO] Occurrences correctly counted." << endl;
    createTree(); cout << "INFO] Occurrences tree correctly created." << endl;
}

void printOccurrencesOnTerminal() {
    printTree(onlyFoundOccurrencesVet[onlyFoundOccurrencesDim-1], cout);
    cout << "\nDimensione prima della codifica (numero di bit): " << getSentenceDimBefore() << endl;
    cout << "Dimensione in bit dopo della codifica (numero di bit): " << getSentenceDimAfter(
            onlyFoundOccurrencesVet[onlyFoundOccurrencesDim - 1], 0) << endl;
}

void printOccurrencesOnFile() {
    ofstream of("output.txt", ios::out);

    printTree(onlyFoundOccurrencesVet[onlyFoundOccurrencesDim-1], of);
    of << "\nDimensione prima della codifica (numero di bit): " << getSentenceDimBefore() << endl;
    of << "Dimensione in bit dopo della codifica (numero di bit): " << getSentenceDimAfter(
            onlyFoundOccurrencesVet[onlyFoundOccurrencesDim - 1], 0) << endl;
    of.close();
}

void countOccurrences(const string& frase) {
    int cod;

    for (char i: frase) {
        cod = (int) ((unsigned char) i);

        if(cod==13) continue;
        else if (allPossibleOccurrencesVet[cod] == nullptr) {
            onlyFoundOccurrencesDim++;
            allPossibleOccurrencesVet[cod] = new Occurrence{i, 1, nullptr, nullptr, nullptr, ""};
        }
        else allPossibleOccurrencesVet[cod]->count++;
    }

    setOnlyOccurrencesVet();
    orderOnlyOccurrencesVet(0, onlyFoundOccurrencesDim - 1);
}

void setOnlyOccurrencesVet() {
    int index=0;
    onlyFoundOccurrencesVet = new Occurrence* [onlyFoundOccurrencesDim];

    for(auto & i : allPossibleOccurrencesVet)
        if(i!=nullptr) onlyFoundOccurrencesVet[index++] = new Occurrence{i->c, i->count, nullptr, nullptr, nullptr, ""};
}

void orderOnlyOccurrencesVet(int start, int end) {
    int k;
    do{
        k=0;

        for (int i = start; i < end; i++)
            if(onlyFoundOccurrencesVet[i]->count > onlyFoundOccurrencesVet[i + 1]->count) {
                swap(onlyFoundOccurrencesVet[i], onlyFoundOccurrencesVet[i + 1]);
                k=1;
            }
    } while(k);
}

void createTree() {
    int first, second, dim = onlyFoundOccurrencesDim, start=0;

    do{
        first = start, second = start+1;

        auto* fatherNode = new Occurrence {0, onlyFoundOccurrencesVet[first]->count+onlyFoundOccurrencesVet[second]->count, nullptr, onlyFoundOccurrencesVet[first], onlyFoundOccurrencesVet[second], ""};

        onlyFoundOccurrencesVet[first]->father = fatherNode; onlyFoundOccurrencesVet[first]->path = "0";
        onlyFoundOccurrencesVet[second]->father = fatherNode; onlyFoundOccurrencesVet[second]->path = "1";

        onlyFoundOccurrencesVet[first] = nullptr;  onlyFoundOccurrencesVet[second]= fatherNode;

        orderOnlyOccurrencesVet(++start, onlyFoundOccurrencesDim - 1);
    }
    while(--dim>1);

    encode(onlyFoundOccurrencesVet[onlyFoundOccurrencesDim-1]);
}


int getSentenceDimBefore() {
    int somma = 0;

    for(auto & i : allPossibleOccurrencesVet)
        if(i!= nullptr) somma += i->count*8;

    return somma;
}

int getSentenceDimAfter(Occurrence* node, int somma) {
    if(node!=nullptr) {
        if (!node->leftSon && !node->rightSon) somma = somma + (int) (node->count * node->path.length());
        if (node->leftSon) somma = getSentenceDimAfter(node->leftSon, somma);
        if (node->rightSon) somma = getSentenceDimAfter(node->rightSon, somma);
    }

    return somma;
}


void printTree(Occurrence* node, ostream& ris) {
    if(node== nullptr) return;

    if(!node->leftSon && !node->rightSon)
        ris << "'" << node->c << "'\t:" << node->count << "\t" << node->path << endl;

    printTree(node->leftSon, ris);
    printTree(node->rightSon, ris);
}

void encode(Occurrence* node) {
    if(node== nullptr) return;

    if(node->father) node->path= node->father->path + node->path;
    encode(node->leftSon);
    encode(node->rightSon);
}

/*string switchStringToPrint(char c) {
    if(c == 32) return "(space)";
    else if(c == 10) return "(enter)";

    return string(1, c);
}*/