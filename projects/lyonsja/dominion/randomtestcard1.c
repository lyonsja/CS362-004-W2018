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

int cAssert(int arg1, int arg2, int flag, char* under_test)
{
    if (arg1 != arg2) {
        printf("__________Testing %s Failed__________\n\n", under_test);
        flag = 0;
    } else{
        printf("__________Testing %s Passed__________\n\n", under_test);
    }
    if (flag == 0) {
        return 0;
    } else {
        return 1;
    }
}

int testSmithy(int p, struct gameState* G, int flag)
{
    struct gameState testG;
    memcpy(&testG, G, sizeof(struct gameState));

    int hpos = 1;
    int result;
    /*printf("FLAG II\n"); */
    result = playSmithy(p, &testG, hpos);

    /*Oracle*/

    if (G->deckCount[p] >= 3) {
        /*printf("FLAG III\n"); */

        /*Check that 3 cards were drawn into the hand -1 for discarding Smithy*/
        G->handCount[p] = G->handCount[p] + 2;
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");
        G->deckCount[p] = G->deckCount[p] - 3;
        flag = cAssert(G->deckCount[p], testG.deckCount[p], flag, "deckCount");

        /*G->hand[p][G->handCount[p]-1] = */
    } else if (G->discardCount[p] > 0) {
        G->discardCount[p] = 0;
        flag = cAssert(G->discardCount[p], testG.discardCount[p], flag, "discardCount");
    }

    return flag; /*temporary*/
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
    int q, i, j, k, l;

    /*Randomize Game State */

    for (q = 0; q < 2000; q++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        int p = 0;
        int hc = floor(Random() * 10);
        int dc = floor(Random() * 15);
        int dsc = floor(Random() * 15);
        G.handCount[p] = hc;
        G.deckCount[p] = dc;
        G.discardCount[p] = dsc;
        printf("\nIteration %d, deckCount is: %d, discardCount is: %d \n", q, dc, dsc);

        for (int j = 0; j < dc; j++) {
            G.deck[p][j] = floor(Random() * 27);
        }
        for (k = 0; k < hc; k++) {
            G.hand[p][k] = floor(Random() * 27);
        }
        for (l = 0; l < dsc; l++) {
            G.discard[p][l] = floor(Random() * 27);
        }

        G.playedCardCount = 1;
        flag = testSmithy(p, &G, flag);
    }

    if (flag) {
        printf("\n %%%%%%%%%%%%%%%%%%%%SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTCARD);
    } else {
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
    return 0;
}
