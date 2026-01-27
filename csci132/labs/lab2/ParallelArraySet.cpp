// Implementation file for an array-based implementation of the ADT set.
// Author: Z. Fitzsimmons, 2020
// Modified: K. Walsh, 10 Feb 2021 - copied and modified from ArraySet.cpp

#include "ParallelArraySet.h"

template<class ItemType>
ParallelArraySet<ItemType>::ParallelArraySet() {
    maxItems = DEFAULT_CAPACITY;
    for (int i = 0; i < maxItems; i++)
        filled[i] = false;
}  // end default constructor

template<class ItemType>
bool ParallelArraySet<ItemType>::add(const ItemType& newEntry) {

    // precondition: make sure new entry isnt already in array
    if (contains(newEntry))
        return false;

    // precondition: make sure array has spots left
    for (int i = 0; i < maxItems; i++){
        if (!filled[i]) {
           items[i] = newEntry;
           filled[i] = true;
           return true; 
        } 
    }
    return false;

}  // end add

template<class ItemType>
int ParallelArraySet<ItemType>::getCurrentSize() const {
    int numFilled = 0;
    for (int i = 0; i < maxItems-1; i++){
        if (filled[i] == true)
        numFilled++;
    }
    return numFilled;
}  // end getCurrentSize

template<class ItemType>
bool ParallelArraySet<ItemType>::isEmpty() const {
    return getCurrentSize() == 0;
}  // end isEmpty

template<class ItemType>
std::vector<ItemType> ParallelArraySet<ItemType>::toVector() const {
    std::vector<ItemType> setContents;
    for (int i = 0; i < maxItems; i++)
        if (filled[i])
            setContents.push_back(items[i]);
    return setContents;
}  // end toVector


template<class ItemType>
bool ParallelArraySet<ItemType>::contains(const ItemType& target) const {
    
    for (int i = 0; i < getCurrentSize(); i++) {
        if (items[i] == target)
            return true;
    }
    return false;

}  // end contains

template<class ItemType>
void ParallelArraySet<ItemType>::clear() {
    for (int i = 0; i < maxItems; i++)
        filled[i] = false;
}  // end clear

template<class ItemType>
int ParallelArraySet<ItemType>::getIndexOf(const ItemType& target) const {
    for (int i = 0; i < maxItems; i++) {
        if (filled[i] && items[i] == target)
            return i;
    }
    return -1;
}  // end getIndexOf

template<class ItemType>
bool ParallelArraySet<ItemType>::remove(const ItemType& anEntry) {
    
    int locatedIndex = getIndexOf(anEntry);
        if (locatedIndex != -1){
            filled[locatedIndex] = false;
            return true;
        }
        return false;
}  // end remove
