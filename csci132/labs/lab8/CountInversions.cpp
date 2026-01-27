/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Fitzsimmons
 * Program: Inversions.cpp
 * Purpose: A program that determines the number of inversions in a given list
 * of integers.
 ***************************************************************************/

#include <iostream>
#include <algorithm>
#include <ctime>
#include "ArrayList.h"
using namespace std;

int slowCountInversions(ArrayList<int>*);

int fastCountInversions(ArrayList<int>*);
int fastCountInversions(ArrayList<int>*, int, int);
int mergeAndCount(ArrayList<int>*, int, int, int);

/* Given an ArrayList of integers, returns the number of
 * inversions in the list (i.e., the number of pairs of
 * entries in the list that are out of order)
 * using an O(n^2) approach.
 *
 * Precondition: List is a non-null pointer to an ArrayList
 *
 * Postcondition: Returns the number of inversions in the given list.
 */
int slowCountInversions(ArrayList<int>* list) {
    int inversions = 0;
    for (int i = 1; i <= list->getLength(); i++) {
        for (int j = i+1; j <= list->getLength(); j++) {
            if (list->getEntry(i) > list->getEntry(j))
                inversions++;
        }
    }
    return inversions;
}


/* Given an ArrayList of integers, returns the number of
 * inversions in the list (i.e., the number of pairs of
 * entries in the list that are out of order) by modifying
 * the approach from merge sort to sort the list and
 * count the number of pairs of entries that were out
 * of order.
 *
 * Precondition: List is a non-null pointer to an ArrayList.
 * If first <= last, then both first and last are valid positions with the
 * ArrayList, i.e., between 1 and ArrayList->getLength().
 *
 * Postcondition: The segment list[first..last] is sorted in ascending order
 * and the number of inversions in the segment list[first..last] before sorting
 * is returned.
 */
int fastCountInversions(ArrayList<int>* list, int first, int last) {
    if (first >= last) {
        return 0;
    } else {
        int mid = (first+last)/2;

        int numLeft = fastCountInversions(list, first, mid);
        int numRight = fastCountInversions(list, mid+1, last);

        int numMerged = mergeAndCount(list, first, mid, last);
        return numLeft+numRight+numMerged;
    }
}

/*
 * Merges two sorted ArrayList segments [first..mid] and [mid+1..last]
 * into one sorted sublist and returns the number of inversions.
 *
 * Precondition:
 *     first <= mid <= last. The segments list[first..mid] and
 *     list[mid+1..last] are each sorted in ascending order.
 * Postcondition:
 *     The segment list[first..last] is sorted in ascending order
 *     and the number of inversions in the segment list[first..last]
 *     before merging is returned.
 */
int mergeAndCount(ArrayList<int>* list, int first, int mid, int last) {

    int numInversions = 0;

    int first1 = first;
    int last1 = mid;
    int first2 = mid+1;
    int last2 = last;

    ArrayList<int> temp;
    while((first1 <= last1) && (first2 <= last2)) {
        // 
        if (list->getEntry(first1) < list->getEntry(first2)) {
            temp.append(list->getEntry(first1));
            first1++;
        } else {
            temp.append(list->getEntry(first2));
            first2++;
            numInversions++;
        }
    }

    while(first1 <= last1) {
        temp.append(list->getEntry(first1));
        first1++;
    }
    while(first2 <= last2) {
        temp.append(list->getEntry(first2));
        first2++;
    }

    int index = first;
    for(int i = 1; i <= temp.getLength(); i++) {
        list->replace(index, temp.getEntry(i));
        index++;
    } 
    return numInversions;
}

int main(int argc, char **argv) {

    int n = 0;
    string choice;
    ArrayList<int>* list = new ArrayList<int>;
    
    if (argc == 2) {
        choice = argv[1];
        // Prompt user for list size and values.
        cout << "Enter a number of values greater than 0: ";
        cin >> n;
        cout << "Enter a space-delimited sequence of " << n << " distinct integers: ";

        int val;
        for(int i = 0; i < n; i++) {
            cin >> val;
            list->append(val);
        }
    } else if (argc == 3) {
        // Generate a list of the numbers 1 to a given size in random order.
        choice = argv[1];
        n = atoi(argv[2]);
        cout << "Initializing a list of the numbers 1 to " << n << " in random order...\n";
        int* nums = new int[n];
        for (int i = 0; i < n; i++)
            nums[i] = i+1;
        srand(123);
        random_shuffle(&nums[0], &nums[n]);

        for (int i = 1; i <= n; i++) {
            list->append(nums[i-1]);
        }
        delete[] nums;

        if (n <= 30) {
            cout << "list = " << list->toPrettyString() << endl;
        } else {
            cout << "List is too large to display here.\n";
        }
    } else {
        cout << "Invalid number of commandline arguments." << endl;
        return 1;
    }

    cout << "Finding the number of inversions...\n";
    double elapsedTime = 0.0;
    int result = 0;
    if (choice == "slow") {
        clock_t start  = clock();
        result = slowCountInversions(list);
        clock_t finish = clock();
        elapsedTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;
    } else if (choice == "fast") {
        clock_t start  = clock();
        result = fastCountInversions(list, 1, n);
        clock_t finish = clock();
        elapsedTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;        
    }
    cout << "Number of inversions: " << result << endl << endl;

    printf("Elapsed time for length %d: about %.6f seconds\n", n, elapsedTime);

    return 0;
}
