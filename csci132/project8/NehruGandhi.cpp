// Alexandra Chase
// amchas26@g.holycross.edu
// CSCI 132
// Project 8
// April 26 2023
// This program takes a doc of family information and puts it into a Binary Tree. 

#include "Tree.h"
#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


void printFamilyTree(string prefix, TreeNode<Person*> *t)
{
  if (t == nullptr) {
    cout << "oops, subtree is nullptr\n";
    return;
  }
  int n = t->getNumChildren();
  cout << prefix << t->getItem()->toString() << ", with " << n << " children\n";
  for (int i = 0; i < n; i++) {
    TreeNode<Person*> *child = t->getChild(i);
    printFamilyTree(prefix + "| ", child);
  }
}

void printChildren(TreeNode<Person*> *person) {
  // if pointer is null, print error message.
  if (person == nullptr) {
    cout << "None.";
  }
  // number of children that person has.
  int n = person->getNumChildren();

  // for each child, make a pointer and print their name
  for (int i = 0; i < n; i++) {
    TreeNode<Person*> *child = person->getChild(i);
    cout << child->getItem()->name;
    cout << "\n";
  }
} // end printChildren

Person* findPersonHelper(TreeNode<Person*> *person, string target) {

  // if given ptr is null, return nullptr
  if (person == nullptr) {
    return nullptr;
  }
  // count of how many children the given pointer has
  int n = person->getNumChildren();

  // if the given ptr contains the target name, return it
  if (person->getItem()->name == target) {
    return person->getItem();
  }
  // iterate through all the children of the given node to see 
  // if the target is there. make sure it is not a leaf before
  // iterating through. make a pointer for each child, if it matches,
  // and isnt null, return. 
  if (!person->isLeaf()) {
    for (int i = 0; i < n; i++) {
      TreeNode<Person*> *childPtr = person->getChild(i);
      auto child = findPersonHelper(childPtr, target);
      if(child != nullptr) {
        return child;
      } 
    }
  }
  return nullptr;
} // end findPersonHelper

Person* findPerson(Tree<Person*> *tree, string target) {

  // base case: if the tree is empty return null ptr.
  // otherwise, call helper function with the root of the tree and
  // the given target.
  if (tree->isEmpty())
    return nullptr;
  else
    return findPersonHelper(tree->getRoot(), target);
} // end findPerson

void printFriendsOf(Tree<Person*> *family, string target) {

  // find the target person in the family. if its null, 
  // print an error message and return
  auto person = family->findNode(findPerson(family, target));
  if (person == nullptr) {
    cout << "Siblings and cousins of " << target << "are not known.";
    return;
  }

  // find that persons parent, if its null, 
  // print an error message and return
  auto parent = person->getParent();
  if (parent == nullptr) { 
    cout << "Parents of " << target << "are not known.";
    return;
  }

  // find the grand parent of the person, if its null,
  // print an error message and return 
  auto grandparent = parent->getParent();
  if (grandparent == nullptr) {
    cout << "Extended cousins of " << target << " are not known." << endl;
    return;
  }

  // get number of "siblings" the given person has
  int nSiblings = parent->getNumChildren();

  // if the persons name is the target, then make a pointer
  // for each sibling and print their name
  if (person->getItem()->name == target) {
    cout << "Siblings and cousins of " << target << " include: " << endl;
    for (int i = 0; i < nSiblings; i++) {
      auto sibling = parent->getChild(i);
      if (sibling->getItem()->name != target) { // all siblings who aren't main
        cout << sibling->getItem()->name << endl;
      }
    }
    // now get the number of extended family members,
    // for each member make a pointer. make sure that pointer isnt also
    // the parent of the given node (it should be an "aunt" or "uncle.")
    // get the number of "cousins," for each cousin, make a pointer and
    // print their name.
    int nExtended = grandparent->getNumChildren();
    for (int i = 0; i < nExtended; i++) {
      auto otherFam = grandparent->getChild(i);
      if (otherFam->getItem()->name != parent->getItem()->name) {
        int nCousins = otherFam->getNumChildren();
        for (int j = 0; j < nCousins; j++) {
          auto cousin = otherFam->getChild(j);
          cout << cousin->getItem()->name << endl;
        }
      }
    }
  }
} // end printFriendsOf

bool isPrimeMinister(Person *p)
{
  return p->occupation.find("Prime Minister") != string::npos;
}

int printPrimeMinistersHelper(TreeNode<Person*> *p) {

  // count = how many family members found (which will be returned)
  int count = 0;

  // if given person is null, return 0 as count
  if (p == nullptr) {
    return count;
  }

  // n = number of children under the given person node
  int n = p->getNumChildren();

  // if the given person is a prime minister, add that to the count and print out their 
  // information
  if (isPrimeMinister(p->getItem())) {
    count++;
    cout << p->getItem()->name << " was Prime Minister of " << p->getItem()->occupation << "\n";
  }
  // now iterate through their children nodes and look for any more prime ministers. if one is found,
  // then add it to the count and print out their information. make sure it isn't a leaf beforehand.
  if (!p->isLeaf()) {
    for (int i = 0; i < n; i++) {
      TreeNode<Person*> *child = p->getChild(i);
      count += printPrimeMinistersHelper(child);
      }
    }
  return count;
} // end printPrimeMinistersHelper

bool printPrimeMinisters(Tree<Person*> *tree) {

  // if tree is empty, return false.
  // otherwise calls printPrimeMinistersHelper function and
  // prints the total number of family members found
  int count = 0;
  if (tree->isEmpty())
    return false;
  else {  
    cout << "Results of search for prime ministers: \n";
    count = printPrimeMinistersHelper(tree->getRoot());
    cout << "Found " << count << " family members. \n";
  return true;
  }
} // end printPrimeMinisters

void printAncestryOf(Tree<Person*> *tree, string target) {

  // if the tree is empty, print an error message and return
  if (tree->isEmpty()) {
    cout << target << " does not appear to be a member of this family. \n";
    return;
  }

  // make a pointer and find the given target name. if the pointer is
  // null, print an error message and return
  TreeNode<Person*> *p = tree->findNode(findPerson(tree,target));
  if (p == nullptr) {
    cout << target << " does not appear to be a member of this family. \n";
    return;
  }

  // make a pointer for the parent of the given person.
  TreeNode<Person*> *parent = p->getParent();

  // if its the root, print message saying that the parent is the head of the family and return.
  // otherwise, print out the given person's lineage. then move up in the tree to their parent. 
  // continue up the tree until there are no parents left. 
  if (p->isRoot()) {
    cout << target << " is the head of this family. \n";
    cout << "No further information available. \n";
  } else {
    cout << "Known ancestry of " << target << ": \n";
    cout << target << " is the " << p->getItem()->lineage << ". \n";
    while (parent != nullptr) {
      cout << parent->getItem()->name << " is the " << parent->getItem()->lineage << ". \n";
      parent = parent->getParent();
    }
    cout << "No further information available. \n";
  }
  return;
}

int printGenerationHelper(TreeNode<Person*> *person, int generation) {
  
  // make variables for the number of family members within that generation
  // and n for the number of children that person has.
  int nMembers = 0;
  int n = person->getNumChildren();

  // if that pointer is null, return the total number of members found so far.
  if (person == nullptr) {
    return nMembers;
  }

  // if analyzing the first generation, print that persons name and birth year. 
  if (generation == 1) {
    cout << person->getItem()->name << " born in " << person->getItem()->birthYear << ". \n";
    nMembers++;
  }

  // iterate through the rest of the generations below to find other members of the generation.
  for (int i = 0; i < n; i++) {
    nMembers += printGenerationHelper(person->getChild(i), generation -1);
  }
  return nMembers;
}

void printGeneration(Tree<Person*> *tree, int generation) {

  // print out the members of that generation using the printGenerationHelper function.
  // then print the total number of found family members within that generation.
  cout << "Members of generation " << generation << "\n";
  int nMembers = printGenerationHelper(tree->getRoot(), generation);
  cout << "Found " << nMembers << " family members. \n";
}

Tree<Person*> *parseFile(string filename)
{
  ifstream data(filename.c_str());
  if (!data.is_open()) {
    cout << "Sorry, the file 'genealogy.txt' could not be opened.\n"
      << "It is needed for this program. Please make sure it\n"
      << "can be found in the current directory and has suitable\n"
      << "file permissions.\n";
    return nullptr;
  }

  Tree<Person*> *family = new Tree<Person*>();

  string line;
  while ( getline(data, line) ) {
    Person *p = Person::parseLine(line);
    if (p == nullptr)
      continue; // skip any lines that could not be parsed
    if (family->isEmpty()) {
      family->addAsRoot(p);
    } else  {
      string parentName = "Unknown";
      if (p->lineage.rfind("son of ", 0) == 0)
        parentName = p->lineage.substr(7); // everything after "son of "
      else if (p->lineage.rfind("daughter of ", 0) == 0)
        parentName = p->lineage.substr(12); // everything after "daughter of "
      Person* parent = findPerson(family, parentName);
      if (parent == nullptr || !family->addAsChild(p, parent)) {
         cout << "Oops, this person's parent, " << parentName << " doesn't appear to be part of this family:\n"
           << "  " << p->toString() << "\n";
         delete p;
      }
    }
  }

  return family;
}

int main(void)
{
  Tree<Person*> *family = parseFile("genealogy.txt");

  cout << "The entire family tree:\n";
  printFamilyTree("", family->getRoot());
  cout << "\n";

  cout << "Portion of the family tree showing Indira Gandhi and her descendents:\n";
  TreeNode<Person*> *indiraNode = family->findNode(findPerson(family, "Indira Gandhi"));
  printFamilyTree("", indiraNode);
  cout << "\n";
  
  TreeNode<Person*> *vijayaNode = family->findNode(findPerson(family, "Vijaya Lakshmi Pandit"));
  cout << "Children of Vijaya Lakshmi Pandit are:\n";
  printChildren(vijayaNode);
  cout << "\n";

  printFriendsOf(family, "Balwant Kumar Nehru");
  cout << "\n";
  
  printPrimeMinisters(family);
  cout << "\n";

  printAncestryOf(family, "Anasuya Gandhi");
  printAncestryOf(family, "Prof. Fitzsimmons");
  cout << "\n";

  printGeneration(family, 4);
  cout << "\n";

  cout << "\n";

  return 0;
}
