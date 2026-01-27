/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 10
 * Instructor: Z. Fitzsimmons
 * File: MergeSort.cpp
 * Purpose: Implementation mergesort for arrays.
 ***************************************************************************/
#include "MergeSort.h"
   
template<class ItemType>
void mergeSort(ItemType arr[], int first, int last) {
    if (first >= last) {
        return;
    } else {
        int mid = (first+last)/2;

        mergeSort(arr, first, mid);
        mergeSort(arr, mid+1, last);

        merge(arr, first, mid, last);
    }
}

// Merges two sorted array segments arr[first..mid] and arr[mid+1..last] into
// one sorted segment arr[first...last].
// Preconditions:
//   Parameters first, mid, and last are all valid array indices into the array,
//   with first <= mid <= last.
//   The subarray arr[first..mid] is already sorted in ascending order.
//   The subarray arr[mid+1..last] is already sorted in ascending order.
// Postconditions:
//   The subarray arr[first..last] is now sorted in ascending order.
template<class ItemType>
void merge(ItemType arr[], int first, int mid, int last) {
  // cout << "Merging arr[" << first << ".." << mid << "] with arr[" << (mid+1) << ".." << last << "]\n";
  int n = last - first + 1;
  ItemType *temp = new ItemType[n];  // a temporary array used during merging

  // Initialize the local indices to indicate the subarrays
  int first1 = first;            // Beginning of first subarray
  int last1 = mid;               // End of first subarray
  int first2 = mid + 1;          // Beginning of second subarray
  int last2 = last;              // End of second subarray

  // While both subarrays are not empty, copy the
  // smaller item into the temporary array
  int index = 0;                 // Next available location in temp
  while ((first1 <= last1) && (first2 <= last2)) {
    if (arr[first1] <= arr[first2]) {
      temp[index] = arr[first1];
      first1++;
    } else {
      temp[index] = arr[first2];
      first2++;
    }
    index++;
  }

  // Copy any remaining values from first subarray
  while (first1 <= last1) {
    temp[index] = arr[first1];
    first1++;
    index++;
  }

  // Copy any remaining values from second subarray
  while (first2 <= last2) {
    temp[index] = arr[first2];
    first2++;
    index++;
  }

  // Copy result back into original array
  for (int i = 0; i < n; i++)
    arr[first+i] = temp[i];

  delete[] temp;
}  // end merge
