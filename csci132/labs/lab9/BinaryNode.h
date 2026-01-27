// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  20 April 2021 - K. Walsh - fix style and added comments

/** A class of nodes for a link-based binary tree.
  Listing 16-2.
  @file BinaryNode.h */

#ifndef BINARY_NODE_
#define BINARY_NODE_

// A BinaryNode object holds a single data value (item) and two pointers to
// other nodes (leftChildPtr and rightChildPtr). Many BinaryNode objects can be
// linked together to form a binary tree, with one node acting as the root,
// pointing to left and right subtrees, which in turn point to nodes further
// down the tree. Note: an alternative use for BinaryNode objects is to build a
// doubly-linked chain, with each node's left and right pointers leading towards
// that node's left and right neighbors in the chain.
template<class ItemType>
class BinaryNode {   
  private:
    ItemType item;                       // Data value
    BinaryNode<ItemType>* leftChildPtr;  // Pointer to left child
    BinaryNode<ItemType>* rightChildPtr; // Pointer to right child

  public:
    // Default constructor
    BinaryNode();

    // Construct a node to hold the given data value
    BinaryNode(const ItemType& anItem);

    // Construct a node to hold the given data value, and pointing to two
    // other existing child nodes. If building a linked tree structure, the
    // given left and right nodes should either be null, or a leaf node, or
    // perhaps the root of some subtree (but they should not be internal
    // nodes in some other existing tree structure).
    BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftPtr,
        BinaryNode<ItemType>* rightPtr);

    // Change the data value in this node.
    void setItem(const ItemType& anItem);

    // Get a copy the data value stored in this node.
    ItemType getItem() const;

    // Check whether this node is childless.
    bool isLeaf() const;

    // Get a pointer to the left child of this node.
    BinaryNode<ItemType>* getLeftChildPtr() const;

    // Get a pointer to the left child of this node.
    BinaryNode<ItemType>* getRightChildPtr() const;

    // Set the left child pointer of this node.
    void setLeftChildPtr(BinaryNode<ItemType>* leftPtr);

    // Set the right child pointer of this node.
    void setRightChildPtr(BinaryNode<ItemType>* rightPtr);

}; // end BinaryNode

#include "BinaryNode.cpp"
#endif 
