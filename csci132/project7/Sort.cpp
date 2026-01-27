/*******************************************************************
 * Name: Alexandra Chase
 * amchas26@g.holycross.edu
 * Date: Spring 2023
 * Course: CSCI 132
 * Assignment: Project 7
 * Instructor: Fitzsimmons
 * Program: Sort.cpp
 * Purpose: Program to compare the clock time for different sorting algorithms.
 ***************************************************************************/

#include <iostream>
#include <cassert>
using namespace std;

// Returns true if arr[0...size-1] is sorted in ascending order.
bool sorted(const int arr[], int size) {
  for (int i = 1; i < size; i++) {
    if (arr[i] < arr[i-1]) {
      cout << "Error: positions " << (i-1) << " and " << i
           << " (values " << arr[i-1] << " and " << arr[i]
           << ") in the array are not properly sorted.\n";
      return false;
    }
  }
  return true;
}

// Find index of largest item in arr[0] through arr[size-1]
// Preconditions:
//   0...size-1 is a valid range in arr.
// Postconditions:
//   Returns the index of the largest element in arr[0...size-1].
int findIndexOfLargest(int arr[], int size) {
  int m = 0;	// m is the index of the largest found so far
  for (int i = 1; i < size; i++)
    if (arr[i] > arr[m])
      m = i;
  return m;
}

// Sorts the entries in the array arr into ascending order using
// the selection sort algorithm.
// Precondition:
//  Parameter n is the length of the array.
// Postcondtions:
//  If the subarray was not empty, then array arr is now sorted in ascending
//  order.
void SelectionSort(int arr[], int n) {
  for (int last = n - 1; last >= 1; last--) {
    int idxOfLargest = findIndexOfLargest(arr, last+1);
    std::swap(arr[idxOfLargest], arr[last]);
  }
}

// Merges two sorted array segments arr[first..mid] and arr[mid+1..last] into
// one sorted segment arr[first...last].
// Preconditions:
//   Parameters first, mid, and last are all valid array indices into the array,
//   with first <= mid <= last.
//   The subarray arr[first..mid] is already sorted in ascending order.
//   The subarray arr[mid+1..last] is already sorted in ascending order.
// Postcondtions:
//   The subarray arr[first..last] is now sorted in ascending order.
void merge(int arr[], int first, int mid, int last) {
  // cout << "Merging arr[" << first << ".." << mid << "] with arr[" << (mid+1) << ".." << last << "]\n";
  int n = last - first + 1;
  int *temp = new int[n];  // a temporary array used during merging

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

// Sorts the entries in the subarray arr[first..last] into ascending order using
// a recursive merge-sort algorithm.
// Precondition:
//   Parameters first and last are both valid array indices into the array,
//   with first <= last. Or, first > last to indicate an empty subarray.
// Postcondtions:
//   If the subarray was not empty, then subarray arr[first..last] is now sorted
//   in ascending order.
void MergeSort(int arr[], int first, int last) {
  if (first < last) {
    
    // Sort each half
    int mid = (first + last)/2; // Index of approximate midpoint
    // NOTE: if the subarray length is exactly 2, the midpoint is the left value
    // in the pair, so we consider them midpoint as part of the left half.

    // Sort left half arr[first..mid]
    MergeSort(arr, first, mid);

    // Sort right half arr[mid+1..last]
    MergeSort(arr, mid + 1, last);

    // Merge the two halves
    merge(arr, first, mid, last);
  }   
}

// Computes the average value in the subarray arr[first...last]
// Preconditions:
//   Parameters first and last are both valid array indices into the array,
//   with first <= last.
// Postcondtions:
//   Returns the average value in The subarray arr[first..last].
double AverageOfSubarray(const int arr[], int first, int last) {
  double avg = 0;
  int count = 0;
  for (int i = first; i <= last; i++) {
    avg = avg + arr[i];
    count++;
  }
  avg = avg/count;
  return avg;
}

// Computes the average value in the subarray arr[first...last]
// Preconditions:
//   Parameters first and last are valid array indices into the array,
//   with first <= last.
// Postcondtions:
//   Returns the index such that arr[first...index-1] contains values less than
//   or equal to the average of arr[first...last] and arr[index...last] contains values
//   greater than or equal to the average of arr[first...last].
int MeanPartition(int arr[], int first, int last) {

  double avg = AverageOfSubarray(arr, first, last);
  int leftIndex = first;
  int rightIndex = last;

  bool done = false;
  while (!done) {
    // while the value is less than the avg value, move left index to the right
    while ((leftIndex < last) && (arr[leftIndex] < avg))
      leftIndex++;
    // while right index is larger than the first index (0) AND the value is 
    // larger than the avg value, move right index to the left
    while ((rightIndex > first) && (arr[rightIndex] > avg)) 
      rightIndex--;
        // if the indeces haven't overlapped yet, swap the values in them and
        // continue moving them towards the middle
    if (leftIndex < rightIndex) {
      std::swap(arr[leftIndex], arr[rightIndex]);
      leftIndex++;
      rightIndex--;
    // otherwise the partition is finished
    } else {
      done = true;
    }
  }
  return leftIndex;
}

// Sorts the entries in the subarray arr[first..last] into ascending order using
// a recursive mean-sort algorithm.
// Precondition:
//   Parameters first and last are both valid array indices into the array,
//   with first <= last. Or, first > last to indicate an empty subarray.
// Postcondtions:
//   If the subarray was not empty, then subarray arr[first..last] is now sorted
//   in ascending order.
void MeanSort(int arr[], int first, int last) {
  
  if (first < last) {
    int startOfSecond = MeanPartition(arr, first, last);

    // Sort the first side of the array
    MeanSort(arr, first, startOfSecond-1);

    // Sort the second part of the array
    MeanSort(arr, startOfSecond, last);
  }
}

int main(int argc, char **argv) {
  int size = 50;
  int seed = 1234; // any value, to seed the random genrator, or 0 to use time of day

  if (argc != 3) {
    cout << "Usage: ./sort <SelectionSort/MergeSort/MeanSort> <size>" << endl; 
    cout << "For example: ./sort SelectionSort 10" << endl; 
    return 1;
  }
  string type = argv[1];
  size = atoi(argv[2]);

  assert(size > 0);

  int *arr = new int[size];
  cout << "Testing using a random array of length " << size << endl;
  int range = 5*size;
  for (int i = 0; i < size; i++) {
    int val = 1 + rand() % range; // rand value between 1 and range
    arr[i] = val;
  }
  if (size <= 50) {
    for (int i = 0; i < size; i++) 
      cout << arr[i] << " ";
    cout << endl;
  }

  double elapsedTime = 0.0;
  
  clock_t start, finish;

  if (type == "SelectionSort") {
    cout << "Sorting using selection sort...\n";
    start = clock();
    SelectionSort(arr, size);
    finish = clock();
  } else if (type == "MergeSort") {
    cout << "Sorting using merge sort...\n";
    start = clock();
    MergeSort(arr, 0, size-1);
    finish = clock();
  } else if (type == "MeanSort") {
    cout << "Sorting using mean sort...\n";
    start = clock();
    MeanSort(arr, 0, size-1);
    finish = clock();
  }
  assert(sorted(arr,size));
  elapsedTime += static_cast<double>(finish - start) / CLOCKS_PER_SEC;
  
  printf("Elapsed time for array of length %d: about %.6f seconds\n", size, elapsedTime);

  // This next line is needed by the plot.sh script to plot this data point.
  printf("PLOT %d %0.6f\n", size, elapsedTime);
  cout << endl;

  if (size <= 50) {
    for (int i = 0; i < size; i++) 
      cout << arr[i] << " ";
    cout << endl;
  }

  delete[] arr;
}
