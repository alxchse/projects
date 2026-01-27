//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// revisisons:
//   K. Walsh, 28 July 2020 - add fillArray(), get(), and getFrequencyOf()
//   K. Walsh, 25 January 2021 - added a one-argument constructor

/** Header file for an array-based implementation of the ADT bag. Listing 3-1.
  @file ArrayBag.h */

#ifndef ARRAY_BAG_
#define ARRAY_BAG_

#include "BagInterface.h"

template<class ItemType>
class ArrayBag : public BagInterface<ItemType> {
  private:
    static const int DEFAULT_CAPACITY = 8; // Small size to test for a full bag
    ItemType items[DEFAULT_CAPACITY];      // Array of bag items
    int itemCount;                         // Current count of bag items 
    int maxItems;                          // Max capacity of the bag

    // Returns either the index of the element in the array items that
    // contains the given target or -1, if the array does not contain 
    // the target.
    int getIndexOf(const ItemType& target) const;   

  public:
    ArrayBag(); // Default Constructor
    ArrayBag(int capacity); // Construct a bag with a given maximum capacity
    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& anEntry);
    void clear();
    bool contains(const ItemType& anEntry) const;
    ItemType get(int pos) const;
    int getFrequencyOf(const ItemType& anEntry) const;
    std::vector<ItemType> toVector() const;
    void fillArray(ItemType arr[]) const;

    // pickRandom selects a random item from this Bag.
    // precondition: this Bag must not be empty
    // returns: the randomly-selected item
    ItemType pickRandom() const; 
}; // end ArrayBag

#include "ArrayBag.cpp"
#endif
