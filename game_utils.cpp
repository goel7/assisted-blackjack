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

    void printActionGuide() {
        std::cout << "Type for action:\n";
        std::cout << "* h: hit\n* s: stand\n* x: split\n";
        std::cout << "* d: double down\n* r: surrender\n";
        std::cout << "* p: see valid actions\n\n";
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
    
    // check if any hand is a non-bust hand for dealer actions
    bool anyNonBust(bool arr[], int arrSize) {
        for (int i {0}; i < arrSize; ++i) {
            if (!arr[i]) return true;
        }
        return false;
    }

    void printOutcome(
        int dealerHand[],
        int dealerHandSize,
        int playerHand[][12],
        int playerHandSize[],
        int numHands,
        bool split
    ) {
        for (int i {0}; i < numHands; ++i) {
            std::string playerRef = split ? "Hand " + std::to_string(i + 1) : "Player";
            
            int playerScore {Game::getScore(
                playerHand[i], 
                playerHandSize[i]
            )};

            int dealerScore {Game::getScore(
                dealerHand,
                dealerHandSize
            )};

            if (dealerScore > 21) {
                if (i == 0) std::cout << "Dealer busts.\n";
                std::cout << playerRef << " wins\n";
            }
            else if ((dealerScore > playerScore) || (playerScore > 21)) {
                std::cout << playerRef << " loses\n";
            }
            else if ((dealerScore < playerScore) && (playerScore <= 21)) {
                std::cout << playerRef << " wins\n";
            }
            else {
                std::cout << playerRef << " ties\n";
            }
        }
    }
}
