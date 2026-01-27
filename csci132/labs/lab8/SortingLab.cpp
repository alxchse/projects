/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: K. Walsh
 * Program: SortingLab.cpp
 * Purpose: Test the quicksort and insertionSort implementations for correctness and
 *   efficiency.
 * Modified:
 *   6 April 2021 - K. Walsh - Split into multiple files.
 *   3 November 2021 - Z. Fitsimmons
 ***************************************************************************/

#include "ArrayList.h"
#include "Record.h"
#include "MergeSort.h"
#include "InsertionSort.h"
#include "Node.h"
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


// Delete a linked chain, and set the list pointer to nullptr.
template<class ItemType>
void deleteChain(Node<ItemType>* &list) {
  while (list != nullptr) {
    Node<ItemType>* temp = list;
    list = list->getNext();
    temp->setNext(nullptr); // just as a precaution
    delete temp;
    temp = nullptr; // just as a precaution
  }
}

// Verify a linked chain is sorted.
template<class ItemType>
bool checkSorted(const Node<ItemType>* list) {
  if (list != nullptr) {
    const Node<ItemType>* previous = list;
    const Node<ItemType>* current = list->getNext();

    int i = 2;
    while(current != nullptr) {
      if (previous->getItem() > current->getItem()) {
        cout << "Error: positions " << (i-1) << " and " << i
          << " (values " << previous->getItem() << " and "
          << current->getItem() << ") in the chain are not properly sorted.\n";
        return false;
      }
      previous = previous->getNext();
      current = current->getNext();
      i++;
    }
  }
  return true;
}

// Verify an ArrayList is sorted.
template<class ItemType>
bool checkSorted(const ArrayList<ItemType>* list) {
  for (int i = 2; i < list->getLength(); i++) {
    if (list->getEntry(i) < list->getEntry(i-1)) {
        cout << "Error: positions " << (i-1) << " and " << i
          << " (values " << list->getEntry(i-1) << " and "
          << list->getEntry(i) << ") in the ArrayList are not properly sorted.\n";
      return false;
    }
  }
  return true;
}

// Generate an ArrayList of the given length containing random numbers, each
// chosen from the range 1 to size/2.
// Preconditions:
//   size must be positive.
ArrayList<Record>* getRandomArrayList(int size) {
  assert(size > 0);
  ArrayList<Record>* list = new ArrayList<Record>();
  srand(1234);
  for (int i = 0; i < size; i++) 
    list->append(Record(1 + (rand() % (size/2))));
  return list;
}

// Generate an ArrayList of the given length containing values 1 up to size, in
// sequential sorted order.
ArrayList<Record>* getInorderArrayList(int size) {
  assert(size > 0);
  ArrayList<Record>* list = new ArrayList<Record>();
  for (int i = 1; i <= size; i++) 
    list->append(Record(i));
  return list;
}

// Generate an ArrayList of the given length containing values size down to 1,
// in sequential reverse sorted order.
ArrayList<Record>* getReverseOrderArrayList(int size) {
  assert(size > 0);
  ArrayList<Record>* list = new ArrayList<Record>();
  for (int i = size; i >= 1; i--) 
    list->append(Record(i));
  return list;
}

// Generate a Node chain of the given length containing random numbers, each
// chosen from the range 1 to size/2.
// Preconditions:
//   size must be positive.
Node<Record>* getRandomChain(int size) {
  assert(size > 0);
  Node<Record>* list = new Node<Record>(Record(1 + (rand() % (size/2))));
  Node<Record>* cursor = list;
  srand(1234);
  for (int i = 1; i < size; i++) {
    cursor->setNext(new Node<Record>(Record(1 + (rand() % (size/2)))));
    cursor = cursor->getNext();
  }
  return list;
}

// Generate a Node chain of the given length containing values 1 up to size, in
// sequential sorted order.
Node<Record>* getInorderChain(int size) {
  assert(size > 0);
  Node<Record>* list = new Node<Record>(Record(1));
  Node<Record>* cursor = list;

  for (int i = 2; i <= size; i++) {
    cursor->setNext(new Node<Record>(Record(i)));
    cursor = cursor->getNext();
  }
  return list;
}

// Generate a Node chain of the given length containing values size down to 1,
// in sequential reverse sorted order.
Node<Record>* getReverseOrderChain(int size) {
  assert(size > 0);
  Node<Record>* list = new Node<Record>(Record(size));
  Node<Record>* cursor = list;

  for (int i = size-1; i >= 1; i--) {
    cursor->setNext(new Node<Record>(Record(i)));
    cursor = cursor->getNext();
  }
  return list;
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

// Function for testing sort algorithms. This runs quicksort (using an
// ArrayList) and mergesort (using a linked chain of Nodes), for three different
// cases: random lists of length n, an already-sorted list of length n, and a
// already-reverse-sorted list of length n. For each test, it prints statistics
// on the number of Record comparisons performed and Record copies made.
void test_sort(int runs, int n) {
  int comparisons, assignments;

  cout << "\nTesting Contiguous Insertion Sort for random ArrayList:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    ArrayList<Record>* list = getRandomArrayList(n);
    Record::resetStatistics();
    insertionSort(list);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(list));
    delete list;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Contiguous Insertion Sort for already-ordered ArrayList:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    ArrayList<Record>* list = getInorderArrayList(n);
    Record::resetStatistics();
    insertionSort(list);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(list));
    delete list;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Contiguous Insertion for reverse-ordered ArrayList:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    ArrayList<Record>* list = getReverseOrderArrayList(n);
    Record::resetStatistics();
    insertionSort(list);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(list));
    delete list;
  }
  printStatistics(runs, comparisons, assignments);

  cout << endl;

  cout << "\nTesting Insertion Sort for random Node chain:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Node<Record>* chain = getRandomChain(n);
    Record::resetStatistics();
    insertionSort(chain);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(chain));
    deleteChain(chain);
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Insertion Sort for already-ordered Node chain:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Node<Record>* chain = getInorderChain(n);
    Record::resetStatistics();
    insertionSort(chain);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(chain));
    deleteChain(chain);
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Insertion Sort for reverse-ordered Node chain:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    Node<Record>* chain = getReverseOrderChain(n);
    Record::resetStatistics();
    insertionSort(chain);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(chain));
    deleteChain(chain);
  }
  printStatistics(runs, comparisons, assignments);

  cout << endl;


  cout << "\nTesting Merge Sort for random ArrayList:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    ArrayList<Record>* list = getRandomArrayList(n);
    Record::resetStatistics();
    mergeSort(list, 1, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(list));
    delete list;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Merge Sort for already-ordered ArrayList:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    ArrayList<Record>* list = getInorderArrayList(n);
    Record::resetStatistics();
    mergeSort(list, 1, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(list));
    delete list;
  }
  printStatistics(runs, comparisons, assignments);

  cout << "\nTesting Merge Sort for reverse-ordered ArrayList:\n";
  comparisons = assignments = 0;
  for (int i = 0; i < runs; i++) {
    ArrayList<Record>* list = getReverseOrderArrayList(n);
    Record::resetStatistics();
    mergeSort(list, 1, n);
    comparisons += Record::comparisons;
    assignments += Record::assignments;
    assert(checkSorted(list));
    delete list;
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

