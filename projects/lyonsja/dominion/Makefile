CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtests: randomtestcard1.c dominion.c rngs.c interface.c dominion.o rngs.o dominion.h rngs.h interface.h randomtestcard1
	
	gcc -c rngs.c -g
	gcc -c dominion.c -g
	gcc -c interface.c -g
		
	echo "randomtestcard1 test results: " > randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov -abcfu dominion.c >> randomtestcard1.out
	rm dominion.gcda
	
#	gcc -c dominion.c -g $(CFLAGS)
#	echo "randomtestcard2 test results: " > randomtestcard2.out
#	gcc -o randomtestcard2 randomtestcard2.c -lm dominion.o rngs.o
#	./randomtestcard2 >> randomtestcard2.out
#	rm dominion.gcda
	
#	gcc -c dominion.c -g $(CFLAGS)
#	echo "randomtestadventurer test results: " > randomtestadventurer.out
#	gcc -o randomtestadventurer randomtestadventurer.c -lm dominion.o rngs.o
#	./randomcardtestadventurer >> randomtestadventurer.out	


unittestresults.out: dominion.c dominion.h rngs.h rngs.c interface.c interface.h cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	
	gcc -c rngs.c -g  $(CFLAGS)
	gcc -c dominion.c -g  $(CFLAGS)
	gcc -c interface.c -g  $(CFLAGS)
	
	echo "Result of all card and unit tests: " > unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out
	rm dominion.gcda
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS) 
	./unittest2 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out
	rm dominion.gcda
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out
	rm dominion.gcda
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out
	rm dominion.gcda
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out
	rm dominion.gcda
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out
	rm dominion.gcda
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out
	rm dominion.gcda
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -abcfu dominion.c >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard1
