// Alexandra Chase
// CSCI 132 Prof. Fitzsimmons
// 07 February 2023
// Project 1
// player.cpp: This is the implementation code for the Player class. It pertains to all methods relating to the 
// player in Yahtzee. This includes rolling the dice, calculating scores, and earning prizes.

#include "Player.h"
#include <cstdlib> // for rand()
#include "ArrayBag.h"
#include <iostream>

Player::Player(std::string name1) {

// initialize  variables
    gamesWon = 0;               // number of games Player has won
    name = name1;               // player's name
} // end initialization
  
void Player::clearHand() {
// preconditions: none 
// postconditions: clears all values array bag diceBag
  diceBag.clear();
} // end clearHand

void Player::clearPrizes() {
// preconditions: none
// postconditions: clears all values in array bag prizeBag
  prizeBag.clear();
} // end clearPrizes

void Player::throwDice() {
// preconditions: none
// postconditions: uses randInRange() to pick a number between 1 and 6 for a dice roll
// and adds that value to the player's diceBag
int roll = 0;


  for (int i = 0; i < 5; i++) {
    roll = randInRange(1,6);
    bool added = diceBag.add(roll);

    if (!added)
      std::cout << "Could not add" << roll << "\n";
    else
      std::cout << roll << " ";
  } 
  std::cout << "\n";

computeHand();

} // end throwDice

void Player::showHand() {
  // preconditions: none
  // postconditions: shows the player's hand and prize
  std::cout << hand;
} // end showHand

std::string Player::getHand() {
  // preconditions: none
  // postconditions: returns the player's hand
  return hand;
} // end getHand
  
int Player::countPrizes() {
  // preconditions: none
  // postconditions: counts how many prizes are in a players prize bag
  int numPrizes = prizeBag.getCurrentSize();
  return numPrizes;
} // end countPrizes

bool Player::addPrize(std::string prize) {
  // preconditions: ensures the prize doesnt already exist
  // in that player's prize bag
  if (prizeBag.contains(prize))
    return false;

  // postconditions: adds prize to prize bag
  prizeBag.add(prize);
  return true;
} // end addPrize

void Player::addGameWin() {
  // preconditions: none
  // postconditions: add a win to the count of total wins the players obtained so far
  gamesWon++;
} // end addGameWin

int Player::getGamesWon() {
  // preconditions: none
  // postconditions: return the amount of wins a player has obtained so far
  return gamesWon;
} // end getGamesWon

void Player::computeHand() {
  // preconditions: none
  // postconditions: gets two highest frequencies of each number rolled in the round,
  // and compares them to see which prize the player receives 
  int freq = 0; 
  int maxLoc = 0;
  int max = 0;
  int max2 = 0;

  for (int i = 1; i < 7; i++) {
    freq = diceBag.getFrequencyOf(i);

    if (freq > max){
      max = freq;
      maxLoc = i;
    }
  }

  for(int i = 1; i < 7; i++){
    freq = diceBag.getFrequencyOf(i);
    if (i != maxLoc && freq > max2)
      max2 = freq;
  }
  
    std::cout << max << " and " << max2;

    if (max == 5){
      hand = "Five of a Kind";
    } else if (max == 4) {
      hand = "Four of a Kind";
    } else if (max == 3 && max2 == 2) {
      hand = "Full House";
    } else if (max == 3 && max2 == 1) {
      hand = "Three of a Kind";
    } else if (max == 2 && max2 == 2) {
      hand = "Two Pairs";
    } else if (max == 2 && max2 == 1) {
      hand = "One Pair";
    } else if (max == 1 && max2 == 1) {
      hand = "Assortment";
    }
} // end computeHand

std::string Player::getName() {
  // preconditions: none
  // postconditions: returns the player's name
  return name;
} // end getName

int randInRange(int lo, int hi) {
  // preconditions: none
  // postconditions: returns a random number 1-6 for each roll
  double v = (double)rand();    // 0 <= v && v <= RAND_MAX
  double f = v / ((double)RAND_MAX+1);  // 0 <= f && f < 1.0
  return lo + (int)(f * (hi - lo + 1));
}  // end randInRange
