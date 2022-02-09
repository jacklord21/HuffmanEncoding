#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "huffmanFunctions.h"

using namespace std;

[[noreturn]] void start();
void printMenu();
void switchChoice(int);

int main() {

    start();
/*    string path = "";



  //  string path = "G:/Il mio Drive/Portatile/File e documenti/file/txt/expressvpn.txt";
    string frase = "ciao a tutti";
    frase = "Se qualcuno lo facesse ma non fosse sicuro sarebbe meglio farlo per sicurezza o non farlo per insicurezza";
 //   frase = "ciao sono mario rossi   ";

    string fileText, temp;
    ifstream inf(path, ios::in);;

    if(inf.is_open()) {
        cout << "FILE OPENED" << endl;
        while(getline(inf, temp)) {
            fileText += temp;
            fileText.push_back('\n');
        }
    }
    else cout << "FILE NOT OPENED";

//    cout << fileText;

    cout << "SOMMA OCCORRENZE PRIMA: " << frase.size()*8 << endl;
    countOccurrences(fileText);
    createTree();
    exit(0);


  //  start();*/
}

[[noreturn]] void start() {

    int choice=0;
    vector<int> choices = {0, 1, 2, 3, 4};

    while(true) {
        printMenu();

        cout << "\nInsert choice: ";
        cin >> choice;

        while(find(choices.begin(), choices.end(), choice)==choices.end()) {
            cout << "Wrong choice. Try again: ";
            cin >> choice;
        }

        switchChoice(choice);
    }
}

void switchChoice(int choice) {
    switch (choice) {
        case 1: acquire("terminal"); break;
        case 2: acquire("file"); break;
        case 3:
            printOccurrencesOnTerminal(); break;
        case 4:
            printOccurrencesOnFile();  break;
        case 0: exit(0);
        default: return;
    }
}

void printMenu() {
    cout << "\n\nHUFFMAN ENCODING PROGRAM MENÙ\n" << endl;
    cout << "1. Input from terminal" << endl;
    cout << "2. Input from file" << endl;
    cout << "3. Print occurrences on terminal" << endl;
    cout << "4. Print occurrences on file" << endl;
    cout << "0. Exit program" << endl;
}