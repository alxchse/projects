// Adapted from QueueInterface.h created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Revisisons:
//   Z. Fitzsimmons, 1 March 2021 - update for spring 2021 project
//   K. Walsh, 4 March 2021 - reformatted comments, updated style

#ifndef DEQUE_INTERFACE_
#define DEQUE_INTERFACE_

// DequeuInterface defines the API for the Dequee abstract data type. A Deque,
// or "double-ended queue" (usually pronounced either "deck" or "DQ"), is
// similar to a regular Queue, but items can be added and removed from both the
// front and the back. Conceptually, A Dequeue provides more features than a
// Queue, but less features than a List.
template<class ItemType>
class DequeInterface
{
  public:
    // Checks whether this deque is empty.
    // Returns: true if the deque is empty, and false if not.
    virtual bool isEmpty() const = 0;

    // Checks whether this deque is full.
    // Returns: true if the deque is full, and false if not.
    virtual bool isFull() const = 0;

    // Adds a new entry to the front of this deque.
    // Returns: true if newEntry was added successfully, and false on failure.
    // Postconditon: If successful, newEntry is now at the front of the deque.
    virtual bool enqueueFront(const ItemType& newEntry) = 0;

    // Adds a new entry to the back of this deque.
    // Returns: true if newEntry was added successfully, and false on failure.
    // Postcondtion: If successful, newEntry is now at the back of the deque,
    // otherwise the deque is unchanged.
    virtual bool enqueueBack(const ItemType& newEntry) = 0;

    // Removes the entry at the front of this deque.
    // Returns: true if an entry was removed successfully, and false on failure.
    // Postcondtion: If successful, the front entry has been removed, otherwise
    // the deque is unchanged.
    virtual bool dequeueFront() = 0;

    // Removes the entry at the back of this deque.
    // Returns: true if an entry was removed successfully, and false on failure.
    // Postcondtion: If successful, the back entry has been removed, otherwise
    // the deque is unchanged.
    virtual bool dequeueBack() = 0;

    // Accesses the entry at the front of this deque.
    // Precondition: The deque must must not be empty.
    // Returns: The entry at the front of this deque.
    // Postcondtion: The deque is unchanged.
    virtual ItemType peekFront() const = 0;

    // Accesses the entry at the back of this deque.
    // Precondition: The deque must must not be empty.
    // Returns: The entry at the back of this deque.
    // Postcondtion: The deque is unchanged.
    virtual ItemType peekBack() const = 0;

    // The destructor frees any dynamic memory associated with this deque.
    // If ItemType is a pointer type, any objects the dequeue entries point to
    // are not freed: that is the responsibility of clients.
    virtual ~DequeInterface() { }
}; // end DequeInterface
#endif
