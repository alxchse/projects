// Lab 4 code for testing LinkedStack push, peek, pop, and size.
// Author: K. Walsh
// Date: July 18, 2020
// Revised by Z. Fitzsimmons Feb. 2021

#include "LinkedStack.h"
#include <iostream>

using namespace std;

int main(void) {
   LinkedStack<int> stk1;
   LinkedStack<int> stk2;
   LinkedStack<int> stk3;

   cout << "Contents of Stack 1: ";
   for(int i = 0; i <= 20; i+=2) {
       stk1.push(i);
       cout << i << " ";
   }
   cout << endl;

   cout << "Contents of Stack 2: ";
   for(int i = 0; i <= 20; i+=2) {
       stk2.push(i);
       cout << i << " ";
   }
   cout << endl;

   cout << "Contents of Stack 3: ";
   for(int i = 1; i <= 20; i+=2) {
       stk3.push(i);
       cout << i << " ";
   }
   cout << endl << endl << endl;

   cout << "Testing isEqual for Stack 1 and Stack 2." << endl;
   if (stk1.isEqual(stk2))
       cout << "Correctly returns true." << endl;
   else
       cout << "Incorrectly returns false." << endl;

   cout << endl << "Testing isEqual for Stack 1 and Stack 3." << endl;
   if (!stk1.isEqual(stk3))
       cout << "Correctly returns false." << endl;
   else
       cout << "Incorrectly returns true." << endl;

   cout << endl << "Adding 100 to Stack 2." << endl;
   stk2.push(100);
   cout << "Testing isEqual for Stack 1 and (updated) Stack 2." << endl;
   if (!stk1.isEqual(stk2))
       cout << "Correctly returns false." << endl;
   else
       cout << "Incorrectly returns true." << endl;
  
   cout << endl << "Testing isEqual for Stack 1 and an empty stack." << endl;
   LinkedStack<int> stk4;
   if (!stk1.isEqual(stk4))
       cout << "Correctly returns false." << endl;
   else
       cout << "Incorrectly returns true." << endl;

   cout << endl << "Testing isEqual for two empty stacks." << endl;
   LinkedStack<int> stk5;
   if (stk4.isEqual(stk5))
       cout << "Correctly returns true." << endl;
   else
       cout << "Incorrectly returns false." << endl;

} // end main
