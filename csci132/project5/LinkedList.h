// Created by Frank M. Carrano and Timothy M. Henry.  // Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//   18 April 2021 - K. Walsh - Fixed comments, cleaned up style issues.
//   19 April 2021 - K. Walsh - Added copy constructor and assignment operator.
//   October 2021 - Z. Fitzsimmons - Updated the class for to be used for the list functions project..

/** ADT list: Link-based implementation.
  Listing 9-2.
  @file LinkedList.h */

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include "ListInterface.h"
#include "Node.h"

template<class ItemType>
class LinkedList : public ListInterface<ItemType> {
    private:
        Node<ItemType>* headPtr; // Pointer to first node in chain
        int itemCount;           // Current count of list items

        // Locates node at specified position in chain.
        // Precondition:
        //   position is between 1 and count, inclusive.
        Node<ItemType>* getNodeAt(int position) const;
        bool removeEntry(Node<ItemType>* prevPtr, Node<ItemType>* curPtr, const ItemType& anEntry);

    public:
        // Default constructor
        LinkedList();

        // Copy-constructor
        LinkedList(const LinkedList<ItemType>& original);

        // Assignment-operator
        LinkedList<ItemType>& operator=(const LinkedList<ItemType>& original);

        // Destructor
        virtual ~LinkedList();

        // Methods from ListInterface
        bool isEmpty() const;
        int getLength() const;
        void clear();
        ItemType getEntry(int position) const;
        ItemType replace(int position, const ItemType& newEntry);
        bool insert(int newPosition, const ItemType& newEntry);
        bool remove(int position);
        bool removeEntry(const ItemType& anEntry);
}; // end LinkedList

#include "LinkedList.cpp"
#endif 
