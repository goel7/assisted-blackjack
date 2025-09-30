#include "entity_actions.h"
#include "game_utils.h"
#include "deck_utils.h"

#include <iostream>

namespace {
    void hitHand(
        int hand[], 
        int& handSize, 
        const int cards[], 
        int& nextCard
    ) {
        hand[handSize++] = cards[nextCard++];
    }

    bool splitAllowed(int hand[], int handSize, int numHands) {
        bool pair {Game::getCardRank(hand[0]) == Game::getCardRank(hand[1])};
        if (pair && handSize == 2 && numHands < 4) {
            return true;
        }
        return false;
    }

    void printPlayerHand(int hand[], int handSize) {
        std::cout << "Player: ";
        Game::printHand(hand, handSize);
        std::cout << '\n';
    }

    void printAllPlayerHands(
        int i, 
        int numHands, 
        int playerHand[][12], 
        int playerHandSize[]
    ) {
        for (int j {i}; j < numHands; ++j) {
            std::cout << "Hand " << j + 1 << ": ";
            Game::printHand(playerHand[j], playerHandSize[j]);
            std::cout << '\n';
        }
    }

    char actionStmt(bool split, int onHand) {
        char action {};

        if (!split) std::cout << "Action: ";
        else {
            std::cout << "Action (Hand " << onHand + 1 << "): ";
        }

        std::cin >> action;
        return action;
    }
}

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
) {
    for (int i {0}; i < numHands; ++i) {
        int playerScore {Game::getScore(playerHand[i], playerHandSize[i])};
        bool stand {false};

        if (i > 0) {
            hitHand(
                playerHand[onHand], 
                playerHandSize[onHand], 
                cards, 
                nextCard
            );

            printPlayerHand(playerHand[onHand], playerHandSize[onHand]);
            playerScore = Game::getScore(playerHand[onHand], playerHandSize[onHand]);
        }

        if (playerScore == 21) {
            if (playerHandSize[onHand] == 2) {
                std::cout << "Player got blackjack!\n";
                bankroll += betSize;
            } 
            else {
                std::cout << "Player got 21!\n";
                bankroll += betSize;
            }

            if (split && i < numHands - 1) {
                std::cout << "Move on to next hand.\n";
            }

            continue;
        }

        while (!stand && !bustArr[i] && playerScore != 21) {

            // Get player action
            char action {actionStmt(split, onHand)};

            bool canSplit {splitAllowed(
                playerHand[onHand], 
                playerHandSize[onHand], 
                numHands
            )};

            // Handle standing:
            if (action == 's') {
                stand = true;
                
                std::cout 
                    << "Player stood at " 
                    << Game::getScore(playerHand[i], playerHandSize[i]) 
                    << ".\n";
                    
                if (split && i < numHands - 1) {
                    std::cout << "Move on to next hand.\n";
                }
                onHand++;
            }
            
            // Handle hitting:
            else if (action == 'h') {
                hitHand(
                    playerHand[onHand], 
                    playerHandSize[onHand], 
                    cards, 
                    nextCard
                );
                printPlayerHand(playerHand[onHand], playerHandSize[onHand]);
            }

            // Handle splitting:
            else if (canSplit && action == 'x') {
                playerHand[numHands++][0] = playerHand[onHand][1];

                --playerHandSize[onHand];
                ++playerHandSize[numHands - 1];

                split = true;

                hitHand(
                    playerHand[onHand], 
                    playerHandSize[onHand], 
                    cards, 
                    nextCard
                );

                printAllPlayerHands(i, numHands, playerHand, playerHandSize);
            }

            // Handle double down:
            else if (action == 'd') {
                betSize *= 2;
                
                hitHand(
                    playerHand[onHand], 
                    playerHandSize[onHand], 
                    cards, 
                    nextCard
                );
                printPlayerHand(playerHand[onHand], playerHandSize[onHand]);
            }

            // Handle surrender:
            else if (action == 'r') {
                ;
            }

            playerScore = Game::getScore(playerHand[onHand], playerHandSize[onHand]);
            
            if (playerScore > 21) {
                bustArr[i] = true;
                if (split) {
                    std::cout << "Player (Hand " << onHand + 1 << ") busted.\n";
                    bankroll -= betSize;
                }
                else {
                    std::cout << "Player busted.\n";
                    bankroll -= betSize;
                }

                if (split && i < numHands - 1) {
                    std::cout << "Move on to next hand.\n";
                }

                onHand++;
            }

            else if (playerScore == 21) {
                if (playerHandSize[onHand] == 2) {
                    std::cout << "Player got blackjack.\n";
                    bankroll += betSize;
                }
                else {
                    std::cout << "Player got 21.\n";
                    bankroll += betSize;
                }
                
                
                if (split && i < numHands - 1) {
                    std::cout << "Move on to next hand.\n";
                }
                onHand++;
            }
        }
    }
}

void runDealerActions(
    int dealerHand[],
    int& dealerHandSize, 
    int cards[], 
    int& nextCard
) {
    std::cout << "Dealer: ";
    Game::printHand(dealerHand, dealerHandSize);
    std::cout << '\n';

    int dealerScore {Game::getScore(dealerHand, dealerHandSize)};

    while (dealerScore <= 16) {
        hitHand(dealerHand, dealerHandSize, cards, nextCard);
        dealerScore = Game::getScore(dealerHand, dealerHandSize);
    }

    if (dealerHandSize > 2) {
        std::cout << "Dealer: ";
        Game::printHand(dealerHand, dealerHandSize);
        std::cout << '\n';
    }
}
