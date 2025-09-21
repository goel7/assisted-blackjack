#ifndef GAME_UTILS_H
#define GAME_UTILS_H

namespace Game {
    void printCard(int id);
    void printHand(int hand[], int size);
    int getScore(int hand[], int size);
    int getCardValue(int id);
}

#endif
