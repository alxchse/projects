// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//   1 March 2021 - Z. Fitzsimmons - Added global count, for debugging.
//   4 March 2021 - K. Walsh - Added comments.

/** @file Node.h 
    Listing 4-1 */
#ifndef NODE_
#define NODE_

template<class ItemType>
class Node
{
private:
   ItemType item;         // The data value stored in this node.
   Node<ItemType>* next;  // Pointer to the next node in a chain.

   
public:
   // Default constructor makes a node with an unspecified item value, and no
   // next pointer. It also increments the count of all Node objects.
   Node();

   // One-argument constructor makes a node with the given item value, and no
   // next pointer. It also increments the count of all Node objects.
   Node(const ItemType& anItem);

   // Two-argument constructor makes a node with the given item value, and the
   // given next pointer. It also increments the count of all Node objects.
   Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);

   // Destructor decrements the count of all Node objects.
   ~Node();

   // Change the value stored in this node.
   void setItem(const ItemType& anItem);

   // Change where this node's next pointer points to.
   void setNext(Node<ItemType>* nextNodePtr);

   // Access the value stored for this node.
   ItemType getItem() const;

   // Access the next-pointer for this node.
   Node<ItemType>* getNext() const;

   // For debugging purposes, we keep a public count of all nodes currently in
   // existence (both static variables, and Nodes created dynamically using the
   // keyword `new`). Note, the keyword `static` in the variable declaration
   // below means this variable is not actually part of Node objects. Instead,
   // there is a single `count` variable that all Node objects share.

   static int count; // Global count of all Node objects (for debugging).
};
#include "Node.cpp"
#endif
