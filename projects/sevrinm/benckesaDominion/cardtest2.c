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

    
    printf("TESTING: Adventurer\n"); 
    // testing case in which there is no discard
    for(p = 0; p < numPlayer; p++) 
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        int idx = p;
        G.whoseTurn = p;        // set current player as player to play
        G.handCount[p] = cardCount;
        G.deckCount[p] = cardCount;
        memcpy(G.hand[p], coppers, sizeof(int) * cardCount); // set all the cards in hand to copper 
        memcpy(G.deck[p], golds, sizeof(int) * cardCount); // set all the cards in deck to silver 
        G.hand[p][idx] = adventurer;  // swap card at position "idx" in player's hand to an adventurer
        int deckCounter = G.deckCount[p]; // save deck count 
        for(i = 0; i < deckCounter; i++) 
        {
            G.deck[p][i] = gold;
        }
        my_assert(cardEffect(G.hand[p][p], 0, 0, 0, &G, idx, &coin_bonus) == 0); // card effect didn't fail
        my_assert(G.discardCount[p] == 1); // only one card in discard pile
        my_assert(G.discard[p][0] == adventurer); // discarded card is smithy
        my_assert(G.handCount[p] == 6);    // 6 cards in hand (5-1+2)
        int lastCardHandPos = G.handCount[p];
        my_assert(G.hand[p][i-1] == gold); // last 2 cards in hand are gold
        my_assert(G.hand[p][i-2] == gold);
    }

    // testing case in which some cards are discarded
    for(p = 0; p < numPlayer; p++) 
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        int idx = p;
        G.whoseTurn = p;        // set current player as player to play
        G.handCount[p] = cardCount;
        G.deckCount[p] = cardCount;
        memcpy(G.hand[p], coppers, sizeof(int) * cardCount); // set all the cards in hand to copper 
        memcpy(G.deck[p], golds, sizeof(int) * cardCount); // set all the cards in deck to silver 
        G.hand[p][idx] = adventurer;  // swap card at position "idx" in player's hand to an adventurer
        int deckCounter = G.deckCount[p]; // save deck count 
        G.deck[p][0] = smithy;          // setting first card to be drawn as a non-treasure
        for(i = 1; i < deckCounter; i++) 
        {
            G.deck[p][i] = gold;
        }
        my_assert(cardEffect(G.hand[p][p], 0, 0, 0, &G, idx, &coin_bonus) == 0); // card effect didn't fail
        my_assert(G.discardCount[p] == 2); // only one card in discard pile
        my_assert(G.discard[p][0] == adventurer); // discarded card is 
        my_assert(G.discard[p][1] == smithy); // discarded card is smithy
        my_assert(G.handCount[p] == 6);    // 6 cards in hand (5-1+2)
        int lastCardHandPos = G.handCount[p];
        my_assert(G.hand[p][i-1] == gold); // last 2 cards in hand are gold
        my_assert(G.hand[p][i-2] == gold);
    }
    printf("END OF TEST\n");
    printf("-------------\n\n");;;
    return 0;
}