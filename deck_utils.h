#ifndef DECK_UTILS_H
#define DECK_UTILS_H

#include <vector>
#include <string>
#include <iostream>


namespace Deck {
    std::vector<std::string> initStr();
    std::vector<int> initInt();
    
    std::vector<std::string> getShuffledDeck();
    
    void print(const std::vector<std::string>& deck);
    void histogram(int trials);
}

#endif
