/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Z. Fitzsimmons
 * File: MergeSort.h
 * Purpose: Interface for an ArrayList mergesort routine.
 ***************************************************************************/

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include "ArrayList.h"
   
/* Sort an ArrayList  using the mergesort algorithm.
 *
 * Postconditions: list is sorterd in ascending order.
 *    
 * Sort a segment of an ArrayList using the mergesort algorithm. This sorts the
 * segment from list[first..last], inclusive, into ascending order.
 * Typically, first < last, meaning the segment has multiple items to be sorted.
 * If first == last, the segment only has a one item, so sorting has no effect.
 * If first > last, the segment is considered empty, and the function does nothing.
 *
 * Preconditions:
 *   list is a non-null pointer to an (unsorted) ArrayList
 *   If first <= last, then both first and last are valid positions within the
 *   arraylist, i.e. between 1 and list.size().
 * Postconditions:
 *   If first <= last, the segment list[first..last] is now sorted in ascending
 *   order, and any other items in the list are left unchanged.
 */
template<class ItemType>
void mergeSort(ArrayList<ItemType>* list, int first, int last);

#include "MergeSort.cpp"
#endif // MERGESORT_H_
