// Adapted from QueueInterface.h created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Revisisons:
//   Z. Fitzsimmons, 1 March 2021 - update for spring 2021 project
//   K. Walsh, 4 March 2021 - reformatted comments, updated style
//   K. Walsh, 20 April 2021 - re-adapted from QueueuInterface.h

#ifndef QUEUE_INTERFACE_
#define QUEUE_INTERFACE_

// QueueuInterface defines the API for the Queue abstract data type. A Queue
// works in First-in-First-out fashion, allowing items to be added at the back
// and removed from the front.
template<class ItemType>
class QueueInterface
{
  public:
    // Checks whether this queue is empty.
    // Returns: true if the queue is empty, and false if not.
    virtual bool isEmpty() const = 0;

    // Checks whether this queue is full.
    // Returns: true if the queue is full, and false if not.
    virtual bool isFull() const = 0;

    // Get the size of the queue.
    // Returns: the number of items currently in the queue.
    virtual int size() const = 0;

    // Adds a new entry to the back of this queue.
    // Returns: true if newEntry was added successfully, and false on failure.
    // Postcondtion: If successful, newEntry is now at the back of the queue,
    // otherwise the queue is unchanged.
    virtual bool enqueue(const ItemType& newEntry) = 0;

    // Removes the entry at the front of this queue.
    // Returns: true if an entry was removed successfully, and false on failure.
    // Postcondtion: If successful, the front entry has been removed, otherwise
    // the queue is unchanged.
    virtual bool dequeue() = 0;

    // Accesses the entry at the front of this queue.
    // Precondition: The queue must must not be empty.
    // Returns: The entry at the front of this queue.
    // Postcondtion: The queue is unchanged.
    virtual ItemType peekFront() const = 0;

    // The destructor frees any dynamic memory associated with this queue.
    // If ItemType is a pointer type, any objects the queue entries point to
    // are not freed: that is the responsibility of clients.
    virtual ~QueueInterface() { }
}; // end QueueInterface
#endif
