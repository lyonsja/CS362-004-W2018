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

/*Option to print additional error information
 * 1 will print additional information
 * 0 to not print */
#define MSG_OPTION 1

int playAdventurer(int currentPlayer, struct gameState* state, int temphand[], int z, int cardDrawn, int drawntreasure);

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

int testAdventurer(int p, struct gameState* G, int flag, int treas_deck, int treas_disc)
{
    struct gameState testG;
    memcpy(&testG, G, sizeof(struct gameState));

    int cardDrawn = 0, z = 0, drawnTreasure = 0;
    int result;
    int tmphand[MAX_HAND];
    int total_cards;
    /*printf("FLAG II\n"); */
    result = playAdventurer(p, &testG, tmphand, z, cardDrawn, drawnTreasure);
    total_cards = G->deckCount[p] + G->discardCount[p];
    /*Oracle*/

    if (treas_deck >= 2) {
        /*Handcount should increase by 2 -1 for discarding Adventurer*/
        G->handCount[p] = G->handCount[p] + 1;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");
        int n_cards_discarded = testG.discardCount[p] - G->discardCount[p];

        G->deckCount[p] = G->deckCount[p] - 2 - n_cards_discarded;
        message("deckCount", G->deckCount[p], testG.deckCount[p]);
        flag = cAssert(G->deckCount[p], testG.deckCount[p], flag, "deckCount");

    } else if (treas_disc >= 2) { /*Shuffle should be triggered regardless*/

        G->handCount[p] = G->handCount[p] + 1;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");
        /*Total cards -2 drawn into hand by Adventurer + 1 from discarding Adventurer*/
        message("deck + discard count", total_cards - 1, testG.discardCount[p] + testG.deckCount[p]);
        flag = cAssert(total_cards - 1, testG.discardCount[p] + testG.deckCount[p], flag, "deck + discard count");
    } else if (treas_disc + treas_deck == 1) {

        /*handCount should be unchanged in this case*/
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");
        /*Total cards -1 drawn into hand by Adventurer + 1 from discarding Adventurer*/
        message("deck + discard count", total_cards, testG.discardCount[p] + testG.deckCount[p]);
        flag = cAssert(total_cards, testG.discardCount[p] + testG.deckCount[p], flag, "deck + discard count");
    } else if (treas_disc + treas_deck == 0) {

        G->handCount[p] = G->handCount[p] - 1;
        message("handCount", G->handCount[p], testG.handCount[p]);
        flag = cAssert(G->handCount[p], testG.handCount[p], flag, "handCount");
        /*Total cards 0 drawn into hand by Adventurer + 1 from discarding Adventurer*/
        message("deck + discard count", total_cards + 1, testG.discardCount[p] + testG.deckCount[p]);
        flag = cAssert(total_cards + 1, testG.discardCount[p] + testG.deckCount[p], flag, "deck + discard count");
    }

    return flag;
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
        int hc = floor(Random() * 10) + 1; /*Hand should at least contain the card played*/
        int dc = floor(Random() * 41);
        int dsc = floor(Random() * 41);

        /*treasure count for deck, discard */
        int treas_deck = 0, treas_disc = 0, tmp = 0;
        G.handCount[p] = hc;
        G.deckCount[p] = dc;
        G.discardCount[p] = dsc;

        /*Filling deck, hand, and discard with random valid cards*/
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
