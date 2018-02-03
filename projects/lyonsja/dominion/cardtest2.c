/*
 * cardtest2.c
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define TESTCARD "adventurer"


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
	int shuffledCards = 0;
    int drawnCards = 0;
	int flag = 1;
	/*int i, j, m; */
	int handpos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
	/*int remove1, remove2;*/
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	initializeGame(numPlayers, k, seed, &G);

	printf("------------------ Testing Card: %s ------------------\n", TESTCARD);

    
    /*Test case where no treasure in deck*/
    printf("@@@@@@@@@@ Test: 0 treasure cards in deck @@@@@@@@@@\n\n");
    
    int q;
    for(q = 4; q >= 0; q--){
     G.deck[thisPlayer][q] = estate; 
    }
    memcpy(&testG, &G, sizeof(struct gameState));
    
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    shuffledCards = 5;
    
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer]);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer], flag);
    
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - shuffledCards);
    /*Should cycle through deck filled w/estates, resulting in empty deck and all estates in discard pile */
	flag = cAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - shuffledCards, flag);

    
    /*Test case where only 1 treasure in deck*/
    printf("@@@@@@@@@@ Test: exactly 1 treasure card left in deck @@@@@@@@@@\n\n");

    for(q = 4; q > 0; q--){
     G.deck[thisPlayer][q] = estate; 
    }
    /*Treasure located at bottom of deck, but position shouldn't matter for this case */
    G.deck[thisPlayer][0] = copper;
    
    
    memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    shuffledCards = 4;
    drawnCards = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer] + drawnCards);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards, flag);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - shuffledCards - drawnCards);
	flag = cAssert(testG.deckCount[thisPlayer],  G.deckCount[thisPlayer] - shuffledCards, flag);
    
    
    
    /*Test case where >2 treasures in deck*/
    printf("@@@@@@@@@@ Test: >2 treasure cards in deck @@@@@@@@@@\n\n");
    
     for(q = 1; q > 0; q--){
     G.deck[thisPlayer][q] = estate; 
    }
    
    /*Treasure on top, should stop drawing after hitting two treasures*/
    G.deck[thisPlayer][2] = copper;
    G.deck[thisPlayer][3] = copper;
    G.deck[thisPlayer][4] = copper;
    
    memcpy(&testG, &G, sizeof(struct gameState));
  /*  printf("Player deckCount: %d\n", testG.deckCount[thisPlayer]); */

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    drawnCards = 2;
    /*No cards should have been shuffled*/
    
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer] + drawnCards);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards, flag);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - drawnCards + discarded);
	flag = cAssert(testG.deckCount[thisPlayer],  G.deckCount[thisPlayer] - drawnCards + discarded, flag);
    
    
	if(flag){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
	return 0;


}
