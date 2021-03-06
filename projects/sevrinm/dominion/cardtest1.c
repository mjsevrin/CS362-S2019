#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"

int main ()
{
    int seed = 1000;
    int numPlayer = 3;
    int p, i;
    int coin_bonus = 0;

    struct gameState G;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    
    printf("TESTING: Smithy\n"); 
    for(p = 0; p < numPlayer; p++) 
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        int idx = p;
        G.whoseTurn = p;        // set current player as player to play
        G.hand[p][idx] = smithy;  // swap card at position "idx" in player's hand to a smithy
        int deckCounter = G.deckCount[p]; // save deck count 
        int oldhand[5];

        my_assert(cardEffect(G.hand[p][p], 0, 0, 0, &G, idx, &coin_bonus) == 0); // smithy didn't fail
        my_assert(G.discardCount[p] == 1); // only one card in discard pile
        my_assert(G.discard[p][0] == smithy); // discarded card is smithy
        my_assert(G.handCount[p] == 7);    // 7 cards in hand (5-1+3)
        my_assert(deckCounter - G.deckCount[p] == 3);  // deck has 3 less cards in it
    }
    printf("END OF TEST\n");
    printf("-------------\n\n");;
    return 0;
}