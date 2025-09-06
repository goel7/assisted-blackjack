#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>

struct GameState {
    size_t dealCard {0};
    std::vector<std::string> dealerHand;
    std::vector<std::vector<std::string>> playerHands;
};

#endif
