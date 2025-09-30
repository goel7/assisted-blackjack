#ifndef ENTITY_ACTIONS_H
#define ENTITY_ACTIONS_H

void runPlayerTurn(
    int playerHand[][12],
    int playerHandSize[],
    int& nextCard,
    const int cards[],
    int& numHands,
    int& onHand,
    bool& split,
    bool bustArr[],
    int& bankroll,
    int& betSize
);

void runDealerActions(
    int dealerHand[],
    int& dealerHandSize, 
    int cards[], 
    int& nextCard
);

#endif
