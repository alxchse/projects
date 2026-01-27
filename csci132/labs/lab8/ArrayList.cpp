// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Implementation file for the class ArrayList.
// Modified:
//  17 March 2021 - K. Walsh - Added helper methods, made array dynamically
//    resizing.
//  21 March 2021 - K. Walsh - Changed PrecondViolatedExcept to use standard C++
//    exceptions instead.
//  21 March 2021 - K. Walsh - Changed the toString methods to use stringstream.

#include "ArrayList.h"
#include <stdexcept>
#include <cassert>
#include <sstream>

template<class ItemType>
ArrayList<ItemType>::ArrayList()
{
  maxItems = DEFAULT_CAPACITY;
  items = new ItemType[maxItems+1];
  itemCount = 0;
}  // end default constructor

template<class ItemType>
ArrayList<ItemType>::ArrayList(int capacity) {
  assert(capacity > 0);
  maxItems = capacity;
  items = new ItemType[maxItems+1];
  itemCount = 0;
}  // end one-argument constructor

template<class ItemType>
ArrayList<ItemType>::ArrayList(const ArrayList<ItemType>& original) {
  maxItems = original.maxItems;
  items = new ItemType[maxItems+1];
  itemCount = original.itemCount;
  for (int i = 1; i <= itemCount; i++)
    items[i] = original.items[i];
}  // end copy constructor

template<class ItemType>
ArrayList<ItemType>::~ArrayList() {
  delete[] items;
}

template<class ItemType>
ArrayList<ItemType>& ArrayList<ItemType>::operator=(const ArrayList<ItemType>& other) {
  if (this != &other) {
    delete[] items;
    maxItems = other.maxItems;
    items = new ItemType[maxItems+1];
    itemCount = other.itemCount;
    for (int i = 1; i <= itemCount; i++)
      items[i] = other.items[i];
  }
  return *this;
}  // end assignment operator


template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
  return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayList<ItemType>::isFull() const
{
  return false;
}  // end isFull

template<class ItemType>
int ArrayList<ItemType>::getLength() const
{
  return itemCount;
}  // end getLength

template<class ItemType>
int ArrayList<ItemType>::size() const
{
  return itemCount;
}  // end size

template<class ItemType>
bool ArrayList<ItemType>::append(const ItemType& newEntry)
{
  return insert(itemCount+1, newEntry);
}

template<class ItemType>
bool ArrayList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
  if (newPosition < 1 || newPosition > itemCount + 1)
    return false;
  if (itemCount == maxItems) {
    // Grow the array
    ItemType *newItems = new ItemType[maxItems * 2 + 1];
    for (int i = 1; i <= itemCount; i++)
      newItems[i] = items[i];
    delete[] items;
    items = newItems;
    maxItems *= 2;
  }
  // Make room for new entry by shifting all entries at
  // positions >= newPosition toward the end of the array
  // (no shift if newPosition == itemCount + 1)
  for (int entryPosition = itemCount; entryPosition >= newPosition; entryPosition--)
    items[entryPosition + 1] = items[entryPosition]; // copy the entry right

  // Insert new entry
  items[newPosition] = newEntry;
  itemCount++;  // Increase count of entries

  return true;
}  // end insert

template<class ItemType>
bool ArrayList<ItemType>::remove(int position)
{
  bool ableToRemove = (position >= 1) && (position <= itemCount);
  if (ableToRemove)
  {
    // Remove entry by shifting all entries after the one at
    // position toward the beginning of the array
    // (no shift if position == itemCount)
    for (int entryPosition = position; entryPosition < itemCount; entryPosition++)
      items[entryPosition] = items[entryPosition + 1]; // copy entry on the right to left

    itemCount--;  // Decrease count of entries
  }  // end if

  return ableToRemove;
}  // end remove

template<class ItemType>
void ArrayList<ItemType>::clear()
{
  itemCount = 0;
}  // end clear

template<class ItemType>
void ArrayList<ItemType>::setEntry(int position, const ItemType& anEntry)
{
  // Enforce precondition
  bool ableToSet = (position >= 1) && (position <= itemCount);
  if (ableToSet)
  {
    items[position] = anEntry;
  }
  else
  {
    std::stringstream s;
    s << "setEntry(" << position << ", ...) called on a list of length " << itemCount << ".";
    s << " This is an invalid position.";
    throw std::runtime_error(s.str());
  }  // end if
}  // end setEntry

template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const
{
  // Enforce precondition
  bool ableToGet = (position >= 1) && (position <= itemCount);
  if (ableToGet)
  {
    return items[position];
  }
  else
  {
    std::stringstream s;
    s << "getEntry(" << position << ") called on a list of length " << itemCount << ".";
    s << " This is an invalid position.";
    throw std::runtime_error(s.str());
  }  // end if
}  // end getEntry

template<class ItemType>
ItemType ArrayList<ItemType>::replace(int position, const ItemType& newEntry)
{
  // Enforce precondition
  bool ableToSet = (position >= 1) && (position <= itemCount);
  if (ableToSet)
  {
    ItemType previous = items[position];
    items[position] = newEntry;
    return previous;
  }
  else
  {
    std::stringstream s;
    s << "replace(" << position << ", ...) called on a list of length " << itemCount << ".";
    s << " This is an invalid position.";
    throw std::runtime_error(s.str());
  }  // end if
}  // end replace

template<class ItemType>
bool ArrayList<ItemType>::contains(const ItemType& target) const {
  for (int i = 1; i <= itemCount; i++) {
    if (items[i] == target)
      return true;
  }
  return false;
}  // end contains

template<class ItemType>
int ArrayList<ItemType>::find(const ItemType& target) const {
  for (int i = 1; i <= itemCount; i++) {
    if (items[i] == target)
      return i;
  }
  return -1;
}  // end find

template<>
ArrayList<char> ArrayList<char>::fromString(const std::string& input) { 
  ArrayList<char> output;
  for (int i = 0; i < input.length(); i++) 
    output.insert(output.getLength()+1,input.at(i));
  return output;
}

template<class ItemType>
std::string ArrayList<ItemType>::toPrettyString() const {
  if (itemCount == 0)
    return "[ ]";
  else
    return "[ " + toStringWithSeparator(", ") + " ]";
}  // end toPrettyString

template<class ItemType>
std::string ArrayList<ItemType>::toString() const {
  return toStringWithSeparator("");
}  // end toString

template<class ItemType>
std::string ArrayList<ItemType>::toStringWithSeparator(const std::string &separator) const {
  if (itemCount == 0)
    return "";
  // Frustratingly, in C++ you can't join together a string with other data
  // types. Instead, you need to use a std::stringstream to do it, then
  // convert the std::stringstream to a string.
  std::stringstream s;
  s << items[1];
  for (int i = 2; i <= itemCount; i++) {
    s << separator << items[i];
  }
  return s.str();
}  // end toStringWithSeparator

