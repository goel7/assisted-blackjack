#include "deck_utils.h"
#include "random.h"

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <numeric>

namespace Deck {
    
    // anonymous namespace for helper functions
    namespace {
        void shuffleIndices(std::vector<int>& deck) {
            for (int i = static_cast<int>(deck.size()) - 1; i >= 1; --i) {
                int swapIndex {Random::get(0, i)};
                std::swap(deck[static_cast<std::size_t>(i)], 
                        deck[static_cast<std::size_t>(swapIndex)]);
            }
        }

        std::vector<std::string> makeShuffledDeck(
            const std::vector<std::string>& originalDeck,
            const std::vector<int>& shuffledIndices) 
        {
            std::vector<std::string> shuffledDeck;
            shuffledDeck.reserve(shuffledIndices.size());

            for (int i : shuffledIndices) 
            {
                shuffledDeck.push_back(originalDeck[static_cast<size_t>(i)]);
            }
            
            return shuffledDeck;
        }
    }

    // create master lookup table, this deck itself is never modified
    std::vector<std::string> initStr() {
        static const std::vector<std::string> deckStr = []() {
            std::vector<std::string> deck {};
            deck.reserve(52);
            
            const std::vector<std::string> ranks = {
                "2", "3", "4", "5", "6", "7", "8", 
                "9", "T", "J", "Q", "K", "A"
            };
            
            const std::vector<std::string> suits = {
                "♠", "♥", "♦", "♣"
            };

            for (const auto& rank : ranks) {
                for (const auto& suit : suits) {
                    deck.push_back(rank + suit);
                }
            }
            return deck;
        }();
        return deckStr;
    }

    /*
    create an ordered deck of indices. Can be modified (shuffled) 
    through shuffleIndices() function below
    */
    std::vector<int> initInt() {
        std::vector<int> deck(52);
        std::iota(deck.begin(), deck.end(), 0);
        return deck;
    }

    /*
    If you are using 6-8 decks, getShuffledDeck() should be called after 
    about 75% of the deck is used. Casinos generally reshuffle after 75-80%.
    For single deck games, perhaps shuffle every hand.
    */
    std::vector<std::string> getShuffledDeck() {
        auto indices {initInt()};
        shuffleIndices(indices);
        auto deck {initStr()};
        return makeShuffledDeck(deck, indices);
    }

    /*
    function below takes an int array, and uses it to print a "shuffled" 
    deck. Note that the actual cards deck is never modified. It's just
    printed by the shuffled index from deck argument.
    */
    void print(const std::vector<std::string>& deck) {
        int counter {0};
        
        for (const auto& card : deck) {
            ++counter;
            std::cout << card << "  ";
            
            // print newline every 10 cards
            if (counter % 10 == 0) {
                std::cout << '\n'; 
            }
        }

        // print newline at end as deck size not divisible by 10
        if (deck.size() % 10 != 0) {
            std::cout << '\n';
        }
    }

    /*
    function below shows frequency of unique cards (first in deck) to check 
    whether shuffle() function does a uniform shuffle with each deck
    permutation having equal probability
    */
    void histogram(int trials) {
        auto deckCards {initStr()};
        std::vector<int> indices {initInt()};
        std::unordered_map<std::string, int> counts;

        for (int i {1}; i <= trials; ++i) {
            indices = initInt(); // Reset indices every trial
            shuffleIndices(indices);
            
            // check first card, update frequency
            ++counts[deckCards[static_cast<size_t>(indices[0])]];
        }

        for (const auto& pair : counts) {
            std::cout << pair.first << " : " << pair.second << '\n';
        }
    }
}
