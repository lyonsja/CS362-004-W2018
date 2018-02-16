/*
 * randomtestadventurer.c
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
	int shuffledCards = 0;
    int drawnCards = 0;
	int flag = 1;
	/*int i, j, m; */
	int handpos = 0, bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
	/*int seed = 1000;*/
	int numPlayers = 2;
	struct gameState G, testG;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


    SelectStream(5);
    PutSeed(7);

	/*initializeGame(numPlayers, k, seed, &G);*/

	printf("------------------ Testing Card: %s ------------------\n", TESTCARD);

    int p; /*Player*/
    int q, i;
    int z; /*Counter for tmpHand*/
    int numTreasDrawn;
    int tmpHand[MAX_HAND];
    /*Randomize Game State */



    for(q = 0; q < 2000; q++){
        for(i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G[i] = floor(Random() * 256 ));
        }









    }
    memcpy(&testG, &G, sizeof(struct gameState));
    





	result = playAdventurer(p, testG, )
   /* shuffledCards = 5; */



   /*Check number of treasure cards in deck, discard*/




    
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer],
			G.handCount[thisPlayer] - discarded);
    flag = cAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded, flag);
    
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer],
			G.deckCount[thisPlayer] - shuffledCards);
    /*Should cycle through deck filled w/estates, resulting in empty deck and all estates in discard pile */
	flag = cAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - shuffledCards, flag);

    
    /*Test case where only 1 treasure in deck*/
    
    
	if(flag){
		printf("\n %%%%%%%%%%%%%%%%%%%%SUCCESS: TESTING COMPLETE %s %%%%%%%%%%%%%%%%%%%%\n\n", TESTCARD);
	}
	else{
        printf("\n >>>>> TEST FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);
    }
	return 0;


}
