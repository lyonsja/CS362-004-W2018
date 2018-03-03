/*
 * unittest2.c
 * Testing  fullDeckCount on line 333 dominion.c
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



#define TESTFUNC "fullDeckCount"

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
    int n_copies = 0;
	int flag = 1;
	/*int i, j, m; */
	/*int handpos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0; */
	/*int remove1, remove2;*/
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
    /*int otherPlayer = 1;
    */
	struct gameState G;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	initializeGame(numPlayers, k, seed, &G);

	printf("------------------ Testing Function: %s ------------------\n", TESTFUNC);
   
    /* As implemented in dominion.c, isGameOver returns 1 when the game is over, 0 otherwise*/
    
    
    
    /*Test case, 1 copy of card in deck*/
    printf("@@@@@@@@@@ Test: 1 copy of card in deck @@@@@@@@@@\n\n");
    G.deck[thisPlayer][0] = smithy;

    n_copies = 1;
    
    flag = cAssert(fullDeckCount(thisPlayer, smithy, &G), n_copies, flag);
    
    /*Test case, there are no copies of the looked for card in the hand or deck*/
    printf("@@@@@@@@@@ Test: NO copies of card in deck @@@@@@@@@@\n\n");
    initializeGame(numPlayers, k, seed, &G);
    
    /*Set all cards in deck and hand to be coppers*/
    int q;
    for(q = 0; q < 5; q++){
        G.deck[thisPlayer][q] = copper;
    }
    for(q = 0; q < 5; q++){
            G.hand[thisPlayer][q] = copper;
    }
    
    n_copies = 0;
    
    flag = cAssert(fullDeckCount(thisPlayer, gold, &G), n_copies, flag);
    
    /*Test case, all cards in deck and hand are the looked for card*/
    printf("@@@@@@@@@@ Test: deck and hand entirely made up of card looked for @@@@@@@@@@\n\n");
    
    for(q = 0; q < 5; q++){
        G.deck[thisPlayer][q] = copper;
    }
    for(q = 0; q < 5; q++){
            G.hand[thisPlayer][q] = copper;
    }
    
    n_copies = 10;
    flag = cAssert(fullDeckCount(thisPlayer, copper, &G), n_copies, flag);
    
    
    if(flag){
		printf("\n %%%%%%%%%%%%%%%%%%%% SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTFUNC);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTFUNC);
    }
    
    
}
    
    
    
    
