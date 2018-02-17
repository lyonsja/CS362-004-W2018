/*
 * randomtestcard1.c
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "smithy"

int playSmithy(int currentPlayer, struct gameState* state, int handPos);

int cAssert(int arg1, int arg2, int flag)
{
    if (arg1 == arg2) {
        printf("__________Test Passed__________\n\n");
    } else {
        printf("__________Test Failed__________\n\n");
        flag = 0;
    }
    if (flag == 0) {
        return 0;
    } else {
        return 1;
    }
}

int testSmithy(int p, struct gameState* G)
{
    struct gameState testG;
    memcpy(&testG, G, sizeof(struct gameState));

    int hpos = 0;
    int result;
    printf("FLAG II\n");
    result = playSmithy(p, &testG, hpos);

    if (G->deckCount[p] >= 3) {
        printf("FLAG III\n");
        G->handCount[p] = G->handCount[p] + 3;
        /*G.hand[p][G.handCount[p]-1] = G. */
    } else if (G->discardCount[p] > 0) {
    }

    return 0; /*temporary*/
}

int main()
{
    /* int discarded = 1;
    int shuffledCards = 0;
    int drawnCards = 0;
    int i, j, m; 
    int seed = 1000;
    int numPlayers = 2; */
    int flag = 1;
    struct gameState G;

    /*int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room };*/

    SelectStream(5);
    PutSeed(7);

    /*initializeGame(numPlayers, k, seed, &G);*/

    printf("------------------ Testing Card: %s ------------------\n", TESTCARD);

    int testResult;
    int p = 0; /*Player*/
    int q, i, j, k;

    /*Randomize Game State */

    for (q = 0; q < 2000; q++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        int p = 0;
        int hc = floor(Random() * MAX_HAND);
        int dc = floor(Random() * MAX_DECK);
        G.handCount[p] = hc;
        G.deckCount[p] = dc;
        printf("FLAG I\n");
        for(int j = 0; j < dc; j++){
            G.deck[p][j] = floor(Random() * 26);
        }
        for(k = 0; k < hc; k++){
            G.hand[p][k] = floor(Random() * 26);
        }

        testResult = testSmithy(p, &G);
    }

    if (flag) {
        printf("\n %%%%%%%%%%%%%%%%%%%%SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTCARD);
    } else {
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
    return 0;
}
