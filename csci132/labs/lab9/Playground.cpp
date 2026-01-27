/*******************************************************************
 * Date: Fall 2020
 * Course: CSCI 132
 * Assignment: Lab 9
 * Instructor: Fitzsimmons
 * Program: Playground.cpp
 * Purpose: Interactive test program for BinaryNodeTree class.
 *     Updated for Fall 2021, Z. Fitzsimmons 
 ***************************************************************************/

#include "BinaryNodeTree.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

// Global variables (the calamity!) to hold our test trees.
BinaryNodeTree<int> iTree; // a tree containing integers
BinaryNodeTree<string> sTree; // a tree containing strings

// Helper functions
char getCommand();
string getParameter();
void help();
bool doCommand();

// Useful visitor functions
void printInt(int value) {
  cout << value << " ";
}

void printStr(string value) {
  cout << value << " ";
}

void showTrees() {
  cout << endl;
  cout << "Tree A, containing "
    << iTree.getNumberOfNodes() << " integers,"
    << " with height " << iTree.getHeight() << ":\n";
  iTree.prettyPrint();
  cout << endl;

  cout << "Tree B, containing "
    << sTree.getNumberOfNodes() << " strings,"
    << " with height " << sTree.getHeight() << ":\n";
  sTree.prettyPrint();
  cout << endl;
}

int main() {

  srand(1234);

  // Add some values to each tree
  for (int i = 1; i < 10; i++)
    iTree.add(i);

  string words[] = { "cat", "dog", "foo", "bar", "baz", "qux", "bee", "see" };
  for (int i = 0; i < 8; i++)
    sTree.add(words[i]);
 
  showTrees();

  help();
  while (doCommand())
    ;

  return 0;
}

// help() prints a menu of commands the user may type.
void help()
{
  cout << endl <<
    "Each command is one letter, sometimes with an argument (any word, no spaces).\n"
    "Type \"a\" to add an item to the tree (you will be prompted for the value).\n"
    "Or type \"a 42\" to add the value 42 to the appropriate tree.\n"
    "You can do many commands at once: \"a 42 a hello a 17 r 42 i\" for example.\n"
    "\n"
    "Valid commands are:\n"
    "  a - [A]dd a number or string to one of the trees.\n"
    "  r - [R]emove a number or string from one of the trees.\n"
    "  g - [G]row the trees by random additions.\n"
    "  s - [S]hrink the trees by random deletions.\n"
    "  c - [C]lear both trees.\n"
    "  t - [T]raverse the trees, printing all nodes.\n"
    "  i - [I]nfo about whther trees are same shape.\n"
    "  q - [Q]uit.\n"
    "Press <Enter> to continue." << flush;

  char c;
  do {
    cin.get(c);
  } while (c != '\n');
  cout << "Enter one or more commands: " << flush;
}  // end help

// getCommand() reads from standard input, looking for the next command entered
// by the user. It returns the character representing the user's command, as a
// lowercase letter. This function also prints a prompt when appropriate.
char getCommand()
{
  string knowncommands = "argsctibqARGSCTIBQhH?"; // all the known commands
  while (true) {
    char c = 'q';
    cin.get(c);
    if (!cin) {
      // no more input, pretend user typed 'Q'
      return 'q';
    }
    if (c == '\n') {
      // user hit enter, print a new prompt
      cout << "Enter one or more commands: " << flush;
    } else if (c == ' ' || c == '\t' || c == '\r') {
      // ignore leading whitespace
    } else if (knowncommands.find(c) != string::npos) {
      // valid command, return it as a lowercase letter
      return tolower(c);
    } else {
      // unrecognized character
      cout << "Sorry, I don't understand '" << c << "'. Try 'H' for help." << endl;
    }
  }
}  // end getCommand

// getParameters() reads from standard input, looking for the next parameter
// entered by the user (a single word, no spaces). It returns the string
// representing the user's parameter. function also prints a prompt when
// appropriate.
string getParameter()
{
  string param = "";
  while (true) {
    char c = cin.peek();
    if (!cin) {
      // no more input, treat this as the end of the parameter
      if (param == "")
        param = "EndOfInput";
      break;
    } else if (c == '\n' && param == "") {
      // user hit enter, print a new prompt
      cout << "Enter a value (integer or word, no spaces): " << flush;
    } else if (c == '\n') {
      // user hit enter, this is the end of the parameter
      break;
    } else if (isspace(c) && param == "") {
      // ignore leading whitespace
    } else if (isspace(c)) {
      // trailing whitespace is the end of the parameter
      break;
    } else {
      // regular character, treat as part of the parameter
      param = param + c;
    }
    cin.get(c);
  }
  return param;
}  // end getParameter

string randWord() {
  const char *vowels = "aeiou";
  string s = "";
  s += ('a' + (rand() % 25));
  s += vowels[rand()%5];
  s += ('a' + (rand() % 25));
  return s;
}

// doCommand() gets a command from the user, and a parameter if needed, then
// performs the requested operation on one or both of the trees.
bool doCommand()
{
  bool continueInput = true;

  char cmd = getCommand();
  string word = "???"; // assigned below, only if necessary for cmd
  int val = -1;
  std::stringstream summary;
  int count = 0;
  bool ok = false;

  switch (cmd) {
    case 'q':
      cout << "Binary Tree stress-test finished." << endl;
      continueInput = false;
      break;

    case 'h':
    case '?':
      help();
      break;

    case 'a': 
      word = getParameter();
      val = atoi(word.c_str());
      if (val > 0)
        ok = iTree.add(val);
      else
        ok = sTree.add(word);
      if (ok)
        cout << "OK: added " << word << endl;
      else
        cout << "Nope: could not add " << word << endl;
      showTrees();
      break;

    case 'r':
      word = getParameter();
      val = atoi(word.c_str());
      if (val > 0)
        ok = iTree.remove(val);
      else
        ok = sTree.remove(word);
      if (ok)
        cout << "OK: removed " << word << endl;
      else
        cout << "Nope: could not remove " << word << endl;
      showTrees();
      break;

    case 'g': 
      count = 0;
      for (int i = 0; i < 10; i++) {
        val = 1 + (rand() % 99);
        ok = iTree.add(val);
        if (ok) {
          summary << " " << val;
          count++;
        }
      }
      if (count > 0)
        cout << "OK: added " << count << " random values: " << summary.str() << endl;
      else
        cout << "Nope: could not add random values\n";
      summary = stringstream();
      count = 0;
      for (int i = 0; i < 10; i++) {
        word = randWord();
        ok = sTree.add(word);
        if (ok) {
          summary << " " << word;
          count++;
        }
      }
      if (count > 0)
        cout << "OK: added " << count << " random values: " << summary.str() << endl;
      else
        cout << "Nope: could not add random values\n";
      showTrees();
      break;

    case 's': 
      count = 0;
      for (int i = 0; i < 50; i++) {
        val = 1 + (rand() % 99);
        ok = iTree.remove(val);
        if (ok) {
          summary << " " << val;
          count++;
        }
      }
      if (count > 0)
        cout << "OK: removed " << count << " random values: " << summary.str() << endl;
      else
        cout << "Nope: could not remove random values\n";
      summary = stringstream();
      count = 0;
      for (int i = 0; i < 500; i++) {
        word = randWord();
        ok = sTree.remove(word);
        if (ok) {
          summary << " " << word;
          count++;
        }
      }
      if (count > 0)
        cout << "OK: removed " << count << " random values: " << summary.str() << endl;
      else
        cout << "Nope: could not remove random values\n";
      showTrees();
      break;

    case 'c':
      iTree.clear();
      sTree.clear();
      showTrees();
      break;

    case 't':
      cout << "A's Pre-order  : ";
      iTree.preorderTraverse(printInt);
      cout << endl;
      cout << "A's In-order   : ";
      iTree.inorderTraverse(printInt);
      cout << endl;
      cout << "A's Post-order : ";
      iTree.postorderTraverse(printInt);
      cout << endl;
      cout << "A's Level-order: ";
      iTree.levelorderTraverse(printInt);
      cout << endl;
      cout << "B's Pre-order  : ";
      sTree.preorderTraverse(printStr);
      cout << endl;
      cout << "B's In-order   : ";
      sTree.inorderTraverse(printStr);
      cout << endl;
      cout << "B's Post-order : ";
      sTree.postorderTraverse(printStr);
      cout << endl;
      cout << "B's Level-order: ";
      sTree.levelorderTraverse(printStr);
      cout << endl;
      break;

    case 'i':
      cout << "Checking if A and B have the same shape... " << flush;
      ok = iTree.isSameShape(sTree);
      cout << (ok ? "YES" : "NO") << endl;
      break;

  }  // end switch on cmd

  return continueInput;
}  // end doCommand
