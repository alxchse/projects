// Header file for an array-based implementation of the ADT set.
// Author: Z. Fitzsimmons, 2020
// Modified: K. Walsh, 10 Feb 2021 - copied and modified from ArraySet.h

#ifndef PARALLEL_ARRAY_SET_
#define PARALLEL_ARRAY_SET_

#include "SetInterface.h"

/* An implementation of SetInterface using two parallel arrays to track the
 * items contained in the set.
 * Invariants:
 *   (1) There are no duplicate entries among the "filled" slots of the items array.
 *   (2) If filled[i] is true, then items[i] is "filled" and contains a valid item.
 *       Other arrays slots are "empty" and unused.
 *   (3) There are at most maxItems stored in the set.
 */
template<class ItemType>
class ParallelArraySet : public SetInterface<ItemType> {
    private:
        static const int DEFAULT_CAPACITY = 8; // Small size to test for a full set
        ItemType items[DEFAULT_CAPACITY];      // Array of set items
        bool filled[DEFAULT_CAPACITY];         // Array of bools to keep track of filled items slots
        int maxItems;                          // Max capacity of the set
   
        // Returns either the index of the element in the array items that
        // contains the given target or -1, if the array does not contain 
        // the target.
        int getIndexOf(const ItemType& target) const;   

    public:
        ParallelArraySet();
        int getCurrentSize() const;
        bool isEmpty() const;
        bool add(const ItemType& newEntry);
        bool remove(const ItemType& anEntry);
        void clear();
        bool contains(const ItemType& anEntry) const;
        std::vector<ItemType> toVector() const;
}; // end ParallelArraySet

#include "ParallelArraySet.cpp"
#endif
