// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  28 April 2021 - K. Walsh - Fix style, remove exceptions.
//  December 2021 - Z. Fitzsimmons - Minor updates to the class.

#include "BinarySearchTree.h" 

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
  : BinaryNodeTree<ItemType>() // this calls the parent class constructor
{ 
}  // end default constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& original) 
  : BinaryNodeTree<ItemType>(original) // the calls the parent class copy constructor
{
}  // end copy constructor

template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& original) {
  BinaryNodeTree<ItemType>::operator=(original); // call parent class assignment operator
  return *this;
}  // end assignment operator

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData) {
  // We could do this recursively, but let's do iterative, just for variety.
  // Note that this method assumes that newData does not appear in the tree.
  auto newNodePtr = new BinaryNode<ItemType>(newData);
  if (BinaryNodeTree<ItemType>::rootPtr == nullptr) {
    BinaryNodeTree<ItemType>::rootPtr = newNodePtr;
    return true;
  }
  auto p = BinaryNodeTree<ItemType>::rootPtr;
  while (true) {
    auto left = p->getLeftChildPtr();
    auto right = p->getRightChildPtr();
    if (newData < p->getItem()) {
      // New node goes somewhere to the left of p
      if (left == nullptr) {
        p->setLeftChildPtr(newNodePtr);
        return true;
      } else {
        p = left;
      }
    } else {
      // New node goes somewhere to the right of p
      if (right == nullptr) {
        p->setRightChildPtr(newNodePtr);
        return true;
      } else {
        p = right;
      }
    }
  }
}  // end add

// This method overrides the parent class helper, because we can more
// efficiently find a target item in a BST than in a regular binary tree.
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,
    const ItemType& target, bool& success) {

  if(subTreePtr == nullptr) { // target not found, leave subtree alone
    success = false;
    return subTreePtr;
  }

  if (subTreePtr->getItem() == target) { // found it
    // The root of this subtree should now be considered vacant. Time to repair
    // the subtree by moving items and/or deleting or rearranging nodes.
    subTreePtr = removeBSTNode(subTreePtr);
    success = true;
    return subTreePtr;
  } else {
    if (target < subTreePtr->getItem()) {
      // Search ONLY the left subtree
      auto repairedChild = removeValue(subTreePtr->getLeftChildPtr(), target, success);
      subTreePtr->setLeftChildPtr(repairedChild);
    } else {
      // Search ONLY the right subtree
      auto repairedChild = removeValue(subTreePtr->getRightChildPtr(), target, success);
      subTreePtr->setRightChildPtr(repairedChild);
    }
    return subTreePtr;
  }  // end if
}   // end removeValue

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeBSTNode(BinaryNode<ItemType>* nodePtr) {
  // Case 1) Node is a leaf - it is deleted, and nullptr is returned instead.
  // Case 2) Node has one child - node is deleted and grandparent adopts the one child
  // Case 3) Node has two children - replace node with the successor node (the
  //   right child subtree's left-most descendant). Because we can't easily use
  //   pass-by-reference for left/right child pointers given the
  //   BinaryNode<ItemType> implementation (where the two pointers are marked as
  //   private), we need a slightly different implementation that deletes the
  //   successor node and replaces this node's value with the one from the
  //   successor.
  if (nodePtr->isLeaf()) {
    delete nodePtr;
    return nullptr;
  }
  auto left = nodePtr->getLeftChildPtr();
  auto right = nodePtr->getRightChildPtr();
  if (left == nullptr) {  // Has rightChild only
    delete nodePtr;
    return right;
  } else if (right == nullptr) {  // Has left child only
    delete nodePtr;
    return left;
  } else {  // Has two children 
    ItemType successorValue;
    auto repairedChild = removeLeftmostNode(right, successorValue);
    nodePtr->setRightChildPtr(repairedChild);
    nodePtr->setItem(successorValue);
    return nodePtr;
  }  // end if
}   // end removeBSTNode

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
    ItemType& successorValue) {
  auto left = nodePtr->getLeftChildPtr();
  if (left == nullptr) {
    successorValue = nodePtr->getItem();
    return removeBSTNode(nodePtr);
  } else {
    auto repairedChild = removeLeftmostNode(left, successorValue);
    nodePtr->setLeftChildPtr(repairedChild);
    return nodePtr;
  }  // end if      
}  // end removeLeftmostNode

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr,
                                                    const ItemType& target) const {
  if (subTreePtr == nullptr)
    return nullptr;
  else if (target == subTreePtr->getItem())
    return subTreePtr;
  else if (target < subTreePtr->getItem())
    return findNode(subTreePtr->getLeftChildPtr(), target);
  else
    return findNode(subTreePtr->getRightChildPtr(), target);
}

// implement fillArray and fillArrayHelper
template<class ItemType>
int BinarySearchTree<ItemType>::fillArray(ItemType arr[]) {
  return fillArrayHelper(BinaryNodeTree<ItemType>::rootPtr, arr, 0);
}

    // Helper for filling an array. This copies all items from the given subtree
    // into the array, starting at position arr[pos]. It returns a count of how
    // many items were copied. If the subtree is empty, the no values are copied
    // and zero is returned.
    // Precondition:
    //   The array must be large enough to hold all the items in this subtree.
    //   That is, arr[pos]... ar[pos+n-1] must all be valid array indexes,
    //   where n is the size of the given subtree.
template<class ItemType>
int BinarySearchTree<ItemType>::fillArrayHelper(BinaryNode<ItemType> *subtreePtr,
    ItemType arr[], int pos) {
  if (subtreePtr == nullptr)
    return 0;
  
  int leftCount = fillArrayHelper(subtreePtr->getLeftChildPtr(), arr, pos);
  arr[pos + leftCount] = subtreePtr->getItem();
  int rightCount = fillArrayHelper(subtreePtr->getRightChildPtr(), arr, pos + leftCount + 1);

  return leftCount + rightCount + 1;
}
