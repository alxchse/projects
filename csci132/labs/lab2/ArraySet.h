// Header file for an array-based implementation of the ADT set.
// Author: Z. Fitzsimmons, 2020
// Modified: K. Walsh, 10 Feb 2021 - added invariants.

#ifndef ARRAY_SET_
#define ARRAY_SET_

#include "SetInterface.h"

/* An implementation of SetInterface using an array and a count to track the
 * items contained in the set.
 * Invariants:
 *   (1) There are no duplicate entries in the "filled" portion of the items array.
 *   (2) Slots 0 through (itemCount-1) of the items array are "filled" and
 *       contain valid items. The remaining slots, itemCount through
 *       (maxItems-1), are "empty" and unused.
 *   (3) There are at most maxItems stored in the set.
 */
template<class ItemType>
class ArraySet : public SetInterface<ItemType> {
    private:
        static const int DEFAULT_CAPACITY = 8; // Small size to test for a full set
        ItemType items[DEFAULT_CAPACITY];      // Array of set items
        int itemCount;                         // Current count of set items 
        int maxItems;                          // Max capacity of the set
   
        // Returns either the index of the element in the array items that
        // contains the given target or -1, if the array does not contain 
        // the target.
        int getIndexOf(const ItemType& target) const;   

    public:
        ArraySet();
        int getCurrentSize() const;
        bool isEmpty() const;
        bool add(const ItemType& newEntry);
        bool remove(const ItemType& anEntry);
        void clear();
        bool contains(const ItemType& anEntry) const;
        std::vector<ItemType> toVector() const;
}; // end ArraySet

#include "ArraySet.cpp"
#endif
