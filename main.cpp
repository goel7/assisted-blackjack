#include "deck_utils.h"
#include "game_utils.h"

#include <iostream>

/*
Note: for player actions, make them type:
h: hit
s: stand
x: split
d: double
r: surrender

This is for initial stage when game is played in terminal.
When moving to web interface, use buttons obviously.
*/

void displayActionGuide() {
    std::cout << "Type for action:\n";
    std::cout << "* h: hit\n* s: stand\n* x: split\n";
    std::cout << "* d: double down\n* r: surrender\n";
    std::cout << "* p: see valid actions\n\n";
}

// bool splitAllowed(int hand[], int handSize, int numHands) {

// }

int main() {
    int cards[52];
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
    // int playerScore {Game::getScore(playerHand, playerHandSize)};


    // Display initial output
    displayActionGuide();

    std::cout << "Dealer: ? ";
    Game::printCard(dealerHand[1]);
    std::cout << '\n';

    std::cout << "Player: ";
    Game::printHand(playerHand[0], playerHandSize[0]);
    std::cout << '\n';
    
    int numHands {1};
    int onHand {0};

    while (true) {
        // Get player action
        char action {};
        std::cout << "Action: ";
        std::cin >> action;

        // Handle hitting:
        if (action == 'h') {
            playerHand[onHand][playerHandSize[onHand]++] = cards[nextCard++];
        }

        // Handle splitting:
        if (action == 'x') {
            playerHand[numHands++][0] = playerHand[onHand][1];
            // playerHand[onHand][1] = 0;

            --playerHandSize[onHand];
            ++playerHandSize[numHands - 1];

            playerHand[onHand][playerHandSize[onHand]++] = cards[nextCard++];
        }

        // /*
        for (int i {0}; i < 4; ++i) {
            std::cout << playerHandSize[i] << '\n';
        }

        for (int i {0}; i < numHands; ++i) {
            std::cout << "Hand " << i + 1 << ": ";
            Game::printHand(playerHand[i], playerHandSize[i]);
            std::cout << '\n';
        }
        // */
    }

    return 0;
}

/*
Next steps:
- Create matrix (2d array) for player hands to allow splitting
- Handle player splitting, hitting on all hands, etc.
- Introduce betting later.
*/
