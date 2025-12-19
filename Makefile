CFLAGS=-Wall -Wextra -g -lm
hashtable: hashtable.c
	gcc hashtable.c $(CFLAGS) -o hashtable
