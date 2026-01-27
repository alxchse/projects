// Filename: TestDeque.cpp
// Author: Zack Fitzsimmons
// Date: Spring 2021 
// Course: CSCI 132
// Modified:
//   1 March 2021 - Z. Fitzsimmons - Added LinkedDeque support.
//   4 March 2021 - K. Walsh - Added comments, new commands for stress-testing.
//
// Purpose: Test deque functions. This is a menu-driven demonstration program.
// It accepts commands from user, and in response performs various operations in
// a Deque object.

#include <iostream>
#include <string>
#include "DequeInterface.h"
#include "ArrayDeque.h"
#include "LinkedDeque.h"

using namespace std;

char getCommand();
string getParameter();
void help();
bool doCommand(string kind, DequeInterface<string>* testDeque);

int main(void)
{
  string kind;

  cout << "Welcome the Deque Stress-Tester!" << endl;
  cout << "Do you want to test an array-based or a linked implementation (array/linked)? ";
  cin >> kind;

  while (kind != "array" && kind != "linked") {
    cout << "Please enter either \"array\" or \"linked\": ";
    cin >> kind;
  }

  DequeInterface<string> *testDeque;

  if (kind == "array")
    testDeque = new ArrayDeque<string>();
  else
    testDeque = new LinkedDeque<string>();

  help();
  while (doCommand(kind, testDeque))
    ;
}  // end main()

// help() prints a menu of commands the user may type.
void help()
{
  cout << endl
    << "To use this program, enter type any of the following" << endl
    << "commands. Each command will cause the corresponding" << endl
    << "corresponding operation to be performed on the dequee." << endl
    << endl
    << "Each command is a single character. Some commands also" << endl
    << "require a parameter (any single word, no spaces)." << endl
    << "You can type just the the one character, then hit enter," << endl
    << "and if needed you will be prompted for the parameter." << endl
    << "Or, you can put the command and parameter on one line," << endl
    << "separated by a space, like this: \"A hello\"" << endl
    << "You can also put many commands on one line, separated" << endl
    << "by spaces, like this: \"A hello A world S S\"" << endl
    << endl
    << "The valid commands are:" << endl
    << "  P - Put a word at the front of the deque." << endl
    << "  A - Append a word at the back of the deque." << endl
    << "  F - Print (but don't remove) the front entry." << endl
    << "  B - Print (but don't remove) the back entry." << endl
    << "  R - Remove (but don't print) the front of the dequeue." << endl
    << "  X - Remove (but don't print) the back of the dequeue." << endl
    << "  I - Print status info about the dequeue." << endl
    << "  M - Test the destructor and copy constructor." << endl
    << "  H - Print this help screen." << endl
    << "  Q - Quit." << endl
    << "Press <Enter> to continue." << flush;

  char c;
  do {
      cin.get(c);
  } while (c != '\n');
}  // end help()

// getCommand() reads from standard input, looking for the next command entered
// by the user. It returns the character representing the user's command, as a
// lowercase letter. This function also prints a prompt when appropriate.
char getCommand()
{
  string knowncommands = "apfbrximhqAPFBRXIMHQ"; // all the known commands
  while (true) {
    char c = 'q';
    cin.get(c);
    if (!cin) {
      // no more input, pretend user typed 'Q'
      return 'q';
    }
    if (c == '\n') {
      // user hit enter, print a new prompt
      cout << "Enter a command: " << flush;
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
      cout << "Enter a parameter (single word, no spaces): " << flush;
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

// doCommand() gets a command from the user, and a parameter if needed, then
// performs the requested operation on testDeque.
bool doCommand(string kind, DequeInterface<string>* testDeque)
{
  bool continueInput = true;

  char cmd = getCommand();
  string word = "???"; // assigned below, only if necessary for cmd

  try {
    switch (cmd) {
      case 'q':
        cout << "Deque stress-test finished." << endl;
        continueInput = false;
        break;
      case 'h':
      case '?':
        help();
        break;
      case 'a': 
        word = getParameter();
        if (testDeque->enqueueBack(word))
          cout << "Successfully appended '" << word << "' at the back." << endl;
        else
          cout << "enqueueBack() returned false. Maybe the Deque is full?" << endl;
        break;
      case 'p':
        word = getParameter();
        if (testDeque->enqueueFront(word))
          cout << "Successfully put '" << word << "' at the front." << endl;
        else
          cout << "enqueueFront() returned false. Maybe the Deque is full?" << endl;
        break;
      case 'b': 
        word = testDeque->peekBack();
        cout << "The back entry is '" << word << "'" << endl;
        break;
      case 'f': 
        word = testDeque->peekFront();
        cout << "The front entry is '" << word << "'" << endl;
        break;
      case 'r':
        if (testDeque->dequeueFront())
          cout << "Successfully removed the front of the Deque." << endl;
        else
          cout << "dequeueFront() returned false. Maybe the Deque is empty?" << endl;
        break;
      case 'x': 
        if (testDeque->dequeueBack())
          cout << "Successfully removed the back of the Deque." << endl;
        else
          cout << "dequeueBack() returned false. Maybe the Deque is empty?" << endl;
        break;
      case 'i': 
        if (testDeque->isEmpty()) {
          cout << "The deque is empty." << endl;
        } else {
          cout << "The deque is not empty." << endl;
        }
        break;
      case 'm':
        cout << "Testing the destructor and copy constructors." << endl;
        if (kind == "array") {
          ArrayDeque<string>* original = (ArrayDeque<string>*)testDeque;
          ArrayDeque<string>* copy = new ArrayDeque<string>(*original);
          if (debugCompare(original, copy)) {
            cout << "Successfully made a copy of the ArrayDeque." << endl;
          } else {
            cout << "Made a copy, but the copy does not match the original." << endl;
          }
          delete copy;
          cout << "Successfully deleted the copy." << endl;
        } else {
          int n = Node<string>::count;
          LinkedDeque<string>* original = (LinkedDeque<string>*)testDeque;
          LinkedDeque<string>* copy = new LinkedDeque<string>(*original);
          if (debugCompare(original, copy)) {
            cout << "Successfully made a copy of the LinkedDeque." << endl;
          } else {
            cout << "Made a copy, but the copy does not match the original." << endl;
          }
          delete copy;
          cout << "Successfully deleted the copy." << endl;
          int m = Node<string>::count;
          if (n != m) {
            cout << "ERR: There were " << n << " Node objects in existence before" << endl
              << "making then deleting the copy, but now there are " << m << " node objects." << endl;
          }
        }
        break;
    }  // end switch on cmd
  } catch (PrecondViolatedExcept e) {
    cout << "Command '" << cmd << "' caused an exception." << endl;
    cout << e.what() << endl;
  }

  return continueInput;
}  // end doCommand()

template <class ItemType>
bool debugCompare(ArrayDeque<ItemType>* a, ArrayDeque<ItemType>* b) {
  if (!sanityCheck("original", a) || !sanityCheck ("copy", b))
    return false;
  if (a->items == b->items) {
      cout << "ERR: Both original and copy share the same array.\n";
      return false;
  }
  if (a->count != b->count) {
    cout << "Original contains " << a->count << " entries, but copy has " << b->count << ".\n";
    return false;
  }
  for (int i = 0; i < a->count; i++) {
    string as = a->items[(a->front + i) % a->capacity];
    string bs = b->items[(b->front + i) % b->capacity];
    if (as != bs) {
      cout << "Entry " << i << " is '" << as << "' in original, but '" << bs << "' in copy.\n";
      return false;
    }
  }
  return true;
}

template <class ItemType>
bool debugCompare(LinkedDeque<ItemType>* a, LinkedDeque<ItemType>* b) {
  if (!sanityCheck("original", a) || !sanityCheck ("copy", b))
    return false;
  Node<ItemType>* ap = a->frontPtr;
  Node<ItemType>* bp = b->frontPtr;
  // Note: we need to check if both are null first, so we don't mistake that
  // situation (both empty) for them "sharing" the same chain.
  if (ap == nullptr && bp == nullptr) {
      return true;
  }
  if (ap == bp) {
      cout << "ERR: Both original and copy share the same linked chain.\n";
      return false;
  }
  if (a->backPtr == b->backPtr) {
      cout << "ERR: Both original and copy share the same last node.\n";
      return false;
  }
  int n = 0;
  while (ap != nullptr && bp != nullptr) {
    n++;
    if (ap == b->frontPtr) {
        cout << "ERR: Copy's chain leads to a node in original's chain.\n";
        return false;
    }
    if (bp == a->frontPtr) {
        cout << "ERR: Original's chain leads to a node in copy's chain.\n";
        return false;
    }
    string as = ap->getItem();
    string bs = bp->getItem();
    if (as != bs) {
      cout << "Entry " << n << " is '" << as << "' in original, but '" << bs << "' in copy.\n";
      return false;
    }
    ap = ap->getNext();
    bp = bp->getNext();
  }
  if (ap != nullptr) {
    cout << "Copy has only " << n << " nodes in the chain, but copy has more.";
    return false;
  }
  if (bp != nullptr) {
    cout << "Original has only " << n << " nodes in the chain, but original has more.";
    return false;
  }
  return true;
}

template <class ItemType>
bool sanityCheck(string name, ArrayDeque<ItemType>* dq) {
  if (dq->capacity <= 0) {
    cout << "ERR: capacity for " << name << " is set to " << dq->capacity << "." << endl;
    return false;
  }
  if (dq->count < 0) {
    cout << "ERR: count for " << name << " is set to " << dq->count << "." << endl;
    return false;
  }
  if (dq->count > dq->capacity) {
    cout << "ERR: count for " << name << " is set to " << dq->count << ","
      << " but capacity is only " << dq->capacity << "." << endl;
    return false;
  }
  if (dq->front < 0 || dq->front >= dq->capacity) {
    cout << "ERR: front for " << name << " is set to " << dq->front << ","
      << " but valid range is 0 to " << (dq->capacity-1) << "." << endl;
    return false;
  }
  if (dq->back < 0 || dq->front >= dq->capacity) {
    cout << "ERR: back for " << name << " is set to " << dq->back << ","
      << " but valid range is 0 to " << (dq->capacity-1) << "." << endl;
    return false;
  }
  // Note: front+count-1 could possibly be negative, if front=0,count=0, and the
  // `%` operator in C++ (and C, and Java) doesn't quite behave as one might
  // expect for negative numbers. By adding capacity here, it ensures the index
  // will be positive and `%` will "wrap it around" properly.
  if (((dq->front + dq->count - 1 + dq->capacity) % dq->capacity) != dq->back) {
    cout << "ERR: front + count - 1 != back " << name << ", since front=" << dq->front << ","
      << " count=" << dq->count << ", back=" << dq->back << "." << endl;
    return false;
  }
  if ((void *)dq->items == nullptr) {
    cout << "ERR: items array for " << name << " is null.\n";
    return false;
  }
  return true;
}

template <class ItemType>
bool sanityCheck(string name, LinkedDeque<ItemType>* dq) {
  // make sure either both pointers are null, or neither are
  if (dq->frontPtr == nullptr && dq->backPtr == nullptr)
    return true;
  if (dq->frontPtr == nullptr || dq->backPtr == nullptr) {
    cout << "ERR: Front and back pointers for " << name << " are inconsitent.\n";
    return false;
  }
  // make sure back points at the last item in the chain
  if (dq->backPtr->getNext() != nullptr) {
    cout << "ERR: Back pointer for " << name << " appears to not be the last node in chain.\n";
    return false;
  }
  // make sure there is a valid chain of nodes, i.e. that
  // frontPtr->getNext()->getNext() ...  will eventually lead to the same node
  // that backPtr points to, without any infinite loops
  Node<ItemType>* tortoise = dq->frontPtr;
  Node<ItemType>* hare = dq->frontPtr;
  int i = 0;
  while (hare != dq->backPtr) {
    if (hare->getNext() == nullptr) {
      cout << "ERR: Chain for " << name << " leads to terminal node " << hare
        << ", but back is " << dq->backPtr << "." << endl;
      return false;
    }
    hare = hare->getNext();
    i++;
    if ((i % 2) == 0)
      tortoise = tortoise->getNext(); // tortoise moves slowly
  }
  return true;
}
