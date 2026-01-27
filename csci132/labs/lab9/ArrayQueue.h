// File Name: ArrayQueue.h
// Author: Zack Fitzsimmons
// Course: CSCI 132
// Date: Fall 2020
// Purpose: Specification of ArrayQueue class
// Revisions
//   4 March 2021 - K. Walsh - Updated as new project for spring 2021
//   20 April 2021 - K. Walsh - Adapted from ArrayQueue

#ifndef ARRAY_QUEUE_
#define ARRAY_QUEUE_

#include "QueueInterface.h"
#include <string>

// The ArrayQueue class provides a circular-array-based implementation of
// QueueInterface. Items are stored in a dynamic array with a dynamic capacity
// that grows as needed to fit however many items are added, so the queue is
// never full.
template<class ItemType>
class ArrayQueue : public QueueInterface<ItemType> {

  private:
    static const int DEFAULT_CAPACITY = 50;
    ItemType *items; // Circular array of queue items, allocated dynamically
    int front;       // Index to front of queue
    int back;        // Index to back of queue
    int count;       // Number of items currently in the queue
    int capacity;    // Max number of items that fit in the queue
    // Invariants:
    //   At all times, capacity > 0, and 0 <= count <= capacity.
    //   At all times, 0 <= front < capacity.
    //   At all times, 0 <= back < capacity.
    //   When the queue is empty, then count = 0.
    //   When the queue is not empty, then 0 < count <= DEFAULT_CAPACITY.
    //   When the queue is not empty, then array positions [front] through
    //     [back], inclusive (and wrapping around), are filled with valid
    //     entries, and all other array positions are ignored.
    //   At all times, front+count-1 = back (wrapping around).
    //   Note: This means when the queue is partially full,
    //     the back will be to the right (but wrapping around) of the front;
    //     when the queue has only one item, then front = back; and when the
    //     queue is completely full or completely empty, then the back will be
    //     just to the left (but wrapping around) the front.
    //
    // Example of a partially-full ArrayQueue (with capacity 10):
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
    // Another example of a partially-full ArrayQueue (with capacity 10):
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
    // Example of an empty ArrayQueue (with capacity 10):
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
    // Another example of an empty ArrayQueue (with capacity 10):
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

    // Default constructor creates an empty queue with a default initial capacity.
    ArrayQueue();

    // One-argument constructor creates an empty queue with the given initial capacity.
    ArrayQueue(int maxItems);

    // Copy-constructor creates an new queue that is a copy of an existing queue.
    ArrayQueue(const ArrayQueue<ItemType>& other);

    // Assignment-operator.
    ArrayQueue<ItemType>& operator=(const ArrayQueue<ItemType>& other);

    // Destructor frees all dyanmically allocated memory associated with the queue.
    virtual ~ArrayQueue();

    // These next methods implement QueueInterface.
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    bool dequeue();
    bool enqueue(const ItemType &newEntry);
    ItemType peekFront() const;
};
#include "ArrayQueue.cpp"
#endif
