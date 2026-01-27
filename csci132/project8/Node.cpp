// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//   1 March 2021 - Z. Fitzsimmons - Added global count, for debugging.
//   4 March 2021 - K. Walsh - Added comments.

/** @file Node.cpp 
  Listing 4-2 */
#include "Node.h"
#include <iostream>

// Initialize count, a "static variable" within the Node class.
template<class ItemType>
int Node<ItemType>::count = 0;

template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
  count++;
  std::cout << "Nodes created! " << count << " nodes now exist." << std::endl;
} // end default constructor

template<class ItemType>
Node<ItemType>::~Node()
{
  count--;
  std::cout << "Node freed! " << count << " nodes now remain." << std::endl;
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
  count++;
  std::cout << "Nodes created! " << count << " nodes now exist." << std::endl;
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
  item(anItem), next(nextNodePtr)
{
  count++;
  std::cout << "Nodes created! " << count << " nodes now exist." << std::endl;
} // end constructor

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
  item = anItem;
} // end setItem

template<class ItemType>
ItemType Node<ItemType>::replaceItem(const ItemType& anItem)
{
  ItemType old = item;
  item = anItem;
  return old;
} // end replaceItem

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
  next = nextNodePtr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
  return item;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
  return next;
} // end getNext

