#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;


void print(string anItem);

int main() {
    cout << "Testing Hashed Dictionary Implementation using Chaining" << endl << endl ;
    DictionaryInterface<int, string>* dict = new HashTable<int, string>();
   
    string letters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};
    for (int i = 1; i <= 16; i++)
        dict->add(i*10, letters[i-1]);
   
    cout << "Traversing entries in the dictionary: \n";
    dict->traverse(print);
   
    dict->remove(10);
    dict->remove(60);
    dict->remove(160);
   
    cout << "\nAfter Removing 10/A, 60/F, and 160/P, traversing entries in the dictionary:\n";
    dict->traverse(print);
    cout << endl << endl;
   
    cout << "Getting key/item 20/B: "<< dict->getItem(20) << endl;
    cout << "Getting key/item 90/I: "<< dict->getItem(90) << endl;
    cout << "Getting key/item 70/G: "<< dict->getItem(70) << endl;
    cout << endl << endl;
   
    if (dict->contains(100)) 
        cout << "Correctly returns true when checking if dictionary contains key/item 110/H." << endl;
    else 
        cout << "Incorrectly returns false when checking if dictionary contains key/item 110/H." << endl;

    if (!dict->contains(10)) 
        cout << "Correctly returns false when checking if dictionary contains key/entry 10/A (which was removed)." << endl;
    else 
        cout << "Incorrectly returns true when checking if dictionary contains key/entry 10/A (which was removed)." << endl;

    if (!dict->contains(200)) 
        cout << "Correctly returns false when checking if dictionary contains entry with key 200." << endl;
    else 
        cout << "Incorrectly returns true when checking if dictionary contains key 200." << endl;


    dict->clear();
   
    cout << endl << endl << "Trying to traverse after clear." << endl;
    dict->traverse(print);
    cout << "Nothing should be displayed above if traverse is working properly." << endl << endl;

    if (!dict->contains(20)) 
        cout << "Correctly returns false when checking if empty dictionary contains key/entry 20/B." << endl;
    else 
        cout << "Incorrectly returns true when checking if empty dictionary contains key/entry 20/B." << endl;
    
   return 0;
}

void print(string anItem) {
   cout << "Displaying entry: " << anItem << endl;
}  // end print


