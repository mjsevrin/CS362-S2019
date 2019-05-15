#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "my_assert.h"
#include "rngs.h"

int isTreasure(enum CARD card)
{
    if(card == copper || card == silver || card == gold)
    {
        return 1;
    }
    return 0;
}

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

    int startingHandTreasureCount;
    int finalHandTreasureCount;
    int treasureRatio = 0;
    int noDiscard = 0;
    int testCount = 0;

    int effectFailures = 0;
    int cardCountFailures = 0;
    int handCountFailures = 0;
    int treasureCountFailures = 0;
    printf("TESTING: Adventurer\n"); 
    while(noDiscard < 10)
    {
        testCount++;
        numPlayer = rand() % MAX_PLAYERS + 1;
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        p = rand() % numPlayer;
        G.whoseTurn = p;        // set current player as player to play

        startingHandTreasureCount = 0;
        finalHandTreasureCount = 0;
        treasureRatio = rand() % 100;

        // set hand 
        G.handCount[p] = rand() % MAX_HAND;
        for(i = 0; i < G.handCount[p]; i++)
        {
            if(rand() % 100 < treasureRatio)
            {
                G.hand[p][i] = (enum CARD)(rand() % 3 + 4);  // generate copper, silver, or gold
                startingHandTreasureCount++;
            }
            else
            {
                G.hand[p][i] = curse; // fill the rest with junk
            }
        }

        // set deck
        G.deckCount[p] = rand() % MAX_DECK;
        for(i = 0; i < G.deckCount[p]; i++)
        {
            if(rand() % 100 < treasureRatio)
            {
                G.deck[p][i] = (enum CARD)(rand() % 3 + 4);  // generate copper, silver, or gold
            }
            else
            {
                G.deck[p][i] = curse; // fill the rest with junk
            }
        }

        // check if we are in a "no discard" test case
        if(isTreasure(G.deck[p][0]))
            if(isTreasure(G.deck[p][1]))
                noDiscard++;


        // set discard
        G.discardCount[p] = rand() % MAX_DECK;
        for(i = 0; i < G.discardCount[p]; i++)
        {
            if(rand() % 100 < treasureRatio)
            {
                G.discard[p][i] = (enum CARD)(rand() % 3 + 4);  // generate copper, silver, or gold
            }
            else
            {
                G.discard[p][i] = curse; // fill the rest with junk
            }
        }

        i = rand() % G.handCount[p];
        G.hand[p][i] = adventurer;  // swap card at ith position in player's hand to an adventurer
        int deckCounter = G.deckCount[p]; // save deck count 
        int handCounter = G.handCount[p]; // save hand count 
        int discardCounter = G.discardCount[p]; // save discard count

        if(!assertTrue(cardEffect(adventurer, 0, 0, 0, &G, i, &coin_bonus) == 0, "Card effect function returned an error")); // card effect didn't fail
            effectFailures++;
        if(!assertTrue((deckCounter + handCounter + discardCounter) == (G.discardCount[p] + G.handCount[p] + G.discardCount[p]), "Incorrect total card count")) // no card lost
            cardCountFailures++; 
        if(!assertTrue(G.handCount[p] + 1 == handCounter, "Incorrect # of cards in hand")) // gain one card in hand (-1 adventurer, +2 treasures)
            handCountFailures++;

        for(i = 0; i < G.handCount[p]; i++)
        {
            if(isTreasure(G.hand[p][i]))
            {
                finalHandTreasureCount++;
            }
        }
        if(!assertTrue(startingHandTreasureCount + 2 == finalHandTreasureCount, "Incorrect # of treasures in hand"))  // check 2 treasures were added to the hand
            treasureCountFailures++;
    }

    printf("END OF TEST\n\n");
    printf("Total test runs: %i\n", testCount);
    printf("# of Card Effect Function Failures: %i\n", effectFailures);
    printf("# of Total Card Count Failures: %i\n", cardCountFailures);
    printf("# of Hand Count Failures: %i\n", handCountFailures);
    printf("# of Treasure Count Failures: %i\n", treasureCountFailures);
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n\n");
    return 0;
}