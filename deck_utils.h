#ifndef DECK_UTILS_H
#define DECK_UTILS_H

inline const char* suit[4] = {
    "\U00002665", 
    "\U00002660", 
    "\U00002666", 
    "\U00002663"
}; // H, S, D, C

inline const char* type[13] = {
    "2", "3", "4", "5", "6", "7", "8", 
    "9", "T", "J", "Q", "K", "A"
};

inline const int value[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

namespace Deck {
    void shuffle(int cards[]);
    void printIds(int cards[]);
    void print(int cards[]);
    void histogram(int cards[], int trials);
}

#endif
