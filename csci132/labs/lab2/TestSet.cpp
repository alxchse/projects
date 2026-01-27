// A test program to practice with implementations of the set interface.
// Author: Z. Fitzsimmons, 2020
// Modified: K. Walsh, 10 Feb 2021 - added preconditions, scrambled order of sets

#include "SetInterface.h"
#include "ParallelArraySet.h"

#include <iostream>
using namespace std;

// These are prototypes for additional functions dealing with SetInterfaces. 
// Because C++ compilers read the code in order, from top to bottom,
// these prototypes need to appear in this .cpp file "above" main(), so that
// main() can call these functions.
// The implementation for these functions can then go at the bottom of this file.
SetInterface<int>* merge(const SetInterface<int>* first, const SetInterface<int>* second);
SetInterface<int>* intersection(const SetInterface<int>* first, const SetInterface<int>* second);
SetInterface<int>* difference(const SetInterface<int>* first, const SetInterface<int>* second);
void printSet(const SetInterface<int>* first);

SetInterface<int>* makeNewEmptySetForTesting() {
  return new ParallelArraySet<int>();
}

int main() {
    SetInterface<int>* one = makeNewEmptySetForTesting();
    SetInterface<int>* two = makeNewEmptySetForTesting();
    SetInterface<int>* three = makeNewEmptySetForTesting();

    if (!one->add(2)) cout << "Could not add 2 to set one.\n";
    if (!one->add(5)) cout << "Could not add 5 to set one.\n";
    if (!one->add(32)) cout << "Could not add 32 to set one.\n";
    if (!one->add(8)) cout << "Could not add 8 to set one.\n";
    if (!one->add(17)) cout << "Could not add 17 to set one.\n";
    if (one->add(17)) cout << "Oops, was able to add 17 TWICE to set one.\n";
    if (one->add(5)) cout << "Oops, was able to add 5 TWICE to set one.\n";
    cout << "Set 1 (contains " << one->getCurrentSize() << " elements) : ";
    printSet(one);

    if (!two->add(1)) cout << "Could not add 1 to set two.\n";
    if (!two->add(2)) cout << "Could not add 2 to set two.\n";
    if (!two->add(3)) cout << "Could not add 3 to set two.\n";
    if (!two->add(4)) cout << "Could not add 4 to set two.\n";
    if (!two->remove(1)) cout << "Could not remove 1 from set two.\n";
    if (!two->add(8)) cout << "Could not add 8 to set two.\n";
    if (!two->add(16)) cout << "Could not add 16 to set two.\n";
    if (!two->remove(3)) cout << "Could not remove 3 from set two.\n";
    if (!two->add(32)) cout << "Could not add 32 to set two.\n";
    if (two->add(2)) cout << "Oops, was able to add 2 TWICE to set two.\n";
    if (two->add(8)) cout << "Oops, was able to add 8 TWICE to set two.\n";
    cout << "Set 2 (contains " << two->getCurrentSize() << " elements) : ";
    printSet(two);
     
    if (!three->add(6)) cout << "Could not add 6 to set three.\n";
    if (!three->add(2)) cout << "Could not add 2 to set three.\n";
    if (!three->add(3)) cout << "Could not add 3 to set three.\n";
    if (!three->add(5)) cout << "Could not add 5 to set three.\n";
    if (!three->add(8)) cout << "Could not add 8 to set three.\n";
    if (!three->add(4)) cout << "Could not add 4 to set three.\n";
    if (!three->add(7)) cout << "Could not add 7 to set three.\n";
    if (!three->add(1)) cout << "Could not add 1 to set three.\n";
    if (!three->add(9)) cout << "Could not add 9 to set three.\n"; // note: this will fail, because set is full
    if (!three->add(10)) cout << "Could not add 10 to set three.\n"; // note: this will fail, because set is full
    cout << "Set 3 (contains " << three->getCurrentSize() << " elements) : ";
    printSet(three);
    
    SetInterface<int>* result = nullptr;

    cout << endl;
    cout << "Computing union of Set 1 and Set 2... result is " << endl;
    result = merge(one, two);
    printSet(result);
    delete result;
    result = nullptr;

    cout << endl;
    cout << "Computing intersection of Set 1 and Set 2... result is " << endl;
    result = intersection(one, two);
    printSet(result);
    delete result;
    result = nullptr;

    cout << endl;
    cout << "Computing difference of Set 1 and Set 3... result is " << endl;
    result = difference(one, three);
    printSet(result);
    delete result;
    result = nullptr;

    cout << endl;
    cout << "Computing union of Set 1 and Set 3... result is " << endl;
    result = merge(one, three);
    printSet(result);
    delete result;
    result = nullptr;

    return 0;
}

// Preconditions: none (they are included in add).
// Postconditions: prints all nums from either set and
// prints them in outputSet.
SetInterface<int>* merge(const SetInterface<int>* first, const SetInterface<int>* second) {
    SetInterface<int>* outputSet = makeNewEmptySetForTesting();

        vector<int> firstVec = first->toVector();
        vector<int> secondVec = second->toVector();
     
    for (int i = 0; i < firstVec.size(); i++) {
        outputSet->add(firstVec[i]);
    }

    for (int i = 0; i < secondVec.size(); i++){
        outputSet->add(secondVec[i]);
    }
    return outputSet;
}

// Preconditions: none.
// Postconditions: finds all nums included both sets
// and prints them out in output set.
SetInterface<int>* intersection(const SetInterface<int>* first, const SetInterface<int>* second) {
    SetInterface<int>* outputSet = makeNewEmptySetForTesting();

    vector<int> firstVec = first->toVector();
   
    for (int i = 0; i < firstVec.size(); i++){
        if (second->contains(firstVec[i]))
            outputSet->add(firstVec[i]);
    }

    return outputSet;
}

// Preconditions: none
// Postconditions: finds all nums included in one set but not the other
// and prints them out in output set.
SetInterface<int>* difference(const SetInterface<int>* first, const SetInterface<int>* second) {
    SetInterface<int>* outputSet = makeNewEmptySetForTesting();

    vector<int> firstVec = first->toVector();
    vector<int> secondVec = second->toVector();

    for (int i = 0; i < firstVec.size(); i++) {
        if (!second->contains(firstVec[i]))
            outputSet->add(firstVec[i]);
    }

    return outputSet;
}

void printSet(const SetInterface<int>* first) {
    vector<int> firstVec = first->toVector();
    for(int i = 0; i < firstVec.size(); i++) {
        cout << firstVec[i] << " ";
    }
    cout << endl;
}
