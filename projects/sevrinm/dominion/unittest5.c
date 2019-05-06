#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"

int arraySum(int* arr, int size)
{
    int i;
    int sum = 0;
    for(i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

int main ()
{
    int seed = 1000;
    int numPlayer = 3;
    int i;
    int players[MAX_PLAYERS] = {0, 0, 0, 0};

    struct gameState G;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};

    
    printf("TESTING: getWinners()\n");

#if VERBOSE
    printf("Case 1: No tie breakers needed\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
#if VERBOSE
    printf("Scores: %i, %i, %i\n", scoreFor(0, &G), scoreFor(1, &G), scoreFor(2, &G));
    int x, y;
    for (x = 0; x < numPlayer; x++){
        for(y = 0; y < G.handCount[x]; y++) {
            printf("%i\t", G.hand[x][y]);
        }
        printf("\n");
        for(y = 0; y < G.deckCount[x]; y++) {
            printf("%i\t", G.deck[x][y]);
        }
        printf("\n");
    }
#endif 
    for(i = 0; i < 3; i++) 
    {
        G.discardCount[i] = 1;
    }
    G.discard[0][0] = curse;
    G.discard[1][0] = estate; // p2 wins by 1 point
    G.discard[2][0] = copper;
#if VERBOSE
    printf("Scores: %i, %i, %i\n", scoreFor(0, &G), scoreFor(1, &G), scoreFor(2, &G));
    for (x = 0; x < numPlayer; x++){
        for(y = 0; y < G.handCount[x]; y++) {
            printf("%i\t", G.hand[x][y]);
        }
        printf("\n");
        for(y = 0; y < G.deckCount[x]; y++) {
            printf("%i\t", G.deck[x][y]);
        }
        printf("\n");
        for(y = 0; y < G.discardCount[x]; y++) {
            printf("%i\t", G.discard[x][y]);
        }
        printf("\n");
    }
#endif 
    getWinners(players, &G);
    my_assert(arraySum(players, MAX_PLAYERS) == 1);  // check only one player has highest score
    my_assert(players[1] == 1); // check player 2 is the winner

#if VERBOSE
    printf("Case 2: Tie breaker due to lower number of turns\n");
#endif
    //memset(&G, 23, sizeof(struct gameState));   // clear the game state
    //initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for(i = 0; i < 3; i++) 
    {
        G.discardCount[i] = 1;
    }
    G.discard[0][0] = estate;
    G.discard[1][0] = estate; // player 1 and 2 are tie, p2 wins on lower number of turns played
    G.discard[2][0] = copper;
#if VERBOSE
    printf("Scores: %i, %i, %i\n", scoreFor(0, &G), scoreFor(1, &G), scoreFor(2, &G));
#endif
    getWinners(players, &G);
    my_assert(arraySum(players, MAX_PLAYERS) == 1);  // check only one player has highest score
    my_assert(players[1] == 1); // check player 2 is the winner

#if VERBOSE
    printf("Case 3: Shared Victory\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for(i = 0; i < 3; i++) 
    {
        G.discardCount[i] = 1;
    }
    G.discard[0][0] = estate; // player 2 and 3 have same point total and turns played
    G.discard[1][0] = estate;
    G.discard[2][0] = estate;
#if VERBOSE
    printf("Scores: %i, %i, %i\n", scoreFor(0, &G), scoreFor(1, &G), scoreFor(2, &G));
#endif
    getWinners(players, &G);
    my_assert(arraySum(players, MAX_PLAYERS) == 2);  // check only one player has highest score
    my_assert(players[1] == 1); // check player 2 is the winner
    my_assert(players[2] == 1); // check player 3 is the winner

#if VERBOSE
    printf("Case 4: Tie breaker only activates when necessary\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for(i = 0; i < 3; i++) 
    {
        G.discardCount[i] = 1;
    }
    G.discardCount[0] = 2;
    G.discard[0][0] = estate; // give player one two estate, a 1-point advantage over players with lower number of turns
    G.discard[0][1] = estate;
    G.discard[1][0] = estate;
    G.discard[2][0] = estate;
    getWinners(players, &G);
    my_assert(arraySum(players, MAX_PLAYERS) == 1);  // check only one player has highest score
    my_assert(players[0] == 1); // check player 1 is the winner

    printf("END OF TEST\n");
    printf("-------------\n\n");;
    return 0;
}