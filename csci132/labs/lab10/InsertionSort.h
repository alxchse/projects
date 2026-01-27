/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 10
 * Instructor: Z. Fitzsimmons
 * File: InsertionSort.h
 * Purpose: Interface for insertion sort for arrays.
 ***************************************************************************/

#ifndef INSERTIONSORT_H_
#define INSERTIONSORT_H_

/* 
 * Sort an array using insertion sort.
 * Preconditions:
 *   arr is an (unsorted) array of length n
 * Postconditions:
 *   arr is sorted in ascending order.
 */template<class ItemType>
void insertionSort(ItemType arr[], int n);

#include "InsertionSort.cpp"
#endif // INSERTIONSORT_H_
