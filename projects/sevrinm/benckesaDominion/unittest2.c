#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h">
#include "rngs.h"


int main ()
{
    int seed = 1000;
    int numPlayer = 2;
    int i, p, r;

    struct gameState G;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};

    printf("TESTING: fullDeckCount()\n");

    for(p = 0; p < numPlayer; p++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    #if VERBOSE
        printf("PLAYER %i\n------------\n", p+1);
        printf("Expected 7 coopers in deck, Actual: %i\n", fullDeckCount(p, copper, &G)); 
        printf("Expected 3 estate in deck, Actual: %i\n", fullDeckCount(p, estate, &G)); 
    #endif
        my_assert(fullDeckCount(p, copper, &G) == 7);  // check hand and deck combined have 7 coppers
        my_assert(fullDeckCount(p, estate, &G) == 3);  // check hand and deck combined have 3 estates

        G.discardCount[p] = 10;
        for(i = 0; i < G.discardCount[p]; i++) // add 10 coppers to the discard
        {
            G.discard[p][i] = copper;
        }
    #if VERBOSE
        printf("Expected 17 coopers in deck, Actual: %i\n", fullDeckCount(p, copper, &G)); 
    #endif
        my_assert(fullDeckCount(p, copper, &G) == 17); // check hand, deck, and discard combined have 17 coppers
    
    #if VERBOSE
        printf("Expection 0 curses in deck, Actual: %i\n\n", fullDeckCount(p, curse, &G)); 
    #endif
        my_assert(fullDeckCount(p, curse, &G) == 0); // check full deck for card that should not be in there
    }

    printf("END OF TEST\n");
    printf("-------------\n\n");
    return 0;
}