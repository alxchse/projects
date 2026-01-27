// hw2.cpp
// fancy sum!
// alexandra chase
// amchas26@g.holycross.edu
// csci 235
// project 2: programming portion
#include <iostream>

int fancySum(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            sum = sum + i * j * j;
        }
    }
    return sum;
}