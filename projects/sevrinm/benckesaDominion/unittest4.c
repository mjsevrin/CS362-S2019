#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"


int main ()
{
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int i, p, r, handCount;

    struct gameState G;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    printf("TESTING: handCard()\n");
    for(p = 0; p < numPlayer; p++)
    {
        G.whoseTurn = p;

        for(i = 0; i < 5; i++)
        {
            G.hand[p][i] = k[i];
#if VERBOSE
    printf("Expected card enum : %i, Actual: %i\n", k[i], handCard(i, &G)); 
#endif
            my_assert(handCard(i, &G) == k[i]);
        }
    }

    printf("END OF TEST\n");
    printf("-------------\n\n");
    return 0;
}