#include "deck_utils.h"
#include "deal_utils.h"
#include "game_state.h"

#include <iostream>

/*
Note: for player actions, make them type:
h: hit
s: stand
x: split
d: double

This is for initial stage when game is played in terminal.
When moving to web interface, use buttons obviously.
*/

GameState game;

int main() {
    auto deck {Deck::getShuffledDeck()};
    dealInitialHands(game, deck);
    
    Deck::print(deck);
    
    printPlayerHand(game);
    std::cout << '\n';
    printDealerHand(game);

    
    /*
    Next part:
        - pass in dealer & player hands to decision engine
        - create auto and manual plays for player 
    */

    return 0;
}
