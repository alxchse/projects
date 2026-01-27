//  Created by Prof. Fitzsimmons
//  Edited by Alexandra Chase
//  07 February 2023
//  CSCI 132
//  Project 1
//  Player.h: The specification file for class Player. It declares all the methods and objects used
//  in the Yahtzee game. 



#ifndef PLAYER_H_
#define PLAYER_H_

#include "ArrayBag.h"
#include <string>

/** randInRange produces a pseudo-random integer between lo and hi,
 * inclusive. For example, randInRange(1, 100) may pick 1, 100, or
 * any number between them.
 * @precondition  lo <= hi
 * @return  A number r, such that lo <= r and r <= hi
 */
int randInRange(int lo, int hi);

class Player {
  public:
    Player(std::string name);
    void clearHand();
    void clearPrizes();
    void throwDice();
    void showHand();
    std::string getHand();
    int countPrizes();
    bool addPrize(std::string prize);
    std::string getName();
    void addGameWin();
    int getGamesWon();

  private:
    void computeHand();                   

    static const int NUM_DICE = 5;        // number of dice (const)
    ArrayBag<int> diceBag;                // bag to keep track of player's rolls
    ArrayBag<std::string> prizeBag;       // bag to keep track of player's prizes
    std::string hand;                     // hand the player won at the end of the round
    int gamesWon;                         // number of games player won
    std::string name;                     // player's name
};

#endif
