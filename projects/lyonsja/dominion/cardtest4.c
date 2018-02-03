/*
 * cardtest4.c
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define TESTCARD "village"


int cAssert(int arg1, int arg2, int flag){
    
    if(arg1 == arg2){
		printf("__________Test Passed__________\n\n");
	}
	else{
		printf("__________Test Failed__________\n\n");
		flag = 0;
    }
	if(flag == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int main() {

	int discarded = 1;
	/*	int xtraCoins = 0; */
	/*int shuffledCards = 0; */
    int drawnCards = 0;
    int additActions = 0;
	int flag = 1;
	/*int i, j, m; */
	int handpos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
	/*int remove1, remove2;*/
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	initializeGame(numPlayers, k, seed, &G);

	printf("------------------ Testing Card: %s ------------------\n", TESTCARD);

    
    /*Test case where at least 1 card is in deck*/
    printf("@@@@@@@@@@ Test: 1+ cards in deck @@@@@@@@@@\n\n");
    
    memcpy(&testG, &G, sizeof(struct gameState));
    
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    drawnCards = 1;
    additActions = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer] + drawnCards - discarded);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards - discarded, flag);
    
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - drawnCards);
    flag = cAssert(testG.deckCount[thisPlayer], G.handCount[thisPlayer] - drawnCards, flag);
    
    printf("action count = %d, expected = %d\n", testG.numActions, G.numActions + additActions);
    flag = cAssert(testG.numActions, G.numActions + additActions, flag);
    
    
    
    /*Test case where 0 cards left in deck*/
    printf("@@@@@@@@@@ Test: NO cards in deck @@@@@@@@@@\n\n");
    
    
    G.deckCount[thisPlayer] = 0;
    memcpy(&testG, &G, sizeof(struct gameState));
    
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    drawnCards = 0;
    additActions = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer] + drawnCards - discarded);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards - discarded, flag);
    
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - drawnCards);
    flag = cAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - drawnCards, flag);
    
    printf("action count = %d, expected = %d\n", testG.numActions, G.numActions + additActions);
    flag = cAssert(testG.numActions, G.numActions + additActions, flag);

    if(flag){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
    
    
}
