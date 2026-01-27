/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Z. Fitzsimmons
 * File: InsertionSort.cpp
 * Purpose: Implementation of insertion sort for arrays.
 ***************************************************************************/

#include "InsertionSort.h"
#include <cassert>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

/* 
 * Sort an array using insertion sort.
 * Preconditions:
 *   arr is an (unsorted) array of length n
 * Postconditions:
 *   arr is sorted in ascending order.
 */
template<class ItemType>
void insertionSort(ItemType arr[], int n) {
    for (int unsorted = 1; unsorted < n; unsorted++) {
        ItemType nextItem = arr[unsorted];
        int loc = unsorted;
        while ((loc > 0) && arr[loc - 1] > nextItem) {
            arr[loc] = arr[loc-1];
            loc--;
        }
        arr[loc] = nextItem;
    }
}
