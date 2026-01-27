// Adapted from BagInterface.h created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified: 21 January 2021 by K. Walsh - changed to Set, rather than Bag
// Modified: 9 February 2021 by K. Walsh - cleaned up comments
// Modified: 10 February 2021 by K. Walsh - fixed outdated comment on toVector

#ifndef SET_INTERFACE_
#define SET_INTERFACE_

#include <vector>

template<class ItemType>
class SetInterface {
public:
   /** Gets the current number of entries in this set.
    @return  The integer number of entries currently in the set. */
   virtual int getCurrentSize() const = 0;
   
   /** Sees whether this set is empty.
    @return  True if the set is empty, or false if not. */
   virtual bool isEmpty() const = 0;
   
   /** Adds a new entry to this set.
    @post  If successful, newEntry is stored in the set and
       the count of items in the set has increased by 1.
    @param newEntry  The object to be added as a new entry.
    @return  True if addition was successful, or false if not. */
   virtual bool add(const ItemType& newEntry) = 0;
   
   /** Removes the given entry from this set, if possible.
    @post  If successful, anEntry has been removed from the set
       and the count of items in the set has decreased by 1.
    @param anEntry  The entry to be removed.
    @return  True if removal was successful, or false if not. */
   virtual bool remove(const ItemType& anEntry) = 0;
   
   /** Removes all entries from this set.
    @post  Set contains no items, and the count of items is 0. */
   virtual void clear() = 0;
   
   /** Tests whether this set contains a given entry.
    @param anEntry  The entry to locate.
    @return  True if set contains anEntry, or false otherwise. */
   virtual bool contains(const ItemType& anEntry) const = 0;
   
   /** Returns a vector with copies of all entries in this set.
    @return  A vector containing all the entries in the set. */
   virtual std::vector<ItemType> toVector() const = 0;
   
   /** Destroys this set and frees its allocated memory. (See C++ Interlude 2.) */
   virtual ~SetInterface() { }
}; // end SetInterface
#endif
