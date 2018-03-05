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

/*Option to print additional error information
 * 1 will print additional information
 * 0 to not print */
#define MSG_OPTION 1

int handle_card_smithy(int currentPlayer, struct gameState* state, int handPos);

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

int testSmithy(int p, struct gameState* G, int flag)
{
    struct gameState testG;
    memcpy(&testG, G, sizeof(struct gameState));

    int hpos = 0;
    int result;
    result = handle_card_smithy(p, &testG, hpos);

    /*Oracle*/

    if (G->deckCount[p] >= 3) {

        /*Check that 3 cards were drawn into the hand -1 for discarding Smithy*/
        G->handCount[p] = G->handCount[p] + 2;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");

        G->deckCount[p] = G->deckCount[p] - 3;
        message("deckCount", G->deckCount[p], testG.deckCount[p]);
        flag = cAssert(G->deckCount[p], testG.deckCount[p], flag, "deckCount");

        /*Check if smithy is discarded*/
        G->discardCount[p] = G->discardCount[p] + 1;
        message("discardCount", G->discardCount[p], testG.discardCount[p]);
        flag = cAssert(G->discardCount[p], testG.discardCount[p], flag, "discardCount");
    } else if (G->discardCount[p] >= 3) { /*Case where deck is empty, discard has at least 3 cards*/
        G->handCount[p] = G->handCount[p] + 2;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");

        /*Check if smithy is discarded*/
        G->discardCount[p] = 1;
        flag = cAssert(G->discardCount[p], testG.discardCount[p], flag, "discardCount");
    } else if (G->discardCount[p] + G->deckCount[p] < 3 && G->discardCount[p] + G->deckCount[p] > 0) {
        /*Case where only 2 or 1 cards in deck + discard*/
        int n_cards_drawn = G->discardCount[p] + G->deckCount[p] - 1;
        G->handCount[p] = G->handCount[p] + n_cards_drawn;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");

        /*Check if smithy is discarded*/
        G->discardCount[p] = 1;
        flag = cAssert(G->discardCount[p], testG.discardCount[p], flag, "discardCount");
    } else { /*Case where 0 cards in deck + discard*/
        G->handCount[p] = G->handCount[p] - 1;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");

        /*deckCount should not change*/
        message("deckCount", G->deckCount[p], testG.deckCount[p]);
        flag = cAssert(G->deckCount[p], testG.deckCount[p], flag, "deckCount");

        /*Check if smithy is discarded*/
        G->discardCount[p] = 1;
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

    int testResult;
    int p = 0; /*Player*/
    int q, i, j, k, l;

    /*Randomize Game State */

    for (q = 0; q < 2000; q++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        int p = 0;
        int hc = floor(Random() * 10) + 1;
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
