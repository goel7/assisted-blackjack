#include "deck_utils.h"
#include "deal_utils.h"
#include "game_state.h"

#include <iostream>

GameState game;

int main() {
    auto deck {Deck::getShuffledDeck()};
    dealInitialHands(game, deck);
    
    Deck::print(deck);
    printPlayerHand(game);
    printDealerHand(game);

    return 0;
}
