/*******************************************************************
 * Date: Spring 2022
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Z. Fitzsimmons
 * File: InsertionSort.cpp
 * Purpose: Implementation for a linked chain of Nodes insertionsort routine.
 ***************************************************************************/

#include "InsertionSort.h"
#include <cassert>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

/* 
 * Sort an ArrayList using insertion sort.
 * Preconditions:
 *   list is a non-null pointer to an (unsorted) ArrayList
 * Postconditions:
 *   list is sorted in ascending order.
 */
template<class ItemType>
void insertionSort(ArrayList<ItemType>* list) {
    for (int i = 2; i <= list->getLength(); i++) {
        ItemType nextItem = list->getEntry(i);
        int loc = i;
        while ((loc > 1) && (list->getEntry(loc-1) > nextItem)) {
            list->replace(loc, list->getEntry(loc-1));
            loc--;
        }
        list->replace(loc, nextItem);
    }
}

/* Sort a linked chain of Nodes using insertion sort. This sorts the
 * entire chain only rearranging the Node pointers without copying
 * any data values.
 * Preconditions:
 *   headPtr is either nullptr, or list points to some Node in an unsorted chain
 *   of values eventually terminating in a nullptr.
 * Postconditions:
 *   If headPtr was nullptr, then it remains nullptr.
 *   Otherwise, list now points to the smallest of the nodes in the original
 *   chain, and all other nodes have been rearranged into sorted order.
 */
template<class ItemType>
void insertionSort(Node<ItemType>* &headPtr) {
    Node<ItemType>* firstUnsorted;
    Node<ItemType>* lastSorted;
    Node<ItemType>* prev;
    Node<ItemType>* curr;

    if (headPtr != nullptr) {
      // lastSorted points to the end of the sorted region
      lastSorted = headPtr; 
      
      // while lastSorted does not point to the end of
      // the list
      while (lastSorted->getNext() != nullptr) {
        // firstUnsorted points to the beginning of the unsorted region
        firstUnsorted = lastSorted->getNext();
      
        // Check if the node pointed to by firstUnsorted should
        // be inserted into the beginning of the list. If so, insert
        // this node to the beginning of the list.
        if (firstUnsorted->getItem() <= headPtr->getItem()) {
            lastSorted->setNext(firstUnsorted->getNext());
            firstUnsorted->setNext(headPtr);
            headPtr = firstUnsorted;
        // otherwise use curr and prev to insert the node into proper order
        } else {
            curr = headPtr->getNext();
            prev = headPtr;
            // while the item in current is bigger than the rest of the list,
            // iterate until we find the proper spot
            while (curr->getItem() < firstUnsorted->getItem()) {
                prev = curr;
                curr = curr->getNext();
            }
            // if the item is the biggest in the list, just add to the end and 
            // move lastSorted up to the end
            if (firstUnsorted == curr) {
                lastSorted = lastSorted->getNext();
            // otherwise move around pointers to insert node into the 
            // correct positions
            } else {
                lastSorted->setNext(lastSorted->getNext()->getNext());
                prev->setNext(firstUnsorted);
                firstUnsorted->setNext(curr);
            }
        } 
      } 
    }
}

