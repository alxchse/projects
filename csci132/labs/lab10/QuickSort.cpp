/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 10
 * Instructor: Z. Fitzsimmons
 * File: QuickSort.cpp
 * Purpose: Implementation of quicksort for arrays.
 ***************************************************************************/
#include <algorithm> // for std::swap
#include "QuickSort.h"


// Partition arr[first..last] and return the index of the pivot.
template<class ItemType>
int partition(ItemType arr[], int first, int last) {
  // Choose pivot as the last entry.
  int pivotIndex = (first+last)/2;

  // Reposition pivot so it is last in the array
  std::swap(arr[pivotIndex], arr[last]);
  pivotIndex = last;
  ItemType pivot = arr[pivotIndex];

  // Determine the regions S1 and S2
  int indexFromLeft = first;
  int indexFromRight = last-1;

  bool done = false;
  while (!done) {
    // Locate first entry on left that is >= pivot
    while (arr[indexFromLeft] < pivot)
      indexFromLeft = indexFromLeft + 1;

    // Locate first entry on right that is <= pivot
    while (indexFromRight > first && arr[indexFromRight] > pivot)
      indexFromRight = indexFromRight - 1;

    if (indexFromLeft < indexFromRight) {
      std::swap(arr[indexFromLeft], arr[indexFromRight]);
      indexFromLeft = indexFromLeft + 1;
      indexFromRight = indexFromRight - 1;
    } else {
      done = true;
    }
  }   // end while

  // Place pivot in proper position between S1 and S2, and mark its new location
  std::swap(arr[pivotIndex], arr[indexFromLeft]);
  pivotIndex = indexFromLeft;

  return pivotIndex;
}   // end partition

template<class ItemType>
void quickSort(ItemType arr[], int first, int last) {
  if (first < last) { 
    // Create the partition: S1 | Pivot | S2
    int pivotIndex = partition(arr, first, last);

    // Sort subarrays S1 and S2
    quickSort(arr, first, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, last);
  }
}  // end quickSort
