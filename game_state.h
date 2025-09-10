#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>

struct GameState {
    size_t dealCard {0};

    int dealerUpcard;
    std::vector<std::string> dealerHand; // with suit, for display
    std::vector<int> dealerCardValues; // no suit, for backend

    std::vector<std::vector<std::string>> playerHands; // with suit, for display
    
    // imo, just create new function, and manually calc values.
    // std::vector<std::vector<int>> playerCardValues; // no suit, for backend
};

#endif
