CFLAGS= -Wall -fpic -coverage -lm -std=c99

runTest:
	gcc -o testme testme.c -g $(CFLAGS)
	./testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno testme
