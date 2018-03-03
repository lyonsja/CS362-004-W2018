/*
 * unittest1.c
 * Testing isGameOver on line 399 dominion.c
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define TESTFUNC "isGameOver"

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
	/*int thisPlayer = 0;
    int otherPlayer = 1;
    */
	struct gameState G;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	initializeGame(numPlayers, k, seed, &G);

	printf("------------------ Testing Function: %s ------------------\n", TESTFUNC);
   
    /* As implemented in dominion.c, isGameOver returns 1 when the game is over, 0 otherwise*/
    
    
    
    /*Test case, no supply piles empty--game should continue*/
    printf("@@@@@@@@@@ Test: NO empty supply piles @@@@@@@@@@\n\n");
    
    flag = cAssert(isGameOver(&G), 0, flag);
    
    
    /*Test case, 1 (non-province) supply pile empty--game should continue*/
    printf("@@@@@@@@@@ Test: 1 empty supply pile @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    
    G.supplyCount[mine] = 0;
    flag = cAssert(isGameOver(&G), 0, flag);
    
    
    
    
    /*Test case, 2 (non-province) supply piles empty--game should continue*/
    printf("@@@@@@@@@@ Test: 2 empty supply piles @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    G.supplyCount[adventurer] = 0;
    G.supplyCount[village] = 0;

    flag = cAssert(isGameOver(&G), 0, flag);
    
    
    
    /*Test case, 3 (non-province) supply piles empty--game should end*/
    printf("@@@@@@@@@@ Test: 3 empty supply piles @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    G.supplyCount[adventurer] = 0;
    G.supplyCount[village] = 0;
    G.supplyCount[tribute] = 0;

    flag = cAssert(isGameOver(&G), 1, flag);
    
   
    /*Test case, 4 (non-province) supply piles empty--game should end*/
    printf("@@@@@@@@@@ Test: 4 empty supply piles @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    G.supplyCount[adventurer] = 0;
    G.supplyCount[village] = 0;
    G.supplyCount[tribute] = 0;
    G.supplyCount[silver] = 0;

    flag = cAssert(isGameOver(&G), 1, flag);


    /*Test case, province pile empty--game should end*/
    printf("@@@@@@@@@@ Test: province pile empty @@@@@@@@@@\n\n");
    G.supplyCount[province] = 0;
    
    flag = cAssert(isGameOver(&G), 1, flag);
    
    if(flag){
		printf("\n %%%%%%%%%%%%%%%%%%%% SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTFUNC);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTFUNC);
    }
    
    
}
    
    
    
    
