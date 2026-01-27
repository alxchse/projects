// Specification of Deck class to store a deck of playing cards.
// Author: CSCI 132 Instructors
// Date: Fall 2020 
// Modified:
//  23 Feb 2021 - K. Walsh - Reformatted comments.
//       Implement using Stack instead of array. Change shuffle behavior
//       so it must be called multiple times. Add and rename methods.

#ifndef DECK_
#define DECK_

#include "Card.h"
#include "StackInterface.h"

// A Deck object represents a standard pack of 52 playing cards.
class Deck {

  public:

    // Construct a fresh deck of 52 cards. The cards will NOT be shuffled, but
    // are not guaranteed to be in any specific order either.
    Deck();

    // Destructor, frees any allocated memory.
    ~Deck();

    // Shuffle the cards in the deck, randomizing their order.
    // This function simulates the effect of seven "riffle Shuffle" operations.
    // Preconditions:
    //   Clients should call srand(x) once, near the start of your program,
    //   with any desired integer x, to seed the random number generator.
    void shuffle();
    

    // Remove one card from the top of the deck.
    // Returns:
    //   The card that was removed.
    // Precondition:
    //   The deck is not empty.
    // Postcondition:
    //   One card has been removed from the deck.
    Card dealCard();

    // Check if the deck is empty.
    // Returns:
    //   true if the deck has no cards left, and
    //   false otherwise.
    bool isEmpty() const;

  private:
    // Internally, a stack is used to hold the cards.
    StackInterface<Card> *pile;

    // Pick a pseudo-random number in the range lo to hi, inclusive.
    // Precondition:
    //   lo <= hi, and (hi - lo) is a moderatly small number.
    // Note:
    //   The underlying pseudo-random number generator, rand(), is terrible.
    //   It will often generate very predictable, repating sequences, and
    //   typically generates the same numbers every time the program runs.
    //   See documentation for srand() to learn how to change this behavior,
    //   but most programs should simply use a better random number generator.
    int randInRange(int lo, int hi);
};

#endif
