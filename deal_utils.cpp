#include "deal_utils.h"
#include "game_state.h"

#include <string>
#include <vector>
#include <iostream>
#include <cctype>

// anonymous namespace for helper functions
namespace {
    size_t nextCard(GameState& game) {
        return game.dealCard++;
    }

    int getCardValue(char rank, bool aceHigh) {
        if (std::isdigit(rank)) return rank - '0';
        else if (rank == 'A') return aceHigh ? 11 : 1;
        else return 10;
    }

    int getHandValue(const std::vector<std::string>& hand) {
        int handValue {0};

        for (size_t i {0}; i < hand.size(); ++i) {
            char card = hand[i][0];
            handValue += getCardValue(card, true);
        }

        return handValue;
    }
}

void dealInitialHands(GameState& game, const std::vector<std::string>& deck) {
    game.playerHands.push_back({deck[nextCard(game)], deck[nextCard(game)]});
    
    std::string upcard = deck[nextCard(game)];
    game.dealerUpcard = getCardValue(upcard[0], true);
    
    game.dealerHand.push_back(upcard);
    game.dealerHand.push_back(deck[nextCard(game)]);
}


// note: below code returns hand value for index 0.
// so in gamestate, if the first hand after splitting is finished,
// delete it from vector
int getPlayerTotal(GameState& game) {
    const std::vector<std::string> hand = game.playerHands[0];
    return getHandValue(hand);
}

// CODE BELOW FOR dealer total, for future purposes
int getDealerTotal(GameState& game) {
    const std::vector<std::string> hand = game.dealerHand;
    return getHandValue(hand);
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
}

void printDealerHand(GameState& game) {
    const std::vector<std::string> hand = game.dealerHand;
    std::cout << "Dealer hand: ";

    for (size_t i {0}; i < hand.size(); ++i) {
        std::cout << game.dealerHand[i];
    }
}
