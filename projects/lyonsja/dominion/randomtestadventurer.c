/*
 * randomtestadventurer.c
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

#define TESTCARD "adventurer"

int cAssert(int arg1, int arg2, int flag, char* under_test)
{
    if (arg1 != arg2) {
        printf("__________Testing %s Failed__________\n\n", under_test);
        flag = 0;
    } else {
        printf("__________Testing %s Passed__________\n\n", under_test);
    }
    if (flag == 0) {
        return 0;
    } else {
        return 1;
    }
}
int testAdventurer(int p, struct gameState* G, int flag, int treas_deck, int treas_disc)
{
    struct gameState testG;
    memcpy(&testG, G, sizeof(struct gameState));

    int cardDrawn = 0, z = 0, drawnTreasure = 0;
    int result;
    int temphand[MAX_HAND];
    /*printf("FLAG II\n"); */
    flag = playAdventurer(p, &testG, temphand[255], z, cardDrawn, drawnTreasure);

    /*Oracle*/

    if (G->deckCount[p] >= 3) {
        /*printf("FLAG III\n"); */
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

    /*int discarded = 1;
    int shuffledCards = 0;
    int drawnCards = 0; */
    int flag = 1;
    /*int i, j, m; */
    /*int seed = 1000;*/
    struct gameState G;

    /*int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room };*/

    SelectStream(5);
    PutSeed(7);

    /*initializeGame(numPlayers, k, seed, &G);*/

    printf("------------------ Testing Card: %s ------------------\n", TESTCARD);
    /*Counter for tmpHand*/
    int numTreasDrawn;

    int p = 0; /*Player*/
    int q, i, j, l, m;

    /*Randomize Game State */
    for (q = 0; q < 2000; q++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        int p = 0;
        int hc = floor(Random() * 10);
        int dc = floor(Random() * 30);
        int dsc = floor(Random() * 30);

        /*treasure count for deck, discard */
        int treas_deck = 0, treas_disc = 0, tmp = 0;
        G.handCount[p] = hc;
        G.deckCount[p] = dc;
        G.discardCount[p] = dsc;
        printf("\nIteration %d, treasure in deck %d, treasure in discard: %d \n", q, dc, dsc);

        for (int j = 0; j < dc; j++) {
            tmp = floor(Random() * 27);
            G.deck[p][j] = tmp;
            if (tmp > 3 && tmp < 7) {
                treas_deck++;
            }
        }
        for (m = 0; m < hc; m++) {
            G.hand[p][m] = floor(Random() * 27);
        }
        for (l = 0; l < dsc; l++) {
            tmp = floor(Random() * 27);
            G.discard[p][l] = tmp;
            if (tmp > 3 && tmp < 7) {
                treas_disc++;
            }
        }
        printf("\nIteration %d, treasure in deck %d, treasure in discard: %d \n", q, treas_deck, treas_disc);
        G.playedCardCount = 1;
        flag = testAdventurer(p, &G, flag, treas_deck, treas_disc);
    }

    if (flag) {
        printf("\n %%%%%%%%%%%%%%%%%%%%SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTCARD);
    } else {
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
    return 0;
}
