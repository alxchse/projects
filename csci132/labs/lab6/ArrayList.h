// ADT list: Array-based implementation.
// Listing 9-1.
// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  17 March 2021 - K. Walsh - Added helper methods, made array dynamically
//    resizing.

#ifndef ARRAY_LIST_
#define ARRAY_LIST_

#include "ListInterface.h"
#include <string>

template<class ItemType>
class ArrayList : public ListInterface<ItemType>
{
  private:
    static const int DEFAULT_CAPACITY = 50; // Default capacity of the list

    ItemType *items; // Dynamically resizing array of list items (ignore items[0])
    int itemCount;  // Current count of list items
    int maxItems;   // Current capacity of the list

  public:
    ArrayList(); // Default constructor, initializes with a default capacity
    ArrayList(int capacity);  // Initialize with given capacity
    ArrayList(const ArrayList<ItemType>& original); // Copy constructor
    ~ArrayList(); // Destructor
    ArrayList<ItemType>& operator=(const ArrayList<ItemType>& other); // Assignment operator

    bool isEmpty() const;
    bool isFull() const; // note: always returns false

    int getLength() const;
    int size() const; // same as getLength()

    ItemType getEntry(int position) const;
    bool contains(const ItemType& anEntry) const;
    int find(const ItemType& anEntry) const; // returns position of item, or -1 if not found
    void setEntry(int position, const ItemType& newEntry);
    ItemType replace(int position, const ItemType& newEntry); // similar to setEntry()
    bool insert(int newPosition, const ItemType& newEntry);
    bool append(const ItemType& newEntry); // same as insert(size()+1, newEntry)
    bool remove(int position);
    void clear();

    // Appends all items together into a single string, with no spaces, commas,
    // or other decorations, and returns the resulting string.
    // Example: "ABC" (if the list contains "A", "B", and "C").
    std::string toString() const;

    // Appends all items together into a single string, with spaces, commas,
    // and brackets on the outside, and returns the resulting string.
    // Example: "[ A, B, C ]" (if the list contains "A", "B", and "C").
    std::string toPrettyString() const;

    // Appends all items together into a single string, using the given
    // separator between the items, and returns the resulting string.
    // Example: toStringWithSeparator(" and ") would
    //  return "A and B and C" (if the list contains "A", "B", and "C").
    std::string toStringWithSeparator(const std::string &separator) const;

    // Splits the string into pieces, and returns a list containing all of the
    // pieces. Currently, this only works for ArrayList<char>, i.e. when
    // ItemType is char.
    static ArrayList<ItemType> fromString(const std::string &s);

}; // end ArrayList

#include "ArrayList.cpp"
#endif 
