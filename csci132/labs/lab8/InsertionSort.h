/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Z. Fitzsimmons
 * File: InsertionSort.h
 * Purpose: Interface for a linked chain of Nodes mergesort routine.
 ***************************************************************************/

#ifndef INSERTIONSORT_H_
#define INSERTIONSORT_H_

#include "Node.h"

/* 
 * Sort an ArrayList using insertion sort.
 * Preconditions:
 *   list is a non-null pointer to an (unsorted) ArrayList
 * Postconditions:
 *   list is sorted in ascending order.
 */template<class ItemType>
void insertionSort(ArrayList<ItemType>* list);

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
void insertionSort(Node<ItemType>* &headPtr);

#include "InsertionSort.cpp"
#endif // INSERTIONSORT_H_
