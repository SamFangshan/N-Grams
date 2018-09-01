//Author: https://github.com/SamFangshan
#include <iostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "queue.h"
#include "map.h"
#include "vector.h"
#include "random.h"
using namespace std;

void printOpenning();
void readFile(Map<Queue<string>, Vector<string> >& map, int& n);
void generateSentences(Map<Queue<string>, Vector<string> >& map, int& n);
void realGenerate(Map<Queue<string>, Vector<string> >& map, int& n, int& num);

int main() {
    printOpenning();

    Map<Queue<string>, Vector<string> > map;
    int n;
    readFile(map, n);

    generateSentences(map, n);

    cout << "Exiting." << endl;
    return 0;
}


void printOpenning() {
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;
    cout << "" << endl;
}

void readFile(Map<Queue<string>, Vector<string> >& map, int& n) {
    ifstream file;
    promptUserForFile(file, "Input file name? ");
    n = getInteger("Value of N? ");
    while (n < 2) {
        cout << "N must be 2 or greater." << endl;
         n = getInteger("Value of N? ");
    }

    string word;
    Queue<string> window;
    for (int i = 0; i < n - 1; i++) {
        file >> word;
        window.enqueue(word);
    }

    Queue<string> original = window;

    while (file >> word) {
        Vector<string> value;
        value.add(word);
        if(map.containsKey(window)) {
            Vector<string> v = map.get(window);
            v.add(word);
            map.put(window, v);
        } else {
            map.put(window, value);
        }
        window.dequeue();
        window.enqueue(word);
    }

    for (int i = 0; i < n - 1; i++) {
        word = original.dequeue();
        Vector<string> value;
        value.add(word);
        if(map.containsKey(window)) {
            Vector<string> v = map.get(window);
            v.add(word);
            map.put(window, v);
        } else {
            map.put(window, value);
        }
        window.dequeue();
        window.enqueue(word);
    }
}

void generateSentences(Map<Queue<string>, Vector<string> >& map, int& n) {
    int num = 1;
    cout << "" << endl;
    num = getInteger("# of random words to generate (0 to quit)? ");
    while (num < n && num != 0) {
        cout << "Must be at least " << n << " words." << endl;
        cout << "" << endl;
        num = getInteger("# of random words to generate (0 to quit)? ");
    }
    while (num != 0) {
        realGenerate(map, n, num);
        num = getInteger("# of random words to generate (0 to quit)? ");
        while (num < n && num != 0) {
            cout << "Must be at least " << n << " words." << endl;
            cout << "" << endl;
            num = getInteger("# of random words to generate (0 to quit)? ");
        }
    }
}

void realGenerate(Map<Queue<string>, Vector<string> >& map, int& n, int& num) {
    Vector<Queue<string> > keys = map.keys();
    Queue<string> key = keys.get(randomInteger(0, keys.size() - 1));
    ostringstream outputText;
    outputText << "... ";
    for (int i = 0; i < num; i++) {
        Vector<string> value = map.get(key);
        outputText << key.dequeue() << " ";
        string outString = value.get(randomInteger(0, value.size() - 1));
        key.enqueue(outString);
    }
    outputText << "..." << endl;
    cout << outputText.str() << endl;
}
