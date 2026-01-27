// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  Fall 2020 - Zack Fitzsimmons - Removed smart pointers.

/** @file BinaryNode.cpp */

#include "BinaryNode.h"

template<class ItemType>
BinaryNode<ItemType>::BinaryNode()
  : item(nullptr), leftChildPtr(nullptr), rightChildPtr(nullptr) { }

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
  : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr) { }

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftPtr,
    BinaryNode<ItemType>* rightPtr)
  : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr) { } 

template<class ItemType>
  void BinaryNode<ItemType>::setItem(const ItemType& anItem) {
    item = anItem;
  }   // end setItem

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const {
  return item;
}   // end getItem

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const {
  return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType>* leftPtr) {
  leftChildPtr = leftPtr;
}   // end setLeftChildPtr

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType>* rightPtr) {
  rightChildPtr = rightPtr;
}   // end setRightChildPtr

template<class ItemType>
BinaryNode<ItemType>* BinaryNode<ItemType>::getLeftChildPtr() const {
  return leftChildPtr;
}   // end getLeftChildPtr		

template<class ItemType>
BinaryNode<ItemType>* BinaryNode<ItemType>::getRightChildPtr() const {
  return rightChildPtr;
}   // end getRightChildPtr		
