/*
 * unittest4.c
 * Testing  buyCard on line 281 dominion.c
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define TESTFUNC "buyCard"

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
       
    
    
    /*Test case, no supply piles empty--game should continue*/
    printf("@@@@@@@@@@ Test: NO buys left @@@@@@@@@@\n\n");
    G.numBuys = 0;
    
    
    flag = cAssert(buyCard(&G), 0, flag);
    
    
    
    
    
    printf("@@@@@@@@@@ Test: NO buys left @@@@@@@@@@\n\n");
    
    printf("@@@@@@@@@@ Test: NO cards left @@@@@@@@@@\n\n");
    
    
    printf("@@@@@@@@@@ Test: Insufficient buying power @@@@@@@@@@\n\n");
    
    
    printf("@@@@@@@@@@ Test: valid buy from supply @@@@@@@@@@\n\n");
    
    
    
    
    
    
    
  if(flag){
		printf("\n %%%%%%%%%%%%%%%%%%%% SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTFUNC);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTFUNC);
    }  
    
}
    
