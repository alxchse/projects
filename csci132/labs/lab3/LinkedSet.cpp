// File: LinkedSet.h
// Description: Specification for the LinkedSet data type
// Author: K. Walsh
// Class: CSCI 132
// Date: 25 July 2020

#include "LinkedSet.h"
#include <cassert>
#include <cstdlib> // for rand()

template<class ItemType>
LinkedSet<ItemType>::LinkedSet() : head(nullptr)
{
}  // end default constructor
    
template<class ItemType>
LinkedSet<ItemType>::LinkedSet(const LinkedSet<ItemType>& original)
{
   // Point to nodes in original chain
   Node<ItemType>* origChainPtr = original.head;
   
   if (origChainPtr == nullptr)
      head = nullptr;  // Original set is empty
   else
   {
      // Copy first node
      head = new Node<ItemType>();
      head->setItem(origChainPtr->getItem());
      
      // Point to first node in new chain
      Node<ItemType>* newChainPtr = head;
      
      // Advance original-chain pointer
      origChainPtr = origChainPtr->getNext();
      
      // Copy remaining nodes
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
         
         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);
         
         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();
         
         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(nullptr);           // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedSet<ItemType>::~LinkedSet()
{
	clear();
}  // end destructor

template<class ItemType>
int LinkedSet<ItemType>::size() const
{
	int count = 0;
  Node<ItemType>* p = head;
  while (p != nullptr)
  {
    count++;
    p = p->getNext();
  }
  return count;
}  // end size

template<class ItemType>
bool LinkedSet<ItemType>::isEmpty() const
{
	return (head == nullptr);
}  // end isEmpty

template<class ItemType>
bool LinkedSet<ItemType>::add(const ItemType &anItem)
{
  bool wasPresent = contains(anItem);
  if (!wasPresent)
    head = new Node<ItemType>(anItem, head);
  return !wasPresent;
}  // end add

template<class ItemType>
bool LinkedSet<ItemType>::remove(const ItemType& anItem)
{
  if (head == nullptr)
  {
    return false; // empty, so nothing to remove
  }
  else if (head != nullptr && head->getItem() == anItem) {
    Node<ItemType>* oldHead = head;
    head = head->getNext();
    delete oldHead;
    return true; // item was at head, and we removed it
  }
  else
  {
    // search for the item somewhere beyond head of linked list
    Node<ItemType>* prev = head;
    Node<ItemType>* cur = head->getNext();
    bool found = false;
    while (cur != nullptr && !found)
    {
      found = (cur->getItem() == anItem);
      if (!found)
      {
        prev = cur;
        cur = cur->getNext();
      }
    }
    if (found)
    {
      Node<ItemType>* next = cur->getNext();
      prev->setNext(next);
      delete cur;
    }
    return found;
  }
}  // end remove

template<class ItemType>
void LinkedSet<ItemType>::clear()
{
  while (head != nullptr)
  {
    Node<ItemType>* oldHead = head;
    head = head->getNext();
    delete oldHead;
  }
}  // end clear

template<class ItemType>
bool LinkedSet<ItemType>::contains(const ItemType& anItem) const
{
  Node<ItemType>* cur = head;
  bool found = false;
  while (cur != nullptr && !found)
  {
    found = (cur->getItem() == anItem);
    cur = cur->getNext();
  }
  return found;
}  // end contains

template<class ItemType>
std::vector<ItemType> LinkedSet<ItemType>::toVector() const
{
  std::vector<ItemType> vec;
  Node<ItemType>* cur = head;
  while (cur != nullptr)
  {
    vec.push_back(cur->getItem());
    cur = cur->getNext();
  }
  return vec;
}  // end toVector

template<class ItemType>
ItemType LinkedSet<ItemType>::get(int i) const
{
  assert(0 <= i && i < size());

	int pos = 0;
  Node<ItemType>* p = head;
  while (pos != i)
  {
    pos++;
    p = p->getNext();
  }
  return p->getItem();
}  // end get
  
template<class ItemType>
ItemType LinkedSet<ItemType>::pickRandom() const
{
  int i = rand() % size();
  return get(i);
}
