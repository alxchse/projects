// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  28 April 2021 - K. Walsh - Fix style, remove exceptions.
//  December 2021 - Z. Fitzsimmons - Minor updates to the class

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryNodeTree.h"

// A BinarySearchTree inherits from BinaryNodeTree, differing from that class by
// ensuring all items are always maintained in sorted order. In other words,
// this class is overrides the behavior of BinaryNodeTree to ensure:
//  - Either the tree is empty,
//  - Or, the left subtree contains only values strictly less than the value
//    at the root node, and the right subtree contains only values strictly
//    greater than to the value at the root node.
//  - And both left and right subtrees are also binary search trees, i.e., this
//    is a recursive definition that applies to all nodes in the tree.
// Note: Duplicate values are not allowed.
// Note: This implementation does not automatically to balance the tree (so it
//   is not a "Balanced Binary Search Tree", merely a "Binary Search Tree").
template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType> {
  protected:

    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Helper methods for the public methods.
    //------------------------------------------------------------
    virtual BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* subTreePtr,
         const ItemType& target) const override; // override parent class helper

    virtual BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
        const ItemType& target, bool& success) override; // override parent class helper

    // Given a pointer to a non-null BST subtree whose root node is considered
    // vacant, fix up the subtree and return a pointer to new root node of the
    // repaired subtree. If the root was only remaining node, it will be deleted
    // and nullptr will be returned instead.
    virtual BinaryNode<ItemType>* removeBSTNode(BinaryNode<ItemType>* nodePtr);

    // Given a pointer to a non-null BST subtree, find the smallest value in the
    // tree, remove that node, and return a pointer to the repaired tree. The
    // deleted node's value is also returned in the successorValue reference
    // parameter.
    virtual BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
        ItemType& successorValue);

    // Helper for filling an array. This copies all items from the given subtree
    // into the array, starting at position arr[pos]. It returns a count of how
    // many items were copied. If the subtree is empty, the no values are copied
    // and zero is returned.
    // Precondition:
    //   The array must be large enough to hold all the items in this subtree.
    //   That is, arr[pos]... ar[pos+n-1] must all be valid array indexes,
    //   where n is the size of the given subtree.
    virtual int fillArrayHelper(BinaryNode<ItemType>* subtreePtr, ItemType arr[], int pos);

  public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------
    BinarySearchTree(); // Default constructor.
    BinarySearchTree(const BinarySearchTree<ItemType>& original); // Copy-constructor.
    BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& original); // Assignment-operator.

    //------------------------------------------------------------
    // Overridden Methods from BinaryNodeTree Section.
    //------------------------------------------------------------
    bool add(const ItemType& newData) override; // overrides parent class method

    //------------------------------------------------------------
    // Useful methods not present in BinaryTreeInterface.
    //------------------------------------------------------------

    // Traverse the tree in sorted order, placing each item into the given
    // array, starting at arr[0]. This returns a count of how many items were
    // copied.
    // Precondition:
    //   The array must be large enough to hold all the items in the tree. If
    //   the array is too large, the extra array positions are ignored.
    virtual int fillArray(ItemType arr[]);
}; // end BinarySearchTree

#include "BinarySearchTree.cpp"

#endif
