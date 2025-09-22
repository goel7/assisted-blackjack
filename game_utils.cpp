#include "game_utils.h"
#include "deck_utils.h"

#include <iostream>

namespace Game {
    int getCardValue(int id) {
        return value[id % 13];
    }

    char getCardRank(int id) {
        return type[id % 13][0];
    }

    void printCard(int id) {
        int rank {id % 13};
        int s {id / 13};
        std::cout << type[rank] << suit[s];
    }

    void printHand(int hand[], int size) {
        for (int i {0}; i < size; ++i) {
            printCard(hand[i]);
            std::cout << " ";
        }
    }

    int getScore(int hand[], int size) {
        int total {0};
        int aces {0};

        for (int i {0}; i < size; ++i) {
            int cardVal {getCardValue(hand[i])};
            total += cardVal;

            if (cardVal == 11) ++aces;
        }

        while (total > 21 && aces > 0) {
            total -= 10;
            --aces;
        }

        return total;
    }

    void printActionGuide() {
        std::cout << "Type for action:\n";
        std::cout << "* h: hit\n* s: stand\n* x: split\n";
        std::cout << "* d: double down\n* r: surrender\n";
        std::cout << "* p: see valid actions\n\n";
    }

    void printInitialHands(
        int dealerHand[], 
        int playerHand[], 
        int playerHandSize
    ) {
        std::cout << "Dealer: ? ";
        Game::printCard(dealerHand[1]);
        std::cout << '\n';

        std::cout << "Player: ";
        Game::printHand(playerHand, playerHandSize);
        std::cout << '\n';
    }
}
