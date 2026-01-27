//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file  HashedEntry.cpp */

#include "HashedEntry.h"

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry() {
   Entry<KeyType, ItemType>();
   nextPtr = nullptr;
}  // end 

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType itemKey, ItemType newEntry) {
   Entry<KeyType, ItemType>::setItem(newEntry);
   Entry<KeyType, ItemType>::setKey(itemKey);
   nextPtr = nullptr;
}  // end 

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType itemKey, ItemType newEntry,
                                            HashedEntry<KeyType, ItemType>* nextEntryPtr) {
   Entry<KeyType, ItemType>::setItem(newEntry);
   Entry<KeyType, ItemType>::setKey(itemKey);
   nextPtr = nextEntryPtr;
}  // end 

template<class KeyType, class ItemType>
void HashedEntry<KeyType, ItemType>::setNext(HashedEntry<KeyType, ItemType>* nextEntryPtr) {
   nextPtr = nextEntryPtr; 
}  // end 

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>* HashedEntry<KeyType, ItemType>::getNext() const {
   return nextPtr;
}  // end 

