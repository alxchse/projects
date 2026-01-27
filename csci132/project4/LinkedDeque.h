// File Name: LinkedDeque.h
// Author: Zack Fitzsimmons
// Course: CSCI 132
// Date: Spring 2021
// Purpose: Specification of LinkedDeque class
// Revisions
//   4 March 2021 - K. Walsh - Updated as new project for spring 2021

#ifndef LINKED_DEQUE_
#define LINKED_DEQUE_

#include "DequeInterface.h"
#include "Node.h"
#include <string>

// The LinkedDeque class provides a link-based implementation of DequeInterface.
// Items are stored in a linked chain of Node objects. There is no maximum
// capacity, the chain will grow and shrink as needed.
template<class ItemType>
class LinkedDeque : public DequeInterface<ItemType>
{
  private:
    // Two pointers are maintained, one pointing to the Node at the front of the
    // linked chain, one pointing to the Node at the back. 
    Node<ItemType>* frontPtr;
    Node<ItemType>* backPtr;
    // Invariants:
    //   When the deque is empty, then frontPtr and backPtr are both null.
    //   Otherwise, frontPtr and backPtr are both non-null and point to
    //   the first and last nodes in a chain.

  public:

    // Default constructor creates an empty deque with a default capacity.
    LinkedDeque();

    // Copy-constructor creates an new deque that is a copy of an existing deque.
    LinkedDeque(const LinkedDeque<ItemType>& other);

    // Destructor frees all dyanmically allocated memory associated with the
    // deque.
    virtual ~LinkedDeque();

    // These next methods implement DequeInterface.
    bool isEmpty() const;
    bool isFull() const;
    bool dequeueFront();
    bool dequeueBack();
    bool enqueueFront(const ItemType &newEntry);
    bool enqueueBack(const ItemType &newEntry);
    ItemType peekFront() const;
    ItemType peekBack() const;
    
    // These friend functions are for testing and debugging.
    template <class ItemTypeB>
    friend bool sanityCheck(std::string name, LinkedDeque<ItemTypeB> *deque);
    template <class ItemTypeB>
    friend bool debugCompare(LinkedDeque<ItemTypeB>* a, LinkedDeque<ItemTypeB>* b);

};
#include "LinkedDeque.cpp"
#endif
