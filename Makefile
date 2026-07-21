CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

heman: main.c
	$(CC) $(CFLAGS) -o heman main.c
