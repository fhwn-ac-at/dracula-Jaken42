CC = clang
CFLAGS = -Wall -Wextra -pedantic --std=gnu99

all: snl.out lv.out adjacency_matrix.out

snl.out: snakes_and_ladders/main.c snakes_and_ladders/graph.c snakes_and_ladders/utils.c snakes_and_ladders/sim.c
	$(CC) $(CFLAGS) -o snl.out $^

lv.out:
	$(CC) $(CFLAGS) -o lv.out las_vegas/main.c

adjacency_matrix.out:
	$(CC) $(CFLAGS) -o adjacency_matrix.out adjacency_matrix/adjacency_matrix.c

clean:
	rm -f *.out

run:
	./snl.out -w 5 -h 5 -d 5 -s 10 20 -s 24 5 -s 11 6 -s 9 23

.PHONY: all clean