// Implementation of Record class.
// Author: Z. Fitzsimmons
// Date: 1 April 2021
// Modified:
//   5 April 2021 - K. Walsh - Added a custom output operator, removed getValue.
#include "Record.h"
#include <iomanip>
#include <cassert>
#include <ctime>

using namespace std;

// Static variables.
int Record::comparisons = 0;
int Record::assignments = 0;

Record::Record(int x) {
  hidden_value = x;
} // constructor

Record::Record(const Record &original) {
  Record::assignments++;
  hidden_value = original.hidden_value;
}

Record& Record::operator=(const Record &original) {
  // Note: here, we count self-assignment as an assignment
  Record::assignments++;
  hidden_value = original.hidden_value;
  return *this;
}

bool operator ==(const Record &x, const Record &y)
{
  Record::comparisons++;
  return x.hidden_value == y.hidden_value;
} // custom overloaded is-equals

bool operator !=(const Record &x, const Record &y)
{
  Record::comparisons++;
  return x.hidden_value != y.hidden_value;
} // custom overloaded is-not-equal

bool operator >=(const Record &x, const Record &y)
{
  Record::comparisons++;
  return x.hidden_value >= y.hidden_value;
}// custom overloaded is-greater-than-or-equal

bool operator <=(const Record &x, const Record &y)
{
  Record::comparisons++;
  return x.hidden_value <= y.hidden_value;
}// custom overloaded is-less-than-or-equal

bool operator >(const Record &x, const Record &y)
{
  Record::comparisons++;
  return x.hidden_value > y.hidden_value;
} // custom overloaded is-greather-than

bool operator <(const Record &x, const Record &y)
{
  Record::comparisons++;
  return x.hidden_value < y.hidden_value;
} // custom overloaded is-less-than

std::ostream& operator<<(std::ostream& output, const Record &r) {
  output << r.hidden_value;
  return output;
} // custom overloaded output stream operator

Record* Record::generateRandomSortedArray(int n, int &maxval, int seed) {
  assert(n > 0);
  Record* array = new Record[n];
  if (seed == 0)
    seed = (int)time(NULL);
  cout << "Using seed " << seed << " to generate random numbers.\n";
  srand(seed);
  int val = 2 + 2*(rand() % 3); // random value either 2, 4, or 6
  for (int i = 0; i < n; i++) {
    val += 2*(rand() % 5); // increment by random even amount from 0 to 8
    assert(val >= 0); // check for rollover
    array[i].hidden_value = val;
  }
  maxval = val;
  return array;
}

Record* Record::generateRandomUnsortedArray(int n, int seed) {
  assert(n > 0);
  Record* array = new Record[n];
  if (seed == 0)
    seed = (int)time(NULL);
  cout << "Using seed " << seed << " to generate random numbers.\n";
  srand(seed);
  int range = 5*n;
  for (int i = 0; i < n; i++) {
    int val = 1 + rand() % range; // rand value between 1 and range
    array[i].hidden_value = val;
  }
  return array;
}
    
void Record::resetStatistics() {
  Record::comparisons = 0;
  Record::assignments = 0;
}

void Record::printStatistics(int num_operations) {
  // cout << "  Statistics: " << endl;
  if (num_operations > 0) {
    float c = (float)Record::comparisons / (float)num_operations;
    float a = (float)Record::assignments / (float)num_operations;
    cout << "  " << setw(6) << c << " comparisons per operation, averaged across " << num_operations << " operations.\n";
    cout << "  " << setw(6) << a << " copies per operation, averaged across " << num_operations << " operations.\n";
  } else {
    cout << "  " << setw(6) << Record::comparisons << " comparisons performed in total.\n";
    cout << "  " << setw(6) << Record::assignments << " copies made in total.\n";
  }
}
    
void Record::printArray(Record arr[], int n) {
  if (n == 0) {
    cout << "[ ]\n";
  } else {
    cout << "[ " << arr[0];
    for (int i = 1; i < n; i++)
      cout << ", " << arr[i];
    cout << " ]\n";
  }
}

void Record::printSubarray(Record arr[], int first, int last) {
  if (last < first) {
    cout << "empty subarray\n";
  } else {
    cout << "subarray [ " << arr[first];
    for (int i = first+1; i <= last; i++)
      cout << ", " << arr[i];
    cout << " ]\n";
  }
}
    
bool Record::test_verify(const Record &y) const {
  return hidden_value == y.hidden_value;
}
