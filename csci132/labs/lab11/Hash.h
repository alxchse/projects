#ifndef HASH_
#define HASH_

#include <functional> // for std::hash
#include <limits.h>   // for MAX_INT

// This computes a hash of its input, which can be of more or less any type. 
// Parameters:
//   key - any value.
// Returns:
//   an integer between 0 and MAX_INT, inclusive.
template<class KeyType>
int hash(const KeyType &key) {
  // C++ has a standard, built-in hash function named std::hash<K> that works
  // for most key types K. Unfortunately it can return values outside our
  // desired range of 0 to INT_MAX. The unusual "&" operation below is a
  // bitwise-AND operation that ensures the result will be within our desired
  // range.
  auto h = std::hash<KeyType>{}(key);
  return h & INT_MAX;
}

#endif // HASH_
