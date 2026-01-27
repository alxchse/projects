//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 18-5.

/** A class of entry objects for a hashing implementation of the
    ADT dictionary.
 @file HashedEntry.h */
 
#ifndef HASHED_ENTRY_
#define HASHED_ENTRY_

#include <memory>
#include "Entry.h"

template<class KeyType, class ItemType>
class HashedEntry : public Entry<KeyType, ItemType> {
    private:
        HashedEntry<KeyType, ItemType>* nextPtr;
   
    public:
        HashedEntry();
        HashedEntry(KeyType itemKey, ItemType newEntry);
        HashedEntry(KeyType itemKey, ItemType newEntry,
                    HashedEntry<KeyType, ItemType>* nextEntryPtr);
   
        void setNext(HashedEntry<KeyType, ItemType>* nextEntryPtr);
        HashedEntry<KeyType, ItemType>* getNext() const;
}; // end HashedEntry

#include "HashedEntry.cpp"
#endif
