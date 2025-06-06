CC = clang
CFLAGS = -Wall -Wextra --std=gnu99

all: snl.out lv.out adjacency_matrix.out

snl.out: snakes_and_ladders/main.c snakes_and_ladders/graph.c snakes_and_ladders/utils.c
	$(CC) $(CFLAGS) -o snl.out $^

lv.out:
	$(CC) $(CFLAGS) -o lv.out las_vegas/main.c

adjacency_matrix.out:
	$(CC) $(CFLAGS) -o adjacency_matrix.out adjacency_matrix/adjacency_matrix.c

clean:
	rm -f *.out

.PHONY: all clean