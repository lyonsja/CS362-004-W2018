/*
 * randomtestcard2.c
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

#define TESTCARD "village"

/*Option to print additional error information
 * 1 will print additional information
 * 0 to not print */
#define MSG_OPTION 1

int playVillage(int currentPlayer, struct gameState* state, int handPos);

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

void message(char* desc, int a, int b)
{
    if (MSG_OPTION) {
        printf("%s expected: %d, actual: %d\n", desc, a, b);
    }
}

int testVillage(int p, struct gameState* G, int flag)
{
    struct gameState testG;
    memcpy(&testG, G, sizeof(struct gameState));

    int hpos = 1;
    int result;
    result = playVillage(p, &testG, hpos);

    /*Oracle*/

    if (G->deckCount[p] > 0) {

        /*Handsize should remain unchanged, since village is a cantrip*/
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");

        /*Village should draw exactly 1 card*/
        message("deckCount", G->deckCount[p] - 1, testG.deckCount[p]);
        G->deckCount[p] = G->deckCount[p] - 1;
        flag = cAssert(G->deckCount[p], testG.deckCount[p], flag, "deckCount");

        /*Player should gain net 1 additional action from playing village*/
        G->numActions = G->numActions + 1;
        message("numActions", G->numActions, testG.numActions);
        flag = cAssert(G->numActions, testG.numActions, flag, "numActions");

        /*Check that village is discarded properly*/
        G->discardCount[p] = G->discardCount[p] + 1;
        message("discardCount", G->discardCount[p], testG.discardCount[p]);
        flag = cAssert(G->discardCount[p], testG.discardCount[p], flag, "discardCount");

    } else if (G->discardCount[p] > 0) { /*Case where deck is empty, discard has cards*/
        /*Handsize should remain unchanged, since village is a cantrip*/
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");

        /*Player should gain 1 additional action from playing village*/
        G->numActions = G->numActions + 1;
        message("numActions", G->numActions, testG.numActions);
        flag = cAssert(G->numActions, testG.numActions, flag, "numActions");

        /*Check that village is discarded properly*/
        G->discardCount[p] = 1;
        message("discardCount", G->discardCount[p], testG.discardCount[p]);
        flag = cAssert(G->discardCount[p], testG.discardCount[p], flag, "discardCount");
    } else { /*Case where deck and discard are both empty, no cards to draw*/
        /*Handsize be -1 since deck and discard are empty*/
        G->handCount[p] = G->handCount[p] - 1;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");

        /*Deck size shouldn't change, since it is empty*/
        message("deckCount", G->deckCount[p], testG.deckCount[p]);
        G->deckCount[p] = G->deckCount[p];
        flag = cAssert(G->deckCount[p], testG.deckCount[p], flag, "deckCount");

        /*Player should gain 1 additional action from playing village*/
        G->numActions = G->numActions + 1;
        message("numActions", G->numActions, testG.numActions);
        flag = cAssert(G->numActions, testG.numActions, flag, "numActions");

        /*Check that village is discarded properly*/
        G->discardCount[p] = G->discardCount[p] + 1;
        message("discardCount", G->discardCount[p], testG.discardCount[p]);
        flag = cAssert(G->discardCount[p], testG.discardCount[p], flag, "discardCount");
    }

    return flag; /*temporary*/
}

int main()
{
    int flag = 1;
    struct gameState G;

    SelectStream(5);
    PutSeed(7);

    printf("------------------ Testing Card: %s ------------------\n", TESTCARD);

    int p = 0; /*Player*/
    int q, i, j, k, l, m;

    /*Randomize Game State */

    for (q = 0; q < 2000; q++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        int p = 0;
        int hc = floor(Random() * 10);
        int dc = floor(Random() * 15);
        int dsc = floor(Random() * 15);
        G.numActions = floor(Random() * 8);

        G.handCount[p] = hc;
        G.deckCount[p] = dc;
        G.discardCount[p] = dsc;
        printf("\nIteration %d, deckCount is: %d, discardCount is: %d \n", q, dc, dsc);

        /*Filling deck, hand, and discard with random valid cards*/
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
        flag = testVillage(p, &G, flag);
    }

    if (flag) {
        printf("\n %%%%%%%%%%%%%%%%%%%%SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTCARD);
    } else {
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
    return 0;
}
