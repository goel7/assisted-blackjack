#include "game_utils.h"
#include "deck_utils.h"

#include <iostream>

namespace Game {
    int getCardValue(int id) {
        return value[id % 13];
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
}
