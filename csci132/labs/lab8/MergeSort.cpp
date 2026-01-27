/*******************************************************************
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Z. Fitzsimmons
 * File: MergeSort.cpp
 * Purpose: Implementation for ArrayList mergesort routine.
 ***************************************************************************/
#include "MergeSort.h"
   
template<class ItemType>
void mergeSort(ArrayList<ItemType>* list, int first, int last) {
    if (first >= last) {
        return;
    } else {
        int mid = (first+last)/2;

        mergeSort(list, first, mid);
        mergeSort(list, mid+1, last);

        merge(list, first, mid, last);
    }
}

/* Merges two sorted ArrayList segments list[first..mid] and
 * list[mid+1..last] into one sorted sublist.
 *
 * Precondition:
 *     first <= mid <= last. The segments list[first..mid] and
 *     list[mid+1..last] are each sorted in increasing order.
 * Postcondition:
 *     The segment list[first..last] in list is sorted in ascending
 *     order.
 */
template<class ItemType>
void merge(ArrayList<ItemType>* list, int first, int mid, int last) {
    int first1 = first;
    int last1 = mid;
    int first2 = mid+1;
    int last2 = last;

    ArrayList<ItemType> temp;
    while((first1 <= last1) && (first2 <= last2)) {
        if (list->getEntry(first1) < list->getEntry(first2)) {
            temp.append(list->getEntry(first1));
            first1++;
        } else {
            temp.append(list->getEntry(first2));
            first2++;
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
}
