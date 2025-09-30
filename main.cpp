#include "deck_utils.h"
#include "game_utils.h"
#include "entity_actions.h"

#include <iostream>

int getBankroll() {
    int bankroll {};
    std::cout << "Enter buy-in: ";
    std::cin >> bankroll;

    return bankroll;
}

int getBetAmount() {
    int betSize {};
    std::cout << "Enter bet: ";
    std::cin >> betSize;

    return betSize;
}

int main() {
    int cards[52];
    Game::printActionGuide();

    int bankroll {getBankroll()};
    
    while (true) {
        // Ask bet amount
        int betSize {getBetAmount()};

        Deck::shuffle(cards);
        int nextCard {0}; // index for next card to be dealt

        // initialize hands
        int playerHand[4][12];
        int dealerHand[12];
        playerHand[0][0] = cards[nextCard++];
        dealerHand[0] = cards[nextCard++];
        playerHand[0][1] = cards[nextCard++];
        dealerHand[1] = cards[nextCard++];

        int playerHandSize[4] = {2};
        int dealerHandSize {2};

        // Display initial output
        Game::printInitialHands(dealerHand, playerHand[0], playerHandSize[0]);
        
        int numHands {1};
        int onHand {0}; // index of player hand being currently played (due to splits)

        bool split {false}; // to decide Action output statements
        bool bustArr[4] = {};

        runPlayerTurn(
            playerHand,
            playerHandSize,
            nextCard,
            cards,
            numHands,
            onHand,
            split,
            bustArr,
            bankroll,
            betSize
        );

        if ((!split && !bustArr[0]) || (split && Game::anyNonBust(bustArr, numHands))) {
            runDealerActions(dealerHand, dealerHandSize, cards, nextCard);

            Game::printOutcome(
                dealerHand,
                dealerHandSize,
                playerHand,
                playerHandSize,
                numHands,
                split,
                bankroll,
                betSize
            );
        }
    }
    

    return 0;
}

/*
Next:
- Fix edge case of splitting Aces

After the whole blackjack is running:
- Add bets
- Show bankroll after every hand
- Develop double down function and surrender function

After all this is done, blackjack has been finished.
Next steps:
- Make decision_engine.cpp
- Pass in player and dealer hands
- Show optimal decision
- Compare player decision with optimal decision

Afterwards:
- Deploy to web using JSON or whatever
*/
