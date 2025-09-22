#include "deck_utils.h"
#include "game_utils.h"

#include <iostream>

int main() {
    int cards[52];
    Game::printActionGuide();
    
    while (true) {
        Deck::shuffle(cards);
        int nextCard {0}; // index for next card to be dealt

        // initialize hands
        int dealerHand[12];
        int playerHand[4][12];
        playerHand[0][0] = cards[nextCard++];
        dealerHand[0] = cards[nextCard++];
        playerHand[0][1] = cards[nextCard++];
        dealerHand[1] = cards[nextCard++];

        int playerHandSize[4] = {2};

        // Display initial output
        Game::printInitialHands(dealerHand, playerHand[0], playerHandSize[0]);
        
        int numHands {1};
        int onHand {0}; // index of player hand being currently played (due to splits)

        auto getPlayerScore = [&](int handIndex) {
            return Game::getScore(playerHand[handIndex], playerHandSize[handIndex]);
        };
    
        bool split {false}; // to decide Action output statements

        for (int i {0}; i < numHands; ++i) {
            int playerScore {getPlayerScore(i)};
            bool stand {false};
            bool bust {false};

            // auto hitHand = [&](int handIndex) {
            //     playerHand[handIndex][playerHandSize[handIndex]++] = cards[nextCard++];
            // };
            auto hitHand = [&](int hand[], int &handSize) {
                hand[handSize++] = cards[nextCard++];
            };

            auto splitAllowed = [&] (int hand[], int handSize) {
                bool pair {Game::getCardRank(hand[0]) == Game::getCardRank(hand[1])};
                if (pair && handSize == 2 && numHands < 4) {
                    return true;
                }
                return false;
            };

            auto printPlayerHand = [](int hand[], int& handSize) {
                std::cout << "Player: ";
                Game::printHand(hand, handSize);
                std::cout << '\n';
            };

            auto printAllPlayerHands = [&]() {
                for (int j {i}; j < numHands; ++j) {
                    std::cout << "Hand " << j + 1 << ": ";
                    Game::printHand(playerHand[j], playerHandSize[j]);
                    std::cout << '\n';
                }
            };

            auto actionStmt = [&]() {
                char action {};
                if (!split) std::cout << "Action: ";
                else {
                    std::cout << "Action (Hand " << onHand + 1 << "): ";
                }
                std::cin >> action;
                return action;
            };

            if (i > 0) {
                hitHand(playerHand[onHand], playerHandSize[onHand]);
                printPlayerHand(playerHand[onHand], playerHandSize[onHand]);
            }

            if (playerScore == 21) {
                std::cout << "Player got blackjack!\n";
                if (split) {
                    std::cout << "Move on to next hand.\n";
                }
            }

            while (!stand && !bust && playerScore != 21) {
                // Get player action
                char action {actionStmt()};

                bool canSplit {splitAllowed(playerHand[onHand], playerHandSize[onHand])};

                // Handle standing:
                if (action == 's') {
                    stand = true;
                    if (split) {
                        std::cout << "Player stood. Move on to next hand.\n";
                    }
                    onHand++;
                }
                
                // Handle hitting:
                else if (action == 'h') {
                    hitHand(playerHand[onHand], playerHandSize[onHand]);
                    printPlayerHand(playerHand[onHand], playerHandSize[onHand]);
                }

                // Handle splitting:
                else if (canSplit && action == 'x') {
                    playerHand[numHands++][0] = playerHand[onHand][1];
                    // playerHand[onHand][1] = 0;

                    --playerHandSize[onHand];
                    ++playerHandSize[numHands - 1];

                    split = true;

                    hitHand(playerHand[onHand], playerHandSize[onHand]);
                    printAllPlayerHands();
                }

                // Handle double down:
                else if (action == 'd') {
                    // double bet size
                    // hit()
                    // then onHand++ to move on to next hand
                }

                // Handle surrender:
                else if (action == 'r') {
                    ;
                }

                playerScore = getPlayerScore(i);
                if (playerScore > 21) {
                    bust = true;
                    std::cout << "Player (Hand " << onHand + 1 << ") busted.\n";

                    if (split) {
                        std::cout << "Move on to next hand.\n";
                    }

                    onHand++;
                }

                if (playerScore == 21) {
                    std::cout << "Player got 21.\n";
                    if (split) {
                        std::cout << "Move on to next hand.\n";
                    }
                    onHand++;
                }
            }
        }
        
        std::cout << '\n';
    }

    return 0;
}
