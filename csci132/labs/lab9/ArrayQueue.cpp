// File Name: ArrayQueue.cpp
// Author: Zack Fitzsimmons
// Course: CSCI 132
// Date: Fall 2020
// Purpose: Array-based implementation of ArrayQueue ADT
// Revisions
//   4 March 2021 - K. Walsh - Updated as new project for spring 2021
//  20 April 2021 - K. Walsh - Re-adapted from ArrayQueue.cpp

#include "ArrayQueue.h"
#include <stdexcept>

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue()
{
  capacity = DEFAULT_CAPACITY;
  items = new ItemType[capacity]; // dyanamically allocate array
  front = 0;
  back = capacity - 1;
  count = 0;
}  // end default constructor

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue(int maxItems)
{
  capacity = maxItems;
  items = new ItemType[capacity]; // dyanamically allocate array
  front = 0;
  back = capacity - 1;
  count = 0;
}  // end one-argument constructor

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue(const ArrayQueue<ItemType>& other)
{
  // Start with an empty array. We will make it have a capacity exactly
  // the same as the other queue.
  capacity = other.capacity;
  items = new ItemType[capacity];
  front = 0;
  back = capacity - 1;;
  count = 0;

  // Next, copy all of the items from other and put them into this array.
  // Note: We don't need the items to go in the same array positions. So
  // even if the other queue has wrapped around, we can put the items into
  // our array starting at array index 0.
  int cursor = other.front;
  for (int i = 0; i < other.count; i++) {
    enqueueBack(other.items[cursor]);
    cursor = (cursor + 1) % other.capacity;
  }
}  // end copy constructor

template<class ItemType>
ArrayQueue<ItemType>::~ArrayQueue()
{
  delete[] items;
}  // end destructor

template<class ItemType>
bool ArrayQueue<ItemType>::isEmpty() const
{
  return count == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayQueue<ItemType>::isFull() const
{
  return false;
}  // end isFull

template<class ItemType>
int ArrayQueue<ItemType>::size() const
{
  return count;
}  // end size

template<class ItemType>
bool ArrayQueue<ItemType>::dequeue()
{
  if (isEmpty()) {
    return false;
  } else {
    // Increment front, being careful to wrap around to the start
    front = (front + 1) % capacity;
    count--;
    return true;
  }
} // end dequeue

template<class ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const
{
  // Check precondition, just to be safe.
  if (isEmpty())
    throw std::runtime_error("ArrayQueue::peekFront() called with empty queue");

  // ArrayQueue is not empty, so return the front entry
  return items[front];
} // end peekFront

template<class ItemType>
bool ArrayQueue<ItemType>::enqueue(const ItemType &newEntry)
{
  if (count == capacity) {
    // Grow to make room for more items.
    int largerCapacity = capacity * 2;
    ItemType *largerItems = new ItemType[largerCapacity];
    for (int i = 0; i < count; i++)
      largerItems[i] = items[(front + i) % capacity];
    front = 0;
    back = count - 1;
    delete [] items;
    items = largerItems;
    capacity = largerCapacity;
  }
  // Increment back, being careful to wrap around to the start
  back = (back + 1) % capacity;
  items[back] = newEntry;
  count++;
  return true;
} // end enqueue

