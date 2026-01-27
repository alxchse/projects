// File Name: LinkedDeque.h
// Author: Zack Fitzsimmons
// Course: CSCI 132
// Date: Spring 2021
// Purpose: Implementation of a Linked Deque class


#include "LinkedDeque.h"  

template<class ItemType>
LinkedDeque<ItemType>::LinkedDeque()
{
  frontPtr = nullptr;
  backPtr = nullptr;
}  // end default constructor

template<class ItemType>
LinkedDeque<ItemType>::LinkedDeque(const LinkedDeque<ItemType>& original) {
  // Initialize the chain to empty, to start.
  frontPtr = nullptr;
  backPtr = nullptr;

  // Start with a pointer to original deque's first node.
  Node<ItemType>* old = original.frontPtr;

  // If the original is empty, we have nothing more to do.
  if (old == nullptr)
    return;

  // Make our first new first node, with same item as the original's first item,
  // and null for the next pointer (for the moment). Our front and back both
  // point to this new node.
  frontPtr = new Node<ItemType>(old->getItem(), nullptr);
  backPtr = frontPtr;

  // Advance original chain pointer to the next node.
  old = old->getNext(); 
  while (old != nullptr) {
    // Make another new node, with an item from original chain.
    Node<ItemType>* toAdd = new Node<ItemType>(old->getItem(), nullptr);

    // Link it into the back of our chain, and adjust backPtr accordingly.
    backPtr->setNext(toAdd);
    backPtr = toAdd;

    // Advance original chain pointer to the next node.
    old = old->getNext();
  }  // end while. there are no more nodes in the original chain
}


template<class ItemType>
LinkedDeque<ItemType>::~LinkedDeque()
{
  while (!isEmpty())
    dequeueFront();
}  // end destructor

template<class ItemType>
bool LinkedDeque<ItemType>::isEmpty() const
{
  return backPtr == nullptr;
}  // end isEmpty

template<class ItemType>
bool LinkedDeque<ItemType>::isFull() const
{
  return false;
}  // end isFull

template<class ItemType>
bool LinkedDeque<ItemType>::enqueueBack(const ItemType& newEntry)
{
  Node<ItemType>* toAdd = new Node<ItemType>(newEntry, nullptr);

  // Insert the new node
  if (isEmpty()) {
    // Was empty, so it becomes our only node.
    frontPtr = toAdd;
    backPtr = toAdd;
  } else {
    // Not empty, so link it into the back of our chain.
    backPtr->setNext(toAdd);
    backPtr = toAdd;
  }

  return true;
}  // end enqueueBack

template<class ItemType>
ItemType LinkedDeque<ItemType>::peekFront() const
{
  // Check precondition, just to be safe.
  if (isEmpty())
    throw PrecondViolatedExcept("peekFront() called with empty deque");

  // ArrayDeque is not empty, so return the front entry
  return frontPtr->getItem();
} // end peekFront

template<class ItemType>
bool LinkedDeque<ItemType>::dequeueFront() {
  if (isEmpty())
    return false;

  // Deque is not empty, so unlink and delete front node.
  Node<ItemType>* toDelete = frontPtr;
  if (frontPtr == backPtr) {
    // Special case: only one node in the chain
    backPtr = nullptr;
    frontPtr = nullptr;
  } else {
    // Ordinary case: multiple nodes in chain, move front to second one
    frontPtr = frontPtr->getNext();
  }
  delete toDelete;
  return true;
}  // end dequeueFront

template<class ItemType>
bool LinkedDeque<ItemType>::enqueueFront(const ItemType& newEntry)
{
  Node<ItemType>* toAdd = new Node<ItemType>(newEntry, nullptr);

  // Insert the new node
  if (isEmpty()) {
    // Was empty, so it becomes our only node.
    frontPtr = toAdd;
    backPtr = toAdd;
  } else {
    // Not empty, so link it into the back of our chain.
    frontPtr->setNext(toAdd);
    frontPtr = toAdd;
  }
  return true;
}  // end enqueueFront

template<class ItemType>
bool LinkedDeque<ItemType>::dequeueBack() {
  if (isEmpty())
    return false;

  // Deque is not empty, so unlink and delete front node.
  Node<ItemType>* toDelete = backPtr;
  Node<ItemType>* pUlt = frontPtr;

  if (frontPtr == backPtr) {
    // Special case: only one node in the chain
    backPtr = nullptr;
    frontPtr = nullptr;
  } else {
    // Ordinary case: multiple nodes in chain, move front to second one
    while (!(pUlt->getNext() == backPtr)) {
      pUlt = pUlt->getNext();
    }
    backPtr = pUlt;
  }
  delete toDelete;
  return true;
}  // end dequeueBack

template<class ItemType>
ItemType LinkedDeque<ItemType>::peekBack() const
{
  // Check precondition, just to be safe.
  if (isEmpty())
    throw PrecondViolatedExcept("peekBack() called with empty deque");

  // ArrayDeque is not empty, so return the front entry
  return backPtr->getItem();
}  // end peekBack

