// Specification of Card class and related types to represent a single playing card.
// Author: CSCI 132 Instructors
// Date: Fall 2020 
// Modified:
//  23 Feb 2021 - K. Walsh - Reformatted and added comments. Removed unnecessary
//       includes and namespace lines. Added new toString() method, and renamed
//       or removed some other methods.

#ifndef CARD_
#define CARD_

#include <string>

// CardSuit is a data type representing the possible suits. You can mostly treat
// CardSuit just like 'int', and can treat the values (CLUBS, DIAMONDS, etc.)
// just like constants, each having a different integer value. The value of the
// suits is not very meaningful, but it is sequential starting with CLUBS,
// counting up to SPADES.
enum CardSuit { CLUBS = 1, DIAMONDS, HEARTS, SPADES };

// CardValue is a data type representing the possible suits. You can mostly
// treat CardValue just like 'int', and can treat the values (Ace, Two, etc.)
// just like constants, each having a different integer value. The actual
// numerical value of the cards is as you would expect, with Ace equal to 1,
// Two equal to 2, Queen equal to 12, and so on.
enum CardValue { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
                 EIGHT, NINE, TEN, JACK, QUEEN, KING };

// A Card object represents a single playing card. Card objects are
// immutable: none of the methods modify the object in any way.
class Card {
  
  public:

    // Construct a single new "Ace of Clubs" card.
    Card();

    // Construct a single new card with the given value and suit.
    Card(CardValue value, CardSuit suit); 

    // Get the value of this card.
    CardValue getValue() const;

    // Get the suit of this card.
    CardSuit getSuit() const;  

    // Print the value of this card to standard output.
    void printValue() const;

    // Print the suit of this card to standard output.
    void printSuit() const;

    // Print a description of this card to standard output.
    void printCard() const;

    // Get a description of this card.
    std::string toString() const;

    // void setValue(CardValue newValue);
    // void setSuit(CardSuit newSuit);

  private:
    CardValue value;
    CardSuit suit;

    // Note: these must go in the same order as the CardSuit enum, above.
    static const std::string suitDescriptions[];

    // Note: these must go in the same order as the CardSuit enum, above.
    static const std::string valueDescriptions[];

};
#endif
