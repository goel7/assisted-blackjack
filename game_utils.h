#ifndef GAME_UTILS_H
#define GAME_UTILS_H

namespace Game {
    int getCardValue(int id);
    char getCardRank(int id);
    void printCard(int id);
    void printHand(int hand[], int size);
    int getScore(int hand[], int size);
}

#endif
