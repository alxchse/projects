//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//  December 2021 Adapted by Z. Fitzsimmons

/** @file  HashTable.h */

#ifndef HASH_TABLE_
#define HASH_TABLE_

#include "DictionaryInterface.h"
#include "NotFoundException.h"
#include "HashedEntry.h"

// HashTable implements a hash-based Dictionary. This implementation uses
// chaining to resolve collusions. Each key-value pair is stored in a
// HashedEntry object, and a table of pointers is maintained where each position
// in the table holds a chain of these objects.

template <class KeyType, class ValueType>
class HashTable : public DictionaryInterface<KeyType, ValueType> {
    private:
        HashedEntry<KeyType, ValueType>** table;  // Array of pointers to entries
        int itemCount;                           // Count of dictionary entries
        int tableCapacity;                       // Table size must be prime
        static const int DEFAULT_CAPACITY = 13;   // Small size for testing
   
        void destroyDictionary();   
        int getNextPrime(int number) const;
        bool isPrime(int number) const;
   
    public:   
        HashTable();
        HashTable(int maxNumberOfEntries);
        HashTable(const HashTable<KeyType, ValueType>& dict);
        virtual ~HashTable();
   
        bool isEmpty() const;   
        int getNumberOfItems() const;   
        void clear();   
        bool add(const KeyType& itemKey, const ValueType& newItem);   
        bool remove(const KeyType& itemKey);
        ValueType getItem(const KeyType& itemKey) const  throw (NotFoundException);   
        bool contains(const KeyType& itemKey) const;   
        void traverse(void visit(ValueType)) const;   
}; // end HashTable

#include "HashTable.cpp"
#endif
