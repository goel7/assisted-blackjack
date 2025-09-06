#include "deal_utils.h"
#include "game_state.h"

#include <string>
#include <vector>
#include <iostream>

// anonymous namespace for helper functions
namespace {
    size_t nextCard(GameState& game) {
        return game.dealCard++;
    }
}

void dealInitialHands(GameState& game, const std::vector<std::string>& deck) {
    game.playerHands.push_back({deck[nextCard(game)], deck[nextCard(game)]});
    
    game.dealerHand.push_back(deck[nextCard(game)]);
    game.dealerHand.push_back(deck[nextCard(game)]);
}

void printPlayerHand(GameState& game) {
    const std::vector<std::vector<std::string>> hand = game.playerHands;
    std::cout << "Player hand(s): ";

    for (size_t i {0}; i < hand.size(); ++i) {
        for (size_t j {0}; j < hand[i].size(); ++j) {
            std::cout << game.playerHands[i][j];
        }
        std::cout << '\t';
    }
    
    std::cout << '\n';
}

void printDealerHand(GameState& game) {
    const std::vector<std::string> hand = game.dealerHand;
    std::cout << "Dealer hand: ";

    for (size_t i {0}; i < hand.size(); ++i) {
        std::cout << game.dealerHand[i];
    }
    
    std::cout << '\n';
}
