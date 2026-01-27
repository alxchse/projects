/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 10
 * Instructor: Z. Fitzsimmons
 * File: TreeSort.h
 * Purpose: Interface for an implementation of tree sort for arrays.
 ***************************************************************************/

#ifndef TREESORT_H_
#define TREESORT_H_

/* Sort an array  using the treesort algorithm.
 *
 * Preconditions:
 *   arr is an (unsorted) array of length n
 *
 * Postconditions: arr is sorted in ascending order.
 */
template<class ItemType>
void treeSort(ItemType arr[], int n);

#include "TreeSort.cpp"
#endif // TREESORT_H_
