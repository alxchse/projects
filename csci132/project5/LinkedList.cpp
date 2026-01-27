//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Implementation file for the class LinkedList.
  @file LinkedList.cpp */

#include "LinkedList.h"
#include <stdexcept>
#include <cassert>
#include <sstream>

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& original) : headPtr(nullptr), itemCount(0)
{
  *this = original; // invoke assignment-operator to do the actual copy
}

template<class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& original)
{
  if (this != &original) {
    clear(); // Clear any existing nodes in this list's chain.
    if (original->headPtr != nullptr) {
      // Copy item from first node in original's chain.
      headPtr = new Node<ItemType>(original->headPtr->getItem());
      itemCount++;
      // Copy items from remaining nodes in original's chain.
      Node<ItemType>* more = original->headPtr->getNext();
      Node<ItemType>* last = headPtr;
      while (more != nullptr) {
        ItemType another = new Node<ItemType>(more->getItem());
        last->setNext(another);
        last = another;
        more = more->getNext();
        itemCount++;
      }
    }
  } 
  return *this;
}  // end assignment operator

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
  clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
  return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
  return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
  if (newPosition < 1 || newPosition > itemCount + 1)
    return false;

  // Create a new node containing the new entry 
  Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);  

  // Attach new node to chain
  if (newPosition == 1) {
    // Insert new node at beginning of chain
    newNodePtr->setNext(headPtr); 
    headPtr = newNodePtr;
  } else {
    // Find node that will be before new node
    Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);

    // Insert new node after node to which prevPtr points
    newNodePtr->setNext(prevPtr->getNext()); 
    prevPtr->setNext(newNodePtr);
  }

  itemCount++;
  return true;
}  // end insert

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
  if (position < 1 || position > itemCount)
    return false;

  if (position == 1) {
    // Unlink and delete the first node in the chain
    Node<ItemType>* old = headPtr;
    headPtr = headPtr->getNext();
    delete old;
  } else {
    // Find node that is before the one to delete
    Node<ItemType>* prevPtr = getNodeAt(position - 1);

    // Get pointer to the node to be deleted
    Node<ItemType>* old = prevPtr->getNext();

    // Unlink and delete that node
    prevPtr->setNext(old->getNext());
    delete old;
  }

  itemCount--;
  return true;
}  // end remove

template<class ItemType>
void LinkedList<ItemType>::clear()
{
  while (!isEmpty())
    remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
{
  bool ableToGet = (position >= 1) && (position <= itemCount);
  if (ableToGet) {
    Node<ItemType>* nodePtr = getNodeAt(position);
    return nodePtr->getItem();
  } else {
    std::stringstream s;
    s << "LinkedList::getEntry(" << position << ") called on a list of length " << itemCount << ".";
    s << " This is an invalid position.";
    throw std::runtime_error(s.str());
  } 
}  // end getEntry

template<class ItemType>
ItemType LinkedList<ItemType>::replace(int position, const ItemType& newEntry)
{
  // Enforce precondition
  bool ableToSet = (position >= 1) && (position <= itemCount);
  if (ableToSet) {
    Node<ItemType>* nodePtr = getNodeAt(position);
    ItemType old = nodePtr->getItem();
    nodePtr->setItem(newEntry);
    return old;
  } else {
    std::stringstream s;
    s << "LinkedList::replace(" << position << ", ...) called on a list of length " << itemCount << ".";
    s << " This is an invalid position.";
    throw std::runtime_error(s.str());
  }
}  // end replace

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const {
    if((position < 1) || (position > itemCount)) {
        std::stringstream s;
        s << "LinkedList::getNodeAt(" << position << ", ...) called on a list of length " << itemCount << ".";
        s << " This is an invalid position.";
        throw std::runtime_error(s.str());
    }
    Node<ItemType>* current = headPtr;
    for (int skip = 1; skip < position; skip++)
        current = current->getNext();
    return current;
}

template<class ItemType>
bool LinkedList<ItemType>::removeEntry(const ItemType& anEntry) {
    return removeEntry(nullptr, headPtr, anEntry);
}

template<class ItemType>
bool LinkedList<ItemType>::removeEntry(Node<ItemType>* prev, Node<ItemType>* curr, const ItemType& anEntry) {
    
    if (curr == nullptr) {
      return false;
    }
    
    if (headPtr->getItem() == anEntry) {
      headPtr = headPtr->getNext();
      delete curr;
      itemCount--;
      return true;
    }

    if (curr->getNext() == nullptr) 
      return false;

    prev = curr;
    curr = curr->getNext();
    return removeEntry(prev, curr, anEntry);
}
