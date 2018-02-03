/*
 * cardtest1.c
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define TESTCARD "smithy"



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

	int newCards = 0;
	int discarded = 1;
	/*	int xtraCoins = 0; */
	int shuffledCards = 0;

	int flag = 1;
	/*int i, j, m; */
	int handpos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
	/*int remove1, remove2;*/
	int seed = 1010;
	int numPlayers = 2;
	int thisPlayer = 0;
   /* int otherPlayer = 1; */
	struct gameState G, testG;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	initializeGame(numPlayers, k, seed, &G);

	printf("------------------ Testing Card: %s ------------------\n", TESTCARD);

    
    printf("@@@@@@@@@@ Test case: 5 cards in deck @@@@@@@@@@\n\n");
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer] + newCards - discarded);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, flag);
    
    
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - newCards + shuffledCards);
    flag = cAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards, flag);
    
    
    /*Test Case #2*/
    printf("@@@@@@@@@@ Test case: only 2 cards left in deck @@@@@@@@@@\n\n");
    
    G.deckCount[thisPlayer] = 2;
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    
	newCards = 2;

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer] + newCards - discarded);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, flag);
    
    
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - newCards + shuffledCards);
    flag = cAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards, flag);
    

	if(flag){
		printf("\n %%%%%%%%%%%%%%%%%%%%SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTCARD);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
	return 0;


}
