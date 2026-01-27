// hw3.cpp
// alexandra chase
// amchas26@g.holycross.edu
// csci 235
// 18 march 2024
// homework 3, question 2: partitioning functions

#include <iostream>
using namespace std;

int partition(int numbers[], int lo, int hi, int pivot) {
  int leftIndex = lo;
  int rightIndex = hi-1;
  int pivotIndex;
  bool done = false;

  for (int i = 0; i <= hi; i++) {
    if (numbers[i] == pivot)
      pivotIndex = i;
  }
  swap(numbers[pivotIndex], numbers[hi]);
  for (int i = 0; i <= hi; i++)
   cout << numbers[i] << " ";
   cout << "\n";

  while (!done) {
    // while the value is less than the pivot value, move left index to the right
    while ((leftIndex <= (hi-1)) && (numbers[leftIndex] < pivot))
      leftIndex++;
    // while right index is larger than the first index (0) AND the value is 
    // larger than the pivot value, move right index to the left
    while ((rightIndex >= lo) && (numbers[rightIndex] > pivot)) 
      rightIndex--;
        // if the indeces haven't overlapped yet, swap the values in them and
        // continue moving them towards the middle
    if (leftIndex < rightIndex) {
      swap(numbers[leftIndex], numbers[rightIndex]);
      leftIndex++;
      rightIndex--;
    } else if (leftIndex > rightIndex) {
      swap(numbers[leftIndex], numbers[hi]);
      return leftIndex;
    }
  } // end of while
  return leftIndex;
} // end of partition

int main() {
    int A[10] = {1,6,7,2,3,5,8,9,11,21};
    int pivotindex = partition(A, 0, 9, 5);

    cout << "The updated array is: ";
    for (int i = 0; i < 10; i++) {
        cout << A[i] << ", ";
    }
    cout << "\n The pivot index is: " << pivotindex << "\n";
    return 0;
}

void swap(int x,int y) {
    int temp = x;
    x = y;
    y = temp; 
}