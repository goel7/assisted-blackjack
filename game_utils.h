#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <string_view>

namespace Game {
    int getCardValue(int id);
    char getCardRank(int id);
    
    void printActionGuide();
    void printCard(int id);
    void printHand(int hand[], int size);
    
    void printInitialHands(
        int dealerHand[], 
        int playerHand[], 
        int playerHandSize
    );

    int getScore(int hand[], int size);
    bool anyNonBust(bool arr[], int arrSize);
    
    void printOutcome(
        int dealerScore, 
        int playerScore, 
        std::string_view playerRef
    );
}

#endif
