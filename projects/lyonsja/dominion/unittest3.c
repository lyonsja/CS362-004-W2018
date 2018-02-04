/*
 * unittest3.c
 * Testing on gainCard() on line 1215  dominion.c
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define TESTFUNC "gainCard"

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
    /*
	int discarded = 1;
	int xtraCoins = 0; 
	int shuffledCards = 0;
    int drawnCards = 0;
    */
	int flag = 1;
	/*int i, j, m; */
	/*int handpos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0; */
	/*int remove1, remove2;*/
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
    /*int otherPlayer = 1;
    */
    int toIndicat;
    int canGain = 0;
    
    
	struct gameState G;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	initializeGame(numPlayers, k, seed, &G);

	printf("------------------ Testing Function: %s ------------------\n", TESTFUNC);
   
    /* As implemented in dominion.c, isGameOver returns 1 when the game is over, 0 otherwise*/
    
    
    
    /*Test case #1, gaining to discard*/
    printf("@@@@@@@@@@ Test: Gain to discard @@@@@@@@@@\n\n");
    
    toIndicat = 0;
    
    /*Should gain a mine card to the discard*/
    printf("Card should be valid to gain\n");
    flag = cAssert(gainCard(mine, &G, toIndicat, thisPlayer), canGain, flag);
    
    printf("discard count: %d, expected: %d\n", G.discardCount[thisPlayer], 1);
    cAssert(G.discardCount[thisPlayer], 1, flag);
    
    
    
    /*Test case #2, gaining to deck
     */
    printf("@@@@@@@@@@ Test: Gain to deck @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    toIndicat = 1;
    
    /*Should gain 1 mine to the deck*/
    printf("Card should be valid to gain\n");
    flag = cAssert(gainCard(mine, &G, toIndicat, thisPlayer), canGain, flag);
    
    printf("deck count: %d, expected: %d\n", G.deckCount[thisPlayer], 6);
    flag = cAssert(G.deckCount[thisPlayer], 6, flag);
    
    
    /*Test case #3, gaining to hand
     */
    printf("@@@@@@@@@@ Test: Gain to hand @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    toIndicat = 2;
    
    /*Should gain 1 mine to the hand*/
    printf("Card should be valid to gain\n");
    flag = cAssert(gainCard(mine, &G, toIndicat, thisPlayer), canGain, flag);
    
    printf("hand count: %d, expected: %d\n", G.handCount[thisPlayer], 6);
    flag = cAssert(G.handCount[thisPlayer], 6, flag);
    
    
    /*For these next two cases, gainCard() should return -1
     * because these are invalid gain attempts.
     */
    
    /*Test case #4, supply pile of card to be gained is empty
     */
    printf("@@@@@@@@@@ Test: Supply pile is empty @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    G.supplyCount[smithy] = 0;
    canGain = -1;
    
    printf("Card should be invalid to gain\n");
    flag = cAssert(gainCard(smithy, &G, toIndicat, thisPlayer), canGain, flag);
    
    /*Test case #5, card to be gained is not in game
     */
    printf("@@@@@@@@@@ Test: Card not in game @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    
    printf("Card should be invalid to gain\n");
    flag = cAssert(gainCard(baron, &G, toIndicat, thisPlayer), canGain, flag);
    
    
    if(flag){
		printf("\n %%%%%%%%%%%%%%%%%%%% SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTFUNC);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTFUNC);
    }
    
}
