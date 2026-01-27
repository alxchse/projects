// Alexandra Chase
// amchas26@g.holycross.edu
// CSCI 132 Prof. Fitzsimmons
// 15 Febraury 2023
//
// wordPop.cpp is the implementation file that runs
// through a given file (papers.lst) and prints the most popular word from
// each year (1967 - 2007). It also prints a table with each popular word and displays
// the number of times that word appears in said file per year.  


#include "ArrayBag.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// A list of common punctuation characters that might separate words in a title.
const string PUNCTUATION = " ,:;\t.()&";

// most of the papers are from 1967 - 2007, a 41-year span
const int OLDEST = 1967;
const int NEWEST = 2007;

int main()
{
  ifstream data;
  data.open("papers.lst");
  if (!data) {
    cout << "Sorry, could not open file: papers.lst\n";
    return 1;
  }

  ArrayBag<string> *wordsByYear = new ArrayBag<string>[41]; // ArrayBag filled with pointers corresponding to each year & pointing to a bag of words

    // get year file is from
    while (true) {
      int year;
      data >> year;
        if (!data)
          break;

    // get author of file
    string authors;
    getline(data, authors, ',');
    if (!data)
      break;

    // get title of file
    string title;
    getline(data, title);
    if (!data)
      break;

    // ignore papers outside the range OLDEST to NEWEST
    if (year < OLDEST || year > NEWEST)
      continue;

    // ignore papers if the arraybag is already full
    if (wordsByYear[year - OLDEST].isFull())
      continue;

    bool moreWords = true;
    while (moreWords) {
      size_t pos = title.find_first_of(PUNCTUATION);
      string word;
      if (pos == string::npos) {
        word = title;
        moreWords = false;
      } else {
        word = title.substr(0, pos);
        title.erase(0, pos+1);
      }

      // ignore short words, like "A", or "the", which are mostly boring
      if (word.length() < 5)
        continue;

      // process word
      if (!wordsByYear[year - OLDEST].add(word)) {
        cout << "Oops, ArrayBag is now full.\n";
        break;
      }
    }
  }

  // Print frequency of each word, taking care to only print each word
  // (and frequency) once. That way, if "Machine" appears say 3 times
  // in the ArrayBag, we print "3 Machine", but we only print this the
  // first time that "Machine" is encountered in the ArrayBag. It
  // would be silly to print that three times!
  //
  // NOTE: This code should be changed to instead print the most popular words
  // by each year.

  // ArrayBag<string> printed; // this bag keeps track of words already printed

  ArrayBag<string> popWords;                                // arraybag filled with popular words corresponding to each year
  string popWord = "hi";                                    // holds most popular word for that year
  string word;                                              // holds word from file
  
  for (int i = 0; i < 41; i++) {
    int n = wordsByYear[i].getCurrentSize();                // number of words per year
    int maxFreq = 0;                                        // holds freq of most used word so far
    int count = 0;                                          // frequency of that word
    for (int j = 0; j < n; j++) {
      word = wordsByYear[i].get(j);                         // retrieves word from wordsByYear arrayBag
      count = wordsByYear[i].getFrequencyOf(word);          // frequency of that word

      if (count > maxFreq) {  
        popWord = word;                                     // change most popular word to that word
        maxFreq = count;                                    // change highest frequency count to the freq of that word
      }
    }
    popWords.add(popWord);                                  // add most popular word to bag of most popular words
    cout << "Most popular word for " << i + OLDEST << " is " << popWord << ", which appeared "
    << maxFreq << " times, among " << n << "  total words for that year. \n";
  }
  // return 0;

  // start of table

  ArrayBag<string> newPopWords;                             // new arraybag of popular words WITHOUT DUPLICATES
  string newWord;                                           // variable to hold a word
  cout << "YEAR";
  for (int i = 0; i < popWords.getCurrentSize(); i++) {     // loop iterating though each popular word
    newWord = popWords.get(i);                              // initiate word holder variable to a pop word
    if (newPopWords.contains(newWord)) {                    // if the new arraybag already has that word, skip to next word
      continue; 
    } else {
      newPopWords.add(newWord);                             // otherwise add to new arraybag
      cout << right << setw(12) << newWord;                 // prints out popular words from new arraybag
    }
  }
  cout << "\n";
  for (int i = 0; i < NEWEST - OLDEST; i++) {               // loops through every year 1967 - 2007
    int year = i + OLDEST;                                  // gets year and prints it
    cout << year;
    for (int j = 0; j < newPopWords.getCurrentSize(); j++){ // loop iterating through each popular word
      newWord = newPopWords.get(j);                         // gets frequency of that popular word and prints it
      cout << "     " << wordsByYear[i].getFrequencyOf(newWord) << "     ";
    }
  cout << "\n";
  }
  return 0;                                                 // returns 0 when finished successfully
}

