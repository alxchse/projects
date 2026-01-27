/*******************************************************************
 * Name: Alexandra Chase
 * Date: 25 March 2023
 * Course: CSCI 132
 * Assignment: Lab 7
 * Instructor: K. Walsh
 * Program: ComputeCommonFaster.cpp
 * Purpose: A program that computes the list of items that two already-sorted
 *   lists have in common.
 ***************************************************************************/
#include <iostream>
#include <ctime>
#include "ArrayList.h"
using namespace std;

// Compute the unique, common elements of two lists. The resulting list will
// contain all those (and only those) values that appear in both of the lists,
// with no duplicates, sorted in ascending order (smallest to largest).
// Preconditions:
//   The two input lists must each already be sorted in ascending order. Each
//   may contain duplicate values.
// Postconditions:
//   The result list will contain all those values (and only those values) that
//   appear in common between the first and second input lists.
//   The result list will be sorted in ascending order, with no duplicates.
//   This time, we use recursion and binary search to cutdown runtime and
//   improve efficiency. 

template<class ItemType>
bool binarySearch(const ArrayList<ItemType>& list, int target, int lo, int hi)
{

  int mid = (hi+lo) / 2;                            // midpoint of list
  int current = list.getEntry(mid);

  if (lo > hi){                                     // base case: prevent infinite looping
    return false;
  } else if (current == target){                    // base case: found target
    return true;
  } else if (current < target) {                    // search bigger half of remaining list
    return binarySearch(list, target, mid+1, hi);
  } else if (current > target) {                    // search smaller half of remaining list
    return binarySearch(list, target, lo, mid-1);
  }
  return false;
}

template<class ItemType>
ArrayList<int> computeCommon(const ArrayList<ItemType>& first, const ArrayList<ItemType>& second)
{

  ArrayList<ItemType> result;
  
  for (int i = 1; i <= first.getLength(); i++) {
    ItemType val = first.getEntry(i);
    if (binarySearch(second, val, 1, second.getLength()) && !result.contains(val))
      result.append(val);
    }
    return result;
}

// Check whether result contains a sorted list of unique, common items from
// first and second.
template<class ItemType>
bool verifyCommon(const ArrayList<ItemType>& first,
    const ArrayList<ItemType>& second,
    const ArrayList<ItemType>& result)
{
  // check for duplicates in result, and that it is in ascending order
  for (int i = 1; i < result.getLength(); i++) {
    ItemType a = result.getEntry(i);
    ItemType b = result.getEntry(i+1);
    if (a > b) {
      cout << "Result contains values " 
        << a << " and " << b << " not in ascending order.\n";
      return false;
    }
    if (a == b) {
      cout << "Result contains duplicate value " << a << endl;
      return false;
    }
  }

  // check that every value in result is present in both first and second
  for (int i = 1; i <= result.getLength(); i++) {
    ItemType val = result.getEntry(i);
    if (!first.contains(val) || !second.contains(val)) {
      cout << "Result contains value "
        << val << " that wasn't present in both original lists.\n";
        return false;
    }
  }

  // check that every value in common was included in the result
  for (int i = 1; i <= first.getLength(); i++) {
    ItemType val = first.getEntry(i);
    if (second.contains(val) && !result.contains(val)) {
      cout << "Result is missing value "
        << val << " that was present in both lists.\n";
      return false;
    }
  }

  return true;
}

// Generates n random numbers and appends them onto a list. The random numbers
// will be arranged in ascending order (smallest to largest), and there may be
// duplicates.
void fillRandom(ArrayList<int>& nums, int n) {
  int val = 1 + rand() % 5; // random value between 1 and 5
  for (int i = 0; i < n; i++) {
    val += rand() % 4; // increment by random amount from 0 to 3
    assert(val >= 0); // check for rollover
    nums.append(val);
  }
}

int main(int argc, char **argv)
{
  int len;
  if (argc == 2) {
    // Use command-line parameter, if given
    len = atoi(argv[1]);
  } else {
    // Otherwise prompt user for list size
    cout << "Enter a length to use for the lists: ";
    cin >> len;
  }

  ArrayList<int> lstA;
  ArrayList<int> lstB;

  srand(1234);
  cout << "Initializing two lists, each with " << len << " random numbers...\n";
  fillRandom(lstA, len);
  fillRandom(lstB, len);

  if (len <= 30) {
    cout << "lstA = " << lstA.toPrettyString() << endl;
    cout << "lstB = " << lstB.toPrettyString() << endl;
  } else {
    cout << "Lists are too large to display here.\n";
  }

  cout << "Computing the unique, common values of the two lists...\n";

  clock_t start  = clock();
  ArrayList<int> result = computeCommon(lstA, lstB);
  clock_t finish = clock();
  double elapsedTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;

  cout << "Done!\n";
  printf("Elapsed time for length %d: about %.6f seconds\n", len, elapsedTime);

  if (len <= 30) {
    cout << "result = " << result.toPrettyString() << endl;
    assert(verifyCommon(lstA, lstB, result));
    cout << "Result was computed correctly!\n";
  }

  return 0;
}
