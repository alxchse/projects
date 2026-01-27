#include "BinaryNodeTree.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
 
  cout << "Tree A: " << endl;
  BinaryNodeTree<int> treeA;

  treeA.add(7);
  treeA.add(5);
  treeA.add(10);
  treeA.add(2);
  treeA.add(9);
  treeA.add(6);
  treeA.add(1);
  treeA.add(12);
  treeA.add(8);
  treeA.prettyPrint();

  cout << "Checking if Tree A is a binary search tree." << endl;
  if(treeA.isBST())
      cout << "Correct value of true returned." << endl;
  else
      cout << "Incorrect value of false returned." << endl;
  cout << endl << "Swapping each of the left and right subtrees of Tree A." << endl;
  treeA.swapSubTree();
  treeA.prettyPrint();

 
  cout << endl << endl << "Tree B: " << endl;
  BinaryNodeTree<int> treeB;

  treeB.add(10);
  treeB.add(7);
  treeB.add(12);
  treeB.add(2);
  treeB.add(9);
  treeB.add(8);
  treeB.add(1);
  treeB.add(15);
  treeB.remove(1);
  treeB.prettyPrint();

  cout << "Testing if Tree B is a binary search tree." << endl;
  if(!treeB.isBST())
      cout << "Correct value of false returned." << endl;
  else
      cout << "Incorrect value of true returned." << endl;
  cout << endl << "Swapping each of the left and right subtrees of Tree B." << endl;
  treeB.swapSubTree();
  treeB.prettyPrint();

  return 0;
}
