// Implementation file for an array-based implementation of the ADT set.
// Author: Z. Fitzsimmons, 2020
// Modified: K. Walsh, 10 Feb 2021 - fixed typos in some comments.

#include "ArraySet.h"

template<class ItemType>
ArraySet<ItemType>::ArraySet()
{
    itemCount = 0;
    maxItems = DEFAULT_CAPACITY;
}  // end default constructor

template<class ItemType>
bool ArraySet<ItemType>::add(const ItemType& newEntry) {
    // precondition: make sure new entry isnt already in array
    if (contains(newEntry))
        return false;

    // precondition: make sure array has spots left
    if (!(itemCount < maxItems))
            return false;

    items[itemCount] = newEntry;
    itemCount++;  
    return true;
}  // end add

template<class ItemType>
int ArraySet<ItemType>::getCurrentSize() const {
    return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArraySet<ItemType>::isEmpty() const {
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
std::vector<ItemType> ArraySet<ItemType>::toVector() const {
    std::vector<ItemType> setContents;
    for (int i = 0; i < itemCount; i++)
        setContents.push_back(items[i]);

    return setContents;
}  // end toVector


template<class ItemType>
bool ArraySet<ItemType>::contains(const ItemType& target) const {
    for (int i = 0; i < itemCount; i++) {
        if (items[i] == target)
            return true;
    }
    return false;
}  // end contains

template<class ItemType>
void ArraySet<ItemType>::clear() {
    itemCount = 0;
}  // end clear

template<class ItemType>
int ArraySet<ItemType>::getIndexOf(const ItemType& target) const {
    bool isFound = false;
    int result = -1;
    int searchIndex = 0;

    // If the set is empty, itemCount is zero, so loop is skipped
    while (!isFound && (searchIndex < itemCount)) {
        isFound = (items[searchIndex] == target);
        if (isFound) {
            result = searchIndex;
        } else {
            searchIndex++;
        }  // end if
    }  // end while

    return result;
}  // end getIndexOf

template<class ItemType>
bool ArraySet<ItemType>::remove(const ItemType& anEntry) {
    int locatedIndex = getIndexOf(anEntry);
    bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
    if (canRemoveItem) {
        itemCount--;
        items[locatedIndex] = items[itemCount];
    }  // end if

    return canRemoveItem;
}  // end remove
