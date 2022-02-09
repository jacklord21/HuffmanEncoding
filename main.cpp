#include <vector>
#include <iostream>
#include <algorithm>
#include "huffmanFunctions.h"

using namespace std;

[[noreturn]] void start();
void printMenu();
void switchChoice(int);

int main() {
    start();
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