// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  Fall 2020 - Zack Fitzsimmons - removed smart pointers
//  20 April 2021 - K. Walsh - fix style and added comments,
//     removed non-standard exceptions, and removed/modified
//     a few methods that were defined in the textbook.
//  November 2021 - Z. Fitzsimmons updated for Fall 2021 lab

/** @file BinaryNodeTree.cpp */

#include "BinaryNodeTree.h" 
#include "BinaryNode.h" 
#include "ArrayQueue.h"
#include <iostream>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() {
  rootPtr = nullptr;
}  // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& original) {
  rootPtr = copyHelper(original.rootPtr);
}  // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType>& original) {
  if (this != &original) {
    destroyHelper(rootPtr); // note: this does not modify rootPtr
    rootPtr = nullptr;
    rootPtr = copyHelper(original.rootPtr);
  }
  return *this;
}  // end assignment operator

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree() {
  destroyHelper(rootPtr); // note: this does not modify rootPtr
  rootPtr = nullptr;
}  // end destructor

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const {
  return rootPtr == nullptr;
}  // end isEmpty

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const {
  return getHeightHelper(rootPtr);
}  // end getHeight

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const {
  return getNumberOfNodesHelper(rootPtr);
}  // end getNumberOfNodes

template<class ItemType>
void BinaryNodeTree<ItemType>::clear() {
  destroyHelper(rootPtr); // note: this does not modify rootPtr
  rootPtr = nullptr;
}  // end clear

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData) {
  auto newNodePtr = new BinaryNode<ItemType>(newData);
  if (rootPtr == nullptr) 
    rootPtr = newNodePtr;
  else
    balancedAdd(rootPtr, newNodePtr);
  return true;
}  // end add

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target) {
  bool success = false;
  rootPtr = removeValue(rootPtr, target, success);
  return success;
}  // end remove

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const {
  auto nodePtr = findNode(rootPtr, anEntry);
  return nodePtr != nullptr;
}  // end contains

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType)) const {
  preorderHelper(visit, rootPtr);
}  // end preorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType)) const {
  inorderHelper(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType)) const {
  postorderHelper(visit, rootPtr);
}  // end postorderTraverse

//////////////////////////////////////////////////////////////
//      Useful methods not present in BinaryTreeInterface
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::levelorderTraverse(void visit(ItemType)) const {
  if (rootPtr == nullptr)
    return;
  ArrayQueue<BinaryNode<ItemType>*> orderQueue;
  orderQueue.enqueue(rootPtr);
  while (!orderQueue.isEmpty()) {
    auto val = orderQueue.peekFront();
    orderQueue.dequeue();
    visit(val->getItem());
    if (val->getLeftChildPtr() != nullptr)
      orderQueue.enqueue(val->getLeftChildPtr());
    if (val->getRightChildPtr() != nullptr)
      orderQueue.enqueue(val->getRightChildPtr());
  }
}

template<class ItemType>
template<class OtherItemType>
bool BinaryNodeTree<ItemType>::isSameShape(const BinaryNodeTree<OtherItemType>& other) const {
  return isSameShapeHelper(rootPtr, other.rootPtr);
}

template<class ItemType>
template<class OtherItemType>
bool BinaryNodeTree<ItemType>::isSameShapeHelper(const BinaryNode<ItemType>* subtree1,
    const BinaryNode<OtherItemType>* subtree2) const {
    if ((subtree1 == nullptr) && (subtree2 == nullptr)) {
      return true;
    } else if ((subtree1 == nullptr) && (subtree2 != nullptr)) {
      return false;
    } else if ((subtree1 != nullptr) && (subtree2 == nullptr)) {
      return false;
    } else { 
      return isSameShapeHelper(subtree1->getLeftChildPtr(), subtree2->getLeftChildPtr()) &&
      isSameShapeHelper(subtree1->getRightChildPtr(), subtree2->getRightChildPtr());
  }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::prettyPrint() const {
  // Example:
  //  A
  //  |--B
  //  |  |--E
  //  |  '--F
  //  |     |--J
  //  |     |  |--
  //  |     |  '--L
  //  |     `--K
  //  '--C
  //     |--G
  //     '--H
 
  if (rootPtr == nullptr) {
    cout << "[empty tree]\n";
    return;
  }
  cout << "  " << rootPtr->getItem() << endl;
  auto r = rootPtr->getRightChildPtr();
  auto l = rootPtr->getLeftChildPtr();
  prettyPrintHelper("  |--", "  |  ", r);
  prettyPrintHelper("  '--", "     ", l);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::prettyPrintHelper(
    string firstLinePrefix, string childLinePrefix, const BinaryNode<ItemType>* subtree) const {
  if (subtree == nullptr) {
    cout << firstLinePrefix << endl;
  } else {
    cout << firstLinePrefix << subtree->getItem() << endl;
    auto r = subtree->getRightChildPtr();
    auto l = subtree->getLeftChildPtr();
    if (l == nullptr && r == nullptr)
      return;
    prettyPrintHelper(childLinePrefix+"|--", childLinePrefix+"|  ", r);
    prettyPrintHelper(childLinePrefix+"'--", childLinePrefix+"   ", l);
  }
}

//////////////////////////////////////////////////////////////
//      Protected Helper Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(const BinaryNode<ItemType>* subTreePtr) const {
  if (subTreePtr == nullptr)
    return 0;
  int leftHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
  int rightHeight = getHeightHelper(subTreePtr->getRightChildPtr());
  return 1 + max(leftHeight, rightHeight);
}  // end getHeightHelper

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(const BinaryNode<ItemType>* subTreePtr) const {
  if (subTreePtr == nullptr)
    return 0;
  int leftSize = getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
  int rightSize = getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
  return 1 + leftSize + rightSize;
}  // end getNumberOfNodesHelper

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr,
    const ItemType& target) const {
  if (subTreePtr == nullptr)
    return nullptr;

  if (subTreePtr->getItem() == target) 
    return subTreePtr;

  auto ans = findNode(subTreePtr->getLeftChildPtr(), target);
  if (ans != nullptr)
    return ans;
  ans = findNode(subTreePtr->getRightChildPtr(), target);
  return ans;
}  // end findNode

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyHelper(BinaryNode<ItemType>* oldSubTreePtr) const {
  if (oldSubTreePtr == nullptr)
    return nullptr;
  auto newNode = new BinaryNode<ItemType>(oldSubTreePtr->getItem());
  newNode->setLeftChildPtr(copyHelper(oldSubTreePtr->getLeftChildPtr()));
  newNode->setRightChildPtr(copyHelper(oldSubTreePtr->getRightChildPtr()));
  return newNode;
}  // end copyHelper

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyHelper(BinaryNode<ItemType>* subTreePtr) {
  if (subTreePtr == nullptr)
    return;
  // First, recursively destroy all descendants of this node.
  destroyHelper(subTreePtr->getLeftChildPtr());
  destroyHelper(subTreePtr->getRightChildPtr());
  // Next, delete the node itself
  delete subTreePtr;
}  // end destroyHelper

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderHelper(void visit(ItemType),
    const BinaryNode<ItemType>* subTreePtr) const {
  if (subTreePtr != nullptr) {
    visit(subTreePtr->getItem());
    preorderHelper(visit, subTreePtr->getLeftChildPtr());
    preorderHelper(visit, subTreePtr->getRightChildPtr());
  }
}  // end preorderHelper

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderHelper(void visit(ItemType),
    const BinaryNode<ItemType>* subTreePtr) const {
  if (subTreePtr != nullptr) {
    inorderHelper(visit, subTreePtr->getLeftChildPtr());
    visit(subTreePtr->getItem());
    inorderHelper(visit, subTreePtr->getRightChildPtr());
  } 
}  // end inorderHelper

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderHelper(void visit(ItemType),
    const BinaryNode<ItemType>* subTreePtr) const {
  if (subTreePtr != nullptr) {
    postorderHelper(visit, subTreePtr->getLeftChildPtr());
    postorderHelper(visit, subTreePtr->getRightChildPtr());
    visit(subTreePtr->getItem());
  }   
}  // end postorderHelper

template<class ItemType>
void BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr,
    BinaryNode<ItemType>* newNodePtr) {
  auto leftPtr = subTreePtr->getLeftChildPtr();
  if (leftPtr == nullptr) {
    subTreePtr->setLeftChildPtr(newNodePtr);
    return;
  }
  auto rightPtr = subTreePtr->getRightChildPtr();
  if (rightPtr == nullptr) {
    subTreePtr->setRightChildPtr(newNodePtr);
    return;
  }
  if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
    balancedAdd(rightPtr , newNodePtr);
  else
    balancedAdd(leftPtr, newNodePtr);
}  // end balancedAdd

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeValue(
    BinaryNode<ItemType>* subTreePtr,
    const ItemType& target, bool& success) {

  if(subTreePtr == nullptr) { // target not found, leave subtree alone
    success = false;
    return subTreePtr;
  }

  if (subTreePtr->getItem() == target) { // found it
    // The root of this subtree should now be considered vacant. Time to repair
    // the subtree by moving values up (or deleting it entirely, if it is a
    // leaf).
    subTreePtr = moveValuesUpTree(subTreePtr);
    success = true;
    return subTreePtr;
  } else {
    // The target value might appear in one of the child nodes. Try the left.
    auto repairedChild = removeValue(subTreePtr->getLeftChildPtr(), target, success);
    subTreePtr->setLeftChildPtr(repairedChild);
    if (!success) {
      // No success yet. Try the right.
      repairedChild = removeValue(subTreePtr->getRightChildPtr(), target, success);
      subTreePtr->setRightChildPtr(repairedChild);
    }
    // The root of this subtree wasn't modified, so just return it.
    return subTreePtr;
  }
}  // end removeValue

// Copies values up the tree to overwrite value in current node until
// a leaf is reached; the leaf is then removed, since its value is stored in the parent.
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::moveValuesUpTree(BinaryNode<ItemType>* subTreePtr) {
  auto leftPtr = subTreePtr->getLeftChildPtr();
  auto rightPtr = subTreePtr->getRightChildPtr();
  
  if(subTreePtr->isLeaf() == true){
    delete subTreePtr;
    subTreePtr = nullptr;
    return nullptr;
  } 
  int heightL = getHeightHelper(leftPtr);
  int heightR = getHeightHelper(rightPtr);
  if(heightL >= heightR){
    subTreePtr->setItem(leftPtr->getItem());
    subTreePtr->setLeftChildPtr(moveValuesUpTree(leftPtr));
  } else {
    subTreePtr->setItem(rightPtr->getItem());
    subTreePtr->setRightChildPtr(moveValuesUpTree(rightPtr));
  }
  return subTreePtr;
}

