all:
	gcc -Wall -ansi -pedantic -O2 -o wordsindex wordsindex.c linkedlists.h linkedlists.c

wordsindex:
	gcc -Wall -ansi -pedantic -O2 -o wordsindex wordsindex.c linkedlists.h linkedlists.c

clean:
	-rm wordsindex