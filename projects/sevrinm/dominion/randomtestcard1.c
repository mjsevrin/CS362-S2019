#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "my_assert.h"
#include "rngs.h"

int main ()
{
    srand(time(0));

    int seed = 1000;
    int numPlayer;
    int p, i;
    int coin_bonus = 0;

    struct gameState G;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};

    int testCount = 0;
    int effectFailures = 0;
    int cardCountFailures = 0;
    int handCountFailures = 0;
    int actionCountFailures = 0;
    printf("TESTING: Great Hall\n"); 
    while(testCount < 100)
    {
        testCount++;
        numPlayer = rand() % MAX_PLAYERS + 1;
        memset(&G, 0, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        p = rand() % numPlayer;
        G.whoseTurn = p;        // set current player as player to play

        // set hand 
        G.handCount[p] = rand() % 15 + 1;
        for(i = 0; i < G.handCount[p]; i++)
        {
            G.hand[p][i] = (enum CARD)(rand() % 27);  // generate copper, silver, or gold
        }

        // set deck
        G.deckCount[p] = rand() % MAX_DECK;
        for(i = 0; i < G.deckCount[p]; i++)
        {
            G.deck[p][i] = (enum CARD)(rand() % 27);  // generate copper, silver, or gold
        }

        // set discard
        G.discardCount[p] = rand() % MAX_DECK;
        for(i = 0; i < G.discardCount[p]; i++)
        {
            G.discard[p][i] = (enum CARD)(rand() % 27);  // generate copper, silver, or gold
        }

        i = rand() % G.handCount[p];
        G.hand[p][i] = great_hall;  // swap card at ith position in player's hand to an adventurer
        G.numActions = rand() % 10;
    
        int deckCounter = G.deckCount[p]; // save deck count 
        int handCounter = G.handCount[p]; // save hand count 
        int discardCounter = G.discardCount[p]; // save discard count
        int oldNumActions = G.numActions; // save action count 
        int function_return = cardEffect(great_hall, 0, 0, 0, &G, i, &coin_bonus);
        if(!assertTrue(function_return == 0, "Card effect function returned an error"))// card effect didn't fail
            effectFailures++;
        if(!assertTrue((deckCounter + handCounter + discardCounter) == (G.discardCount[p] + G.handCount[p] + G.discardCount[p]), "Incorrect total card count")) // no card lost
            cardCountFailures++; 
        if(!assertTrue(G.handCount[p] == handCounter, "Incorrect # of cards in hand")) // check hand count (-1 great hall, +1 drawn card)
            handCountFailures++;
        if(!assertTrue(G.numActions == (oldNumActions + 1), "Incorrect # of actions left")) // gain one action
            actionCountFailures++;
    }

    printf("END OF TEST\n\n");
    printf("Total test runs: %i\n", testCount);
    printf("# of Card Effect Function Failures: %i\n", effectFailures);
    printf("# of Total Card Count Failures: %i\n", cardCountFailures);
    printf("# of Hand Count Failures: %i\n", handCountFailures);
    printf("# of Action Count Failures: %i\n", actionCountFailures);
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n\n");

    return 0;
}