// Starter code for Lab 4
//Compute prime factors of input number

#include <iostream>
#include "LinkedStack.h"

using namespace std;
int main(void) {
  int number;
  int factor, result;
  LinkedStack<int> primeStack;

  cout << "Enter an integer: ";
  cin >> number;

  for (int i = 2; i <= number; i++){
    while (result % i == 0) {
      primeStack.push(i);
      result = result/i;
    }
  }

  cout << "The prime factors of " << number << " are " << "\n";

  while (!primeStack.isEmpty()) {
    int divisor = primeStack.peek();
    primeStack.pop();
    cout << divisor "\n";
  }

  return 0;
} //main
