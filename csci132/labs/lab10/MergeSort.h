/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 10
 * Instructor: Z. Fitzsimmons
 * File: MergeSort.h
 * Purpose: Interface for mergesort for arrays.
 ***************************************************************************/

#ifndef MERGESORT_H_
#define MERGESORT_H_

/* Sort an array  using the mergesort algorithm.
 *
 * Postconditions: arr is sorterd in ascending order.
 *    
 * Sort a segment of an array using the mergesort algorithm. This sorts the
 * segment from arr[first..last], inclusive, into ascending order.
 * Typically, first < last, meaning the segment has multiple items to be sorted.
 * If first == last, the segment only has a one item, so sorting has no effect.
 * If first > last, the segment is considered empty, and the function does nothing.
 *
 * Preconditions:
 *   arr is an (unsorted) array
 *   If first <= last, then both first and last are valid positions within the
 *   array, i.e., between 0 and n-1.
 * Postconditions:
 *   If first <= last, the segment arr[first..last] is now sorted in ascending
 *   order, and any other items in the list are left unchanged.
 */
template<class ItemType>
void mergeSort(ItemType arr[], int first, int last);

#include "MergeSort.cpp"
#endif // MERGESORT_H_
