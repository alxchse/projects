// Header file for an array-based implementation of the ADT set.
// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//
// Modified:
//  17 March 2021 - K. Walsh - made it dynamically resizable
//    and new constructors, destructor, and assignment operator.

#ifndef ARRAY_SET_
#define ARRAY_SET_

#include "SetInterface.h"
#include <string>

template<class ItemType>
class ArraySet : public SetInterface<ItemType> {
  private:
    static const int DEFAULT_CAPACITY = 50;
    ItemType *items;   // Dynamically resizing array
    int itemCount;     // Current count of set items 
    int maxItems;      // Max capacity of the set

    // Returns either the index of the element in the array items that
    // contains the given target or -1, if the array does not contain 
    // the target.
    int getIndexOf(const ItemType& target) const;   

  public:
    ArraySet(); // Default constructor, initializes with a default capacity
    ArraySet(int capacity);  // Initialize with given capacity
    ArraySet(const ArraySet<ItemType>& original); // Copy constructor
    ~ArraySet(); // Destructor
    ArraySet<ItemType>& operator=(const ArraySet<ItemType>& other); // Assignment operator

    int size() const; // same as getCurrentSize()
    int getCurrentSize() const;

    bool isEmpty() const;
    bool isFull() const; // note: always returns false

    bool add(const ItemType& newEntry);
    bool remove(const ItemType& anEntry);

    void clear();

    bool contains(const ItemType& anEntry) const;

    // NOTE: The following methods do not guarantee any particular ordering
    // to the items. The items could be returned in any arbitrary ordering,
    // and the ordering could change from one moment to the next. So you
    // should not rely on the order of items in the set. The ONLY exception
    // to this rule is that the ordering of items will not change if the
    // client is careful to not modify the set in any way. In other words, a
    // client that is careful to only call const methods can be assured that
    // the order of items (whatever order that might be) won't suddenly
    // change until the next time a non-const method is called.
    
    // Appends all items together into a single string, with no spaces, commas,
    // or other decorations, and returns the resulting string.
    // Example: "ABC" (if the set contains "A", "B", and "C").
    std::string toString() const;

    // Appends all items together into a single string, with spaces, commas,
    // and braces on the outside, and returns the resulting string. 
    // Example: "{ A, B, C }" (if the set contains "A", "B", and "C").
    std::string toPrettyString() const;

    // Appends all items together into a single string, using the given
    // separator between the items, and returns the resulting string.
    // Example: toStringWithSeparator(" and ") would
    //  return "A and B and C" (if the set contains "A", "B", and "C").
    std::string toStringWithSeparator(const std::string &separator) const;

    std::vector<ItemType> toVector() const;

}; // end ArraySet

#include "ArraySet.cpp"
#endif
