// alexandra chase
// amchas26@g.holycross.edu
// csci 235
// 9 april 2024
// homework 5: longest common subsequence

#include <iostream>
#include <cstring>
using namespace std;

int longestCommonSubsequence(char x[], char y[]) {

    int m = strlen(x);              // get length of string in array x
    int n = strlen(y);              // get length of string in array y
    int ** resTable = new int*[m];  // declare resTahle
    for(int i = 0; i < m; i++){
        resTable[i] = new int[n];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // start off with 0 as the first table value
            if (i == 0 || j == 0) {
                resTable[i][j] = 0;
            } else if (x[i - 1] == y[j - 1]) {
                resTable[i][j] = resTable[i - 1][j - 1] + 1;
            } else {
                resTable[i][j] = max(resTable[i - 1][j], resTable[i][j - 1]);
            }
        }
    }
    return resTable[m-1][n-1];
}

int main() {
    char x[] = "ABBYXBC"; 
    char y[] = "CBXKYBC";

    cout << "\nThe longest subsequence is " << longestCommonSubsequence(x,y) << " letters long.\n";
}