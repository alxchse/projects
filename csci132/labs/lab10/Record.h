// Specification of Record class.
// Author: Z. Fitzsimmons
// Date: 1 April 2021
// Modified:
//   5 April 2021 - K. Walsh - Added a custom output operator, removed getValue.
#ifndef RECORD_H
#define RECORD_H

#include <iostream>

// Record objects are meant to represent some arbitrary, possibly large or
// possibly complex, data items to be searched or sorted. For example, a photo,
// or an audio recording. These Records don't actually hold any real data.
// Instead, each Record holds only some small (hidden) random data value used to
// order the Records.
//
// Records can be copied (using the custom copy-constructor or custom
// assignment-operator), and they can be compared to each other (using the
// custom comparison operators). Both of these operations are tracked, for
// statistics and analysis purposes.
//
// Records can be printed to cout (using a custom output-stream operator).
class Record {
  private:
    // Note: there is no programmatic way to access this hidden value. This
    // value is only meant to be used internally by the Record class. If you
    // want to print, assign, or compare Records, just use the usual
    // operators, e.g.: if (recordA < recordB) cout << recordA << endl;
    int hidden_value;

  public:
    // A count of how many Record comparisons have been performed
    static int comparisons;

    // A count of how many Record copies have been made, in total
    static int assignments;

    // constructor
    Record(int val = 0);

    // copy constructor
    Record(const Record &original);

    // custom assignment operator
    Record& operator=(const Record &original);

    // custom comparison operators
    friend bool operator ==(const Record &x, const Record &y);
    friend bool operator !=(const Record &x, const Record &y);
    friend bool operator >=(const Record &x, const Record &y);
    friend bool operator <=(const Record &x, const Record &y);
    friend bool operator >(const Record &x, const Record &y);
    friend bool operator <(const Record &x, const Record &y);

    // custom output stream operator, for printing to cout
    friend std::ostream& operator<<(std::ostream& output, const Record &r);

    // Generate a random, sorted Record array of the given length.
    // The optional seed parameter is used to see the random number generator,
    // or use seed=0 to use the current time of day to seed the generator.
    // All of the numbers generated will be even.
    // The maxval pararameter is set to the maximum random value chosen.
    static Record* generateRandomSortedArray(int len, int &maxval, int seed = 0);

    // Generate a random, unsorted Record array of the given length.
    // The optional seed parameter is used to see the random number generator,
    // or use seed=0 to use the current time of day to seed the generator.
    static Record* generateRandomUnsortedArray(int len, int seed = 0);
    
    // Reset the statistics variables.
    static void resetStatistics();

    // Print a summary of the comparison and copy counts.
    // The optional num_operations parameter specifies how many operations were
    // performed, so that averages can be printed instead of just totals.
    static void printStatistics(int num_operations = 0);
    
    // Print an array of n Records.
    static void printArray(Record arr[], int n);

    // Print a subarray from index first to last, inclusive.
    static void printSubarray(Record arr[], int first, int last);

    // This method should not be used except for debugging. It verifies that the
    // record y matches this one, but does not count as a comparison in the
    // statistics.
    bool test_verify(const Record &y) const;
};


#endif
