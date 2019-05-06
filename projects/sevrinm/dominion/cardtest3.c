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
    int cardCount = 5;
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

    printf("TESTING: Great Hall\n"); 
    for(p = 0; p < numPlayer; p++) 
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        int idx = p;
        G.whoseTurn = p;        // set current player as player to play
        G.numActions = p;        // set current player as player to play
        G.handCount[p] = cardCount;
        G.deckCount[p] = cardCount;
        memcpy(G.hand[p], coppers, sizeof(int) * cardCount); // set all the cards in hand to copper 
        memcpy(G.deck[p], silvers, sizeof(int) * cardCount); // set all the cards in deck to silver 
        G.hand[p][idx] = great_hall;  // swap card at position "idx" in player's hand to a smithy
    
    #if VERBOSE
        printf("Discard Count: %i\n", G.discardCount[p]);
        printf("Hand count: %i\n", G.handCount[p]);
        for(i = 0; i < 5; i++) {
            printf("Card at position %i: %i\n", i, G.hand[p][i]);
        }
    #endif
        my_assert(cardEffect(great_hall, 0, 0, 0, &G, idx, &coin_bonus) == 0); // smithy didn't fail
        my_assert(G.discardCount[p] == 1); // only one card in discard pile
        my_assert(G.discard[p][0] == great_hall); // discarded card is smithy
        my_assert(G.handCount[p] == 5);    // 7 cards in hand (5-1+1)
        my_assert(G.numActions == p+1);    // incremented num of actions
    }
    printf("END OF TEST\n");
    printf("-------------\n\n");;
    return 0;
}