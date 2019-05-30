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
    int i, n = 0;

    struct gameState G;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};

    printf("TESTING: isGameOver()\n");

    // CASE 1 - empty province supply
#if VERBOSE
    printf("Case %i: Empty province supply (GAME OVER)\n", n+1);
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.supplyCount[province] = 0;
    my_assert(isGameOver(&G) == 1);  // check hand and deck combined have 7 coppers
    n++;

    // CASE 2 - 3 empty supplies
#if VERBOSE
    printf("Case %i: Empty supplies (GAME OVER)\n", n+1);
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for(i = 0; i < 3; i++)
    {
        G.supplyCount[i] = 0;
    }
    my_assert(isGameOver(&G) == 1);  // check hand and deck combined have 7 coppers
    n++;

    // CASE 3 - less than 3 empty supplies
#if VERBOSE
    printf("Case %i: Less than 3 empty supplies (GAME NOT OVER)\n", n+1);
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for(i = 0; i < 2; i++)
    {
        G.supplyCount[i] = 0;
    }
    my_assert(isGameOver(&G) == 0);  // check hand and deck combined have 7 coppers

    
    printf("END OF TEST\n");
    printf("-------------\n\n");
    return 0;
}