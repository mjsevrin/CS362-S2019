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
    int p, r, handCount;

    struct gameState G;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};

    r = initializeGame(numPlayer, k, seed, &G);
    

    printf("TESTING: numHandCards()\n");
#if VERBOSE
    printf("Expected num cards in hard: 5, Actual: %i\n", numHandCards(&G)); 
#endif
    my_assert(numHandCards(&G) == 5);
    printf("END OF TEST\n");
    printf("-------------\n\n");
    return 0;
}