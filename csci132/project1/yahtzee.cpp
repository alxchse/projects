// yahtzee.cpp
// author: CSCI 132 Instructor
// date: Spring 2018
// revisisons:
//   K. Walsh, 28 July 2020 - modernize code to go with new textbook
//   K. Walsh, 25 January 2021 - rewrite as Yahtzee-like game instead of Dice Poker
//   Z. Fitzsimmons, 31 January 2023 - minor style updates
//
// This program simulates a simplified and modified "Yahtzee"-like game between
// two players. The program first prompts the user to input the names of the
// players and how many rounds the game should last. It then simulates the game,
// which consists of multiple rounds of rolling dice and awarding prizes. The
// simulated game ends after the requested number of rounds.
// After the game, the winner is printed, and the user is asked whether to run
// another simulation.

#include "Player.h"
#include <iostream>

using namespace std;

void playRound(Player &p);
void printRoundWinners(Player &onePlayer, Player &anotherPlayer);
void printGameWinner(Player &onePlayer, Player &anotherPlayer);

int main(void) {
  // prompt user for player names
  string name1, name2;
  cout << "Enter a name for the first player (no spaces): ";
  cin >> name1;
  cout << "First player name will be " << name1 << ".\n";
  cout << "Enter a name for the second player (no spaces): ";
  cin >> name2;
  cout << "Second player name will be " << name2 << ".\n";

  // set up game variables
  char keepPlaying = 'y'; // whether user wants to simulate again
  Player player1(name1);  // first simulated player
  Player player2(name2);  // second simulated player

  while (keepPlaying == 'y' || keepPlaying == 'Y') {

    // reset the player game state
    player1.clearPrizes();
    player2.clearPrizes();

    // prompt user for number of rounds
    int numRounds;
    cout << "How many rounds would you like this game to be? ";
    cin >> numRounds;
    cout << "Simulated game will run for at most " << numRounds << " rounds.\n";
    cout << "\n";

    // simulate that many rounds
    for (int i = 1; i <= numRounds; i++ ) {
      cout << "Round #" << i << ":\n";
      playRound(player1);
      playRound(player2);
      printRoundWinners(player1, player2);
    }  // end for each round

    // compute and print overall game winner
    cout << "Game Results: ";
    printGameWinner(player1, player2);

    // ask if user wants to run the simulation again
    cout << "Would you like to run another simulation [y/n]? ";
    cin >> keepPlaying;
    cout << "You answered '" << keepPlaying << "'.\n";
  }  // end while the user wants to simulate another game

  cout << "Thank you for playing Yahtzee!\n";
  return 0;
}  // end main

/** playRound simulates one round dice rolling for one player, and prints the
 results to standard output.
 @postcondition the player's rank is set according to the dice roll */
void playRound(Player &p) {
      p.clearHand();
      cout << p.getName() << " rolls: ";
      p.throwDice();
      cout << "... ";
      p.showHand();
      cout << "\n";
}  // end playRound

/** printRoundWinners computes the winner of a round, prints the result to
 standard output (along with one blank line), and updates the player's scores.
 @precondition both player's ranks have already been set according to a fresh
    roll of their dice
 @postcondition one player's score is incremented */
void printRoundWinners(Player &onePlayer, Player &anotherPlayer) {
  std::string prize1 = onePlayer.getHand();
  std::string prize2 = anotherPlayer.getHand();
  if (prize1 == prize2) {
    cout << "It's a tie! Nobody gets a prize this round.\n";
  } else {
    if (onePlayer.addPrize(prize1))
    {
      cout << onePlayer.getName() << " earns and accepts the \"" << prize1 << "\" prize!\n";
    }
    if (anotherPlayer.addPrize(prize2))
    {
      cout << anotherPlayer.getName() << " earns and accepts the \"" << prize2 << "\" prize!\n";
    }
  }
  cout << "\n";
}  // end pringRoundWinner

/** printGameWinner computes the winner of an entire game, and prints the result
 to standard output.
 @precondition all the rounds have been played and the player's scores are updated.
 */
void printGameWinner(Player &onePlayer, Player &anotherPlayer) {
  cout << onePlayer.getName() << " has won " << onePlayer.countPrizes() << " prizes, and "
    << anotherPlayer.getName() << " has won " << anotherPlayer.countPrizes() << " prizes.\n";
  if (onePlayer.countPrizes() > anotherPlayer.countPrizes()) {
    cout << onePlayer.getName() << " has more prizes and wins the game!\n";
    onePlayer.addGameWin();
  } else if (anotherPlayer.countPrizes() > onePlayer.countPrizes()) {
    cout << anotherPlayer.getName() << " has more prizes and wins the game!\n";
    anotherPlayer.addGameWin();
  } else {
    cout << "The game is a tie!\n";
  }
  cout << "That makes " << onePlayer.getGamesWon() << " wins for " << onePlayer.getName()
    << " and " << anotherPlayer.getGamesWon() << " wins for " << anotherPlayer.getName() << ".\n";
}  // end printGameWinner
