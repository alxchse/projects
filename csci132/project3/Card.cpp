// Implementation of Card class.
// Author: CSCI 132 Instructors
// Date: Fall 2020 
// Modified:
//  23 Feb 2021 - K. Walsh - Reformatted and added comments. Removed unnecessary
//       includes and namespace lines. Added new toString() method, and renamed
//       or removed some other methods.

#include "Card.h"
#include <iostream>
#include <cassert>

using namespace std;

const std::string Card::suitDescriptions[] = {
  "Clubs", "Diamonds", "Hearts", "Spades"
};

const std::string Card::valueDescriptions[] = {
  "Ace", "Two", "Three", "Four",
  "Five", "Six", "Seven", "Eight",
  "Nine", "Ten", "Jack", "Queen", "King"
};

Card::Card() {
  value = ACE;
  suit = CLUBS;
}

Card::Card(CardValue initValue, CardSuit initSuit) {
  assert(ACE <= initValue && initValue <= KING);
  assert(CLUBS <= initSuit && initSuit <= SPADES);
  value = initValue;
  suit = initSuit;
}
  
CardValue Card::getValue() const {
  return value;
}

CardSuit Card::getSuit() const {
  return suit;
}

void Card::printValue() const {
  int i = value - ACE;
  cout << valueDescriptions[i];
}

void Card::printSuit() const {
  int j = suit - CLUBS;
  cout << suitDescriptions[j];
}

void Card::printCard() const {
  cout << toString();
}

std::string Card::toString() const {
  int i = value - ACE;
  string v = valueDescriptions[i];
  int j = suit - CLUBS;
  string s = suitDescriptions[j];
  return v + " of " + s;
}

