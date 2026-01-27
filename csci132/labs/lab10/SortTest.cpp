/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 10
 * Instructor: Z. Fitzsimmons
 * Program: SortTest.cpp
 * Purpose: Compare implementations of insertion sort, merge sort, quick sort, and tree sort.
 ***************************************************************************/

#include "Record.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "InsertionSort.h"
#include "TreeSort.h"
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


// Verify an array is sorted.
template<class ItemType>
bool checkSorted(const ItemType arr[], int n) {
  for (int i = 1; i < n; i++) {
    if (arr[i] < arr[i-1]) {
        cout << "Error: positions " << (i-1) << " and " << i
          << " (values " << arr[i-1] << " and "
          << arr[i] << ") in the array are not properly sorted.\n";
      return false;
    }
  }
  return true;
}

// Generate an array of the given length containing values 1 up to size, in
// sequential sorted order.
Record* getInorderArray(int size) {
  assert(size > 0);
  Record* arr = new Record[size];
  for (int i = 0; i < size; i++)
    arr[i] = Record(i+1);
  return arr;
}

// Generate an array of the given length containing values size down to 1,
// in sequential reverse sorted order.
Record* getReverseOrderArray(int size) {
  assert(size > 0);
  Record* arr = new Record[size];
  for (int i = 0; i < size; i++)
    arr[i] = Record(size-i);
  return arr;
}

// Generate an array of the given length containing the numbers
// from 1 to size in a random order.
// Preconditions:
//   size must be positive.
Record* getRandomArray(int size) {
  assert(size > 0);
  Record* arr = getInorderArray(size);
  srand(1234);
  random_shuffle(&arr[0], &arr[size]);
  return arr;
}

// Print statistics about how many comparisons and copy operations were
// performed.
void printStatistics(int num_operations, int comparisons, int assignments) {
  // cout << "  Statistics: " << endl;
  if (num_operations > 0) {
    float c = (float)comparisons / (float)num_operations;
    float a = (float)assignments / (float)num_operations;
    cout << "  " << setw(6) << c << " comparisons per sort, averaged across " << num_operations << " sortings.\n";
    cout << "  " << setw(6) << a << " copies per sort, averaged across " << num_operations << " sortings.\n";
  } else {
    cout << "  " << setw(6) << comparisons << " comparisons performed in total during sorting.\n";
    cout << "  " << setw(6) << assignments << " copies made in total during sorting.\n";
  }
}

// Function for testing sort algorithms for three different
// cases: random arrays of length n, an already-sorted array of length n, and a
// already-reverse-sorted array of length n. For each test, it prints statistics
// on the number of Record comparisons performed and Record copies made.
void test_sort(int runs, int n) {
  int comparisons, assignments;

  cout << "\nTesting Insertion Sort for random array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getRandomArray(n);
    Record::resetStatistics();
    insertionSort(nums, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Insertion Sort for already-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getInorderArray(n);
    Record::resetStatistics();
    insertionSort(nums, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Insertion Sort for reverse-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getReverseOrderArray(n);
    Record::resetStatistics();
    insertionSort(nums, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << endl;

  cout << "\nTesting Merge Sort for random array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getRandomArray(n);
    Record::resetStatistics();
    mergeSort(nums, 0, n-1);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Merge Sort for already-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getInorderArray(n);
    Record::resetStatistics();
    mergeSort(nums, 0, n-1);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Merge Sort for reverse-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getReverseOrderArray(n);
    Record::resetStatistics();
    mergeSort(nums, 0, n-1);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << endl;


  cout << "\nTesting Quick Sort for random array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getRandomArray(n);
    Record::resetStatistics();
    quickSort(nums, 0, n-1);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Quick Sort for already-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getInorderArray(n);
    Record::resetStatistics();
    quickSort(nums, 0, n-1);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Quick Sort for reverse-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getReverseOrderArray(n);
    Record::resetStatistics();
    quickSort(nums, 0, n-1);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << endl;


  cout << "\nTesting Tree Sort for random array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getRandomArray(n);
    Record::resetStatistics();
    treeSort(nums, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Tree Sort for already-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getInorderArray(n);
    Record::resetStatistics();
    treeSort(nums, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Tree Sort for reverse-ordered array:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Record* nums = getReverseOrderArray(n);
    Record::resetStatistics();
    treeSort(nums, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(nums, n));
    delete nums;
  }
  printStatistics(runs, comparisons, assignments);

  cout << endl;


}

int main(int argc, char **argv) {
  int size;
  int runs = 100;

  if (argc >= 2) {
    size = atoi(argv[1]);
    if (argc >= 3)
      runs = atoi(argv[2]);
  } else {
    cout << "Enter the list size to test: ";
    cin >> size;
  }

  assert(size > 0);
  assert(runs > 0);

  cout << "Performing " << runs << " trials using lists of length " << size << endl;

  test_sort(runs, size);
}

