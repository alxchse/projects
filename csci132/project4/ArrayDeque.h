// File Name: ArrayDeque.h
// Author: Zack Fitzsimmons
// Course: CSCI 132
// Date: Fall 2020
// Purpose: Specification of ArrayDeque class
// Revisions
//   4 March 2021 - K. Walsh - Updated as new project for spring 2021

#ifndef ARRAY_DEQUE_ 
#define ARRAY_DEQUE_

#include "DequeInterface.h"
#include <string>

// The ArrayDeque class provides a circular-array-based implementation of
// DequeInterface. Items are stored in a dynamic array with a fixed maximum
// capacity that can't be changed once created. The capacity does not grow,
// even when the deque becomes full.
template<class ItemType>
class ArrayDeque : public DequeInterface<ItemType> {

  private:
    static const int DEFAULT_CAPACITY = 50;
    ItemType *items; // Circular array of deque items, allocated dynamically
    int front;       // Index to front of deque
    int back;        // Index to back of deque
    int count;       // Number of items currently in the deque
    int capacity;    // Max number of items that fit in the deque
    // Invariants:
    //   At all times, capacity > 0, and 0 <= count <= capacity.
    //   At all times, 0 <= front < capacity.
    //   At all times, 0 <= back < capacity.
    //   When the deque is empty, then count = 0.
    //   When the deque is not empty, then 0 < count <= DEFAULT_CAPACITY.
    //   When the deque is not empty, then array positions [front] through
    //     [back], inclusive (and wrapping around), are filled with valid
    //     entries, and all other array positions are ignored.
    //   At all times, front+count-1 = back (wrapping around).
    //   Note: This means when the deque is partially full,
    //     the back will be to the right (but wrapping around) of the front;
    //     when the deque has only one item, then front = back; and when the
    //     deque is completely full or completely empty, then the back will be
    //     just to the left (but wrapping around) the front.
    //
    // Example of a partially-full ArrayDeque (with capacity 10):
    //      0   1   2   3   4   5   6   7   8   9 
    //    +---+---+---+---+---+---+---+---+---+---+
    //    |   |   |   | A | B | C | D | E | F |   |
    //    +---+---+---+---+---+---+---+---+---+---+
    //      front = 3 --^                   ^-- back = 8
    //    Note: count = 6, and
    //       front + count - 1 = 3 + 6 - 1
    //                         = 8
    //                         = back
    //
    // Another example of a partially-full ArrayDeque (with capacity 10):
    //      0   1   2   3   4   5   6   7   8   9 
    //    +---+---+---+---+---+---+---+---+---+---+
    //    | R | S | T | U |   |   |   |   | P | Q |
    //    +---+---+---+---+---+---+---+---+---+---+
    //                          front = 8 --^
    //                  ^--- back = 3
    //    Note: count = 6, and 
    //       front + count - 1 = 8 + 6 - 1
    //                         = 13
    //                         = 3 (wrapping around to the start)
    //                         = back
    //
    // Example of an empty ArrayDeque (with capacity 10):
    //      0   1   2   3   4   5   6   7   8   9 
    //    +---+---+---+---+---+---+---+---+---+---+
    //    |   |   |   |   |   |   |   |   |   |   |
    //    +---+---+---+---+---+---+---+---+---+---+
    //                  ^-- back = 3
    //           front = 4 --^   
    //    Note: count = 0, and 
    //       front + count - 1 = 4 + 0 - 1
    //                         = 3
    //                         = back
    //
    // Another example of an empty ArrayDeque (with capacity 10):
    //      0   1   2   3   4   5   6   7   8   9 
    //    +---+---+---+---+---+---+---+---+---+---+
    //    |   |   |   |   |   |   |   |   |   |   |
    //    +---+---+---+---+---+---+---+---+---+---+
    //      ^-- front = 0
    //                               back = 9 --^   
    //    Note: count = 0, and 
    //       front + count - 1 = 0 + 0 - 1
    //                         = -1
    //                         = 9 (wrapping around to the end)
    //                         = back

  public:

    // Default constructor creates an empty deque with a default capacity.
    ArrayDeque();

    // One-argument constructor creates an empty queue with the given capacity.
    ArrayDeque(int maxItems);

    // Copy-constructor creates an new deque that is a copy of an existing deque.
    ArrayDeque(const ArrayDeque<ItemType>& other);

    // Destructor frees all dyanmically allocated memory associated with the
    // deque.
    virtual ~ArrayDeque();

    // These next methods implement DequeInterface.
    bool isEmpty() const;
    bool isFull() const;
    bool dequeueFront();
    bool dequeueBack();
    bool enqueueFront(const ItemType &newEntry);
    bool enqueueBack(const ItemType &newEntry);
    ItemType peekFront() const;
    ItemType peekBack() const;

    // These friend functions are for testing and debugging.
    template <class ItemTypeB>
    friend bool sanityCheck(std::string name, ArrayDeque<ItemTypeB> *deque);
    template <class ItemTypeB>
    friend bool debugCompare(ArrayDeque<ItemTypeB>* a, ArrayDeque<ItemTypeB>* b);
};
#include "ArrayDeque.cpp"
#endif
