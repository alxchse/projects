// TODO Insert Prologue

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

Person *findPersonHelper(TreeNode<Person*> *node, string target)
{
  // TODO: complete this code
  return nullptr;
}

Person *findPerson(Tree<Person*> *tree, string target)
{
  if (tree->isEmpty())
    return nullptr;
  else
    return findPersonHelper(tree->getRoot(), target);
}

bool isPrimeMinister(Person *p)
{
  return p->occupation.find("Prime Minister") != string::npos;
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
  
  // TODO: print children of a given person
  // TreeNode<Person*> *vijayaNode = family->findNode(findPerson(family, "Vijaya Lakshmi Pandit"));
  // cout << "Children of Vijaya Lakshmi Pandit are:\n";
  // printChildren(vijayaNode);
  cout << "\n";

  // TODO: print all of siblings and cousins of a given person (here "sibling" means
  // they have the same parent as you, and "cousin" means any child of your
  // parents's siblings)
  // printFriendsOf(family, "Balwant Kumar Nehru");
  cout << "\n";
  
  // TODO: print all prime ministers in the family
  // printPrimeMinisters(family);
  cout << "\n";

  // TODO: print all of the ancestors of a given person
  // printAncestryOf(family, "Anasuya Gandhi");
  // printAncestryOf(family, "Prof. Fitzsimmons");
  cout << "\n";

  // TODO (extra credit): print all members of a given generation
  // printGeneration(family, 4);
  cout << "\n";

  cout << "\n";

  return 0;
}
