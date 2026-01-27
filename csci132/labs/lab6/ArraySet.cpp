#include "ArraySet.h"
#include <cassert>

template<class ItemType>
ArraySet<ItemType>::ArraySet() {
  maxItems = DEFAULT_CAPACITY;
  items = new ItemType[maxItems];
  itemCount = 0;
}  // end default constructor

template<class ItemType>
ArraySet<ItemType>::ArraySet(int capacity) {
  assert(capacity > 0);
  maxItems = capacity;
  items = new ItemType[maxItems];
  itemCount = 0;
}  // end one-argument constructor

template<class ItemType>
ArraySet<ItemType>::ArraySet(const ArraySet<ItemType>& original) {
  maxItems = original.maxItems;
  items = new ItemType[maxItems];
  itemCount = original.itemCount;
  for (int i = 0; i < itemCount; i++)
    items[i] = original.items[i];
}  // end copy constructor

template<class ItemType>
ArraySet<ItemType>::~ArraySet() {
  delete[] items;
}

template<class ItemType>
ArraySet<ItemType>& ArraySet<ItemType>::operator=(const ArraySet<ItemType>& other) {
  if (this != &other) {
    delete[] items;
    maxItems = other.maxItems;
    items = new ItemType[maxItems];
    itemCount = other.itemCount;
    for (int i = 0; i < itemCount; i++)
      items[i] = other.items[i];
  }
  return *this;
}  // end assignment operator

template<class ItemType>
bool ArraySet<ItemType>::add(const ItemType& newEntry) {
  if (contains(newEntry))
    return true;
  bool hasRoomToAdd = (itemCount < maxItems);
  if (!hasRoomToAdd) {
    // Grow the array
    ItemType *newItems = new ItemType[maxItems * 2];
    for (int i = 0; i < itemCount; i++)
      newItems[i] = items[i];
    delete[] items;
    items = newItems;
    maxItems *= 2;
  }
  items[itemCount] = newEntry;
  itemCount++;
  return true;
}

template<class ItemType>
int ArraySet<ItemType>::getCurrentSize() const {
  return itemCount;
}  // end getCurrentSize

template<class ItemType>
int ArraySet<ItemType>::size() const {
  return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArraySet<ItemType>::isEmpty() const {
  return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArraySet<ItemType>::isFull() const {
  return false; // this implementation grows the array as needed
}  // end isFull

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

template<class ItemType>
std::string ArraySet<ItemType>::toPrettyString() const {
  if (itemCount == 0)
    return "{ }";
  else
    return "{ " + toStringWithSeparator(", ") + " }";
}  // end toPrettyString

template<class ItemType>
std::string ArraySet<ItemType>::toString() const {
  return toStringWithSeparator("");
}  // end toString

template<class ItemType>
std::string ArraySet<ItemType>::toStringWithSeparator(const std::string &separator) const {
  if (itemCount == 0)
    return "";
  std::string s = "";
  s += items[0];
  for (int i = 1; i < itemCount; i++)
    s += separator + items[i];
  return s;
}  // end toStringWithSeparator

