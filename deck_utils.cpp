#include "random.h"
#include "deck_utils.h"
#include "game_utils.h"

#include <utility> // for std::swap
#include <numeric> // for std::iota
#include <iostream>

// global deck variables
const int numCards = 52;

namespace Deck {
    // Reinitialize and shuffle using Fisher-Yates
    void shuffle(int cards[]) {
        std::iota(cards, cards + 52, 0);

        for (int i {numCards - 1}; i >= 1; --i) {
            std::swap(cards[i], cards[Random::get(0, i)]);
        }
    }

    void printIds(int cards[]) {
        for (int i {0}; i < numCards; ++i) {
            std::cout << cards[i] << " ";
            if ((i + 1) % 10 == 0) std::cout << '\n';
        }
        
        if (numCards % 10 != 0) std::cout << '\n';
    }

    void print(int cards[]) {
        for (int i {0}; i < numCards; ++i)
        {
            Game::printCard(cards[i]);
            std::cout << " ";
            if ((i + 1) % 10 == 0) std::cout << '\n';
        }
        
        if (numCards % 10 != 0) std::cout << '\n';
    }

    // print Histogram counter to check if shuffle is effective
    void histogram(int cards[], int trials) {
        std::unordered_map<int, int> counts;

        for (int i {0}; i < trials; ++i) {
            shuffle(cards);
            ++counts[cards[0]];
        }

        for (const auto& pair : counts) {
            std::cout << pair.first << " : " << pair.second << '\n';
        }
    }
}
