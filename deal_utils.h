#ifndef DEAL_UTILS_H
#define DEAL_UTILS_H

#include "game_state.h"

#include <vector>
#include <string>

void dealInitialHands(GameState& game, const std::vector<std::string>& deck);

void printPlayerHand(GameState& game);
void printDealerHand(GameState& game);


#endif
