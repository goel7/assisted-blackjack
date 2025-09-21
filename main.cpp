#include "deck_utils.h"
#include "game_utils.h"

#include <iostream>

/*
Note: for player actions, make them type:
h: hit
s: stand
x: split
d: double
r: surrender

This is for initial stage when game is played in terminal.
When moving to web interface, use buttons obviously.
*/

int main() {
    int cards[52];
    Deck::shuffle(cards);
    Deck::printIds(cards);
    Deck::print(cards);
    int nextCard {0}; // index for next card to be dealt

    // initialize gameplay
    int dealerHand[12];
    int playerHand[12];

    playerHand[0] = cards[nextCard++];
    dealerHand[0] = cards[nextCard++];
    playerHand[1] = cards[nextCard++];
    dealerHand[1] = cards[nextCard++];

    int playerHandSize = 2;
    // int playerScore {Game::getScore(playerHand, playerHandSize)};


    // Display initial output
    std::cout << "Dealer: ? ";
    Game::printCard(dealerHand[1]);
    std::cout << '\n';

    std::cout << "Player: ";
    Game::printHand(playerHand, playerHandSize);
    std::cout << '\n';

    Deck::print(cards);

    return 0;
}

/*
Next steps:
- Create matrix (2d array) for player hands to allow splitting
- Handle player splitting, hitting on all hands, etc.
- Introduce betting later.
*/
