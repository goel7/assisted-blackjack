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
    int upcard = game.dealerUpcard;

    printDealerHand(game);
    std::cout << '\n';
    printPlayerHand(game);
    std::cout << '\n';

    std::cout << getDealerTotal(game) << " " << getPlayerTotal(game) << '\n';
    std::cout << upcard;

    return 0;
}
