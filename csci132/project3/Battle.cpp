// Alexandra Chase
// amchas26@g.holycross.edu
// 20 February 2023
// CSCI 132 
// Prof. Fitzsimmons

// Battle.cpp is the implementation file that utilizes the Deck, Card,
// and ArrayStack programs to execute a game of Battle (aka War). In this
// program, the deck is shuffled, 

#include "Card.h"
#include "Deck.h"
#include "ArrayStack.h"
#include "StackInterface.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void awardPrizePile (int CCValue, int MCValue, ArrayStack<Card> *compWinPile, ArrayStack<Card> *myWinPile, ArrayStack<Card> *prizePile);
void battleRound (ArrayStack<Card> *compDrawPile, ArrayStack<Card> *compWinPile, ArrayStack<Card> *myDrawPile, ArrayStack<Card> *myWinPile, ArrayStack<Card> *prizePile);
bool check (ArrayStack<Card> *compDrawPile, ArrayStack<Card> *compWinPile, ArrayStack<Card> *myDrawPile, ArrayStack<Card> *myWinPile, ArrayStack<Card> *prizePile);
void transfer (ArrayStack<Card> *from, ArrayStack<Card> *to);


int main()
{   
// create stacks (draw and win) for user and computer, also create the prize stack
    Deck *theDeck = new Deck();
    ArrayStack<Card> *compDrawPile = new ArrayStack<Card> ();
    ArrayStack<Card> *compWinPile = new ArrayStack<Card> ();
    ArrayStack<Card> *myDrawPile = new ArrayStack<Card> ();
    ArrayStack<Card> *myWinPile = new ArrayStack<Card> ();
    ArrayStack<Card> *prizePile = new ArrayStack<Card> ();

// welcome statements and shuffle
    int cardsPerHand = 0;
    cout << "Welcome to Battle. \n";

    cout << "Shuffling Cards. \n";
    theDeck -> shuffle();

// check amount of cards
    cout << "How many cards in each hand (not more than 26)? ";
    cin >> cardsPerHand;

    while (cardsPerHand > 26 || cardsPerHand < 1) {
        if (cardsPerHand > 26) { // if too many cards
            cout << "That’s too many cards. Please enter a number less than 27: ";
        }

        if (cardsPerHand < 1) { // if too little cards
            cout << "Please enter a number greater than zero: ";
        }

        cin >> cardsPerHand;
    }

// dealing, computer first
    cout << "Dealing " << cardsPerHand << " cards to each player. \n";
    
    for (int numCards = 0; numCards< cardsPerHand; numCards++){
        Card compCard = theDeck -> dealCard();
        compDrawPile -> push(compCard);

        Card myCard = theDeck -> dealCard();
        myDrawPile -> push(myCard);
    }

    battleRound (compDrawPile, compWinPile, myDrawPile, myWinPile, prizePile);

    return 0;
}


void battleRound (ArrayStack<Card> *compDrawPile, ArrayStack<Card> *compWinPile, ArrayStack<Card> *myDrawPile, ArrayStack<Card> *myWinPile, ArrayStack<Card> *prizePile) {

    Card compCard;
    Card myCard;

    int CCValue;
    int MCValue;
    
    int roundCounter = 0;

    while (true) {

        roundCounter++;

        if (check(compDrawPile, compWinPile, myDrawPile, myWinPile, prizePile) == false) {
            return;
        }

        else {
            if (myDrawPile -> size() == 0 || compDrawPile -> size() == 0) {
                cout << "User replenishes draw pile using winnings: \n";
                transfer(myWinPile, myDrawPile);
                cout << "Computer replenishes draw pile using winnings: \n";
                transfer(compWinPile, compDrawPile);
            }
        }

        compCard = compDrawPile -> peek();
        myCard = myDrawPile -> peek();

        CCValue = compCard.getValue();
        MCValue = myCard.getValue();

        cout << "User has " << myDrawPile -> size() << " cards and draws " << myCard.toString() << ". \n";
        cout << "Computer has " << compDrawPile -> size() << " cards and draws " << compCard.toString() << ". \n";

        myDrawPile -> pop();
        compDrawPile -> pop();

        if (MCValue > CCValue) {
            myWinPile -> push(myCard);
            myWinPile -> push(compCard);
            awardPrizePile (CCValue, MCValue, compWinPile, myWinPile, prizePile); 
            cout << "User wins round " <<  roundCounter << ". \n";    
        }

        if (CCValue > MCValue) {
            compWinPile -> push(compCard);
            compWinPile -> push(myCard);
            awardPrizePile (CCValue, MCValue, compWinPile, myWinPile, prizePile);
            cout << "Computer wins round " <<  roundCounter << ". \n"; 
        }

        if (CCValue == MCValue) {
            prizePile -> push(myCard);
            prizePile -> push(compCard);
            cout << "Nobody wins round " << roundCounter << ". \n";
        }

        string response;
        cout << "Do you want to continue (y/n)? ";
        cin >> response;
        
        while (response != "y" && response != "n") {
            cout << "Invalid answer. Do you want to continue (y/n)? ";
            cin >> response;
        }

        if (response == "y") {
            continue;
        }

        if (response == "n") {

            int userTotal = myDrawPile -> size() + myWinPile -> size();
            int compTotal = compDrawPile -> size() + compWinPile -> size();

            if (userTotal > compTotal) {
                cout << "User has " << userTotal << " cards total. \n";
                cout << "Computer has " << compTotal << " cards total. \n";
                cout << "There are " << prizePile -> size() << " cards in the prize pile. \n";
                cout << "User wins! \n";
            }

            if (compTotal > userTotal) {
                cout << "User has " << userTotal << " cards total. \n";
                cout << "Computer has " << compTotal << " cards total. \n";
                cout << "There are " << prizePile -> size() << " cards in the prize pile. \n";
                cout << "Computer wins! \n";
            }
            
            if (compTotal == userTotal) {
                cout << "User has " << userTotal << " cards total. \n";
                cout << "Computer has " << compTotal << " cards total. \n";
                cout << "There are " << prizePile -> size() << " cards in the prize pile. \n";
                cout << "It's a tie! Nobody wins. \n";
            }

            return;
        }

    }
}

// deal with prizePile
void awardPrizePile (int CCValue, int MCValue, ArrayStack<Card> *compWinPile, ArrayStack<Card> *myWinPile, ArrayStack<Card> *prizePile) {
    if (!prizePile -> isEmpty()) {

        if (MCValue > CCValue) {
            while (!prizePile -> isEmpty()) {
                transfer(prizePile, myWinPile);
                //Card temp = prizePile -> peek();
                //prizePile -> pop();
                //myWinPile -> push(temp);
            }
        }

        if (CCValue > MCValue) {
            while (!prizePile -> isEmpty()) {
                transfer(prizePile, compWinPile);
                //Card temp = prizePile -> peek();
                //prizePile -> pop();
                //compWinPile -> push(temp);
            }
        }
    }
}


bool check (ArrayStack<Card> *compDrawPile, ArrayStack<Card> *compWinPile, ArrayStack<Card> *myDrawPile, ArrayStack<Card> *myWinPile, ArrayStack<Card> *prizePile) {

    
    if (compDrawPile -> isEmpty() && myDrawPile -> isEmpty()) {
        if (compWinPile -> isEmpty() && myWinPile -> isEmpty()) {
            cout << "User has 0 cards total. \n";
            cout << "Computer has 0 cards total. \n";
            cout << "There are " << prizePile -> size() << " cards in the prize pile. \n";
            cout << "Nobody wins! \n";
            return false;
        }
    }
    
    if (compDrawPile -> isEmpty()) {
        if (compWinPile -> isEmpty()) {
            int userTotal = myDrawPile -> size() + myWinPile -> size();
            cout << "User has " << userTotal << " cards total. \n";
            cout << "Computer has 0 cards total. \n";
            cout << "There are " << prizePile -> size() << " cards in the prize pile. \n";
            cout << "User wins! \n";
            return false;
        }
    }

    if (myDrawPile -> isEmpty()) {
        if (myWinPile -> isEmpty()) {
            int compTotal = compDrawPile -> size() + compWinPile -> size();
            cout << "Computer has " << compTotal << " cards total. \n";
            cout << "User has 0 cards total. \n";
            cout << "There are " << prizePile -> size() << " cards in the prize pile. \n";
            cout << "Computer wins! \n";
            return false;
        }
    }
    return true;
}

void transfer (ArrayStack<Card> *from, ArrayStack<Card> *to) {

    while (!from -> isEmpty()) {
        Card temp = from -> peek();
        cout << "Moving " << temp.toString() << "\n";
        from -> pop();
        to -> push(temp);
    }
}

    




