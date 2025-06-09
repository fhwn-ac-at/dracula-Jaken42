CC = clang
CFLAGS = -Wall -Wextra -pedantic --std=gnu99
file =? snakes_and_ladders/example/default

file1 = snakes_and_ladders/example/normal_board
file2 = snakes_and_ladders/example/oneshot
file3 = snakes_and_ladders/example/whoops_all_1s
file4 = snakes_and_ladders/example/impossible_difficulty

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
	./snl.out $(shell cat $(file))

run1:
	./snl.out $(shell cat $(file1))

run2:
	./snl.out $(shell cat $(file2))

run3:
	./snl.out $(shell cat $(file3))

run4:
	./snl.out $(shell cat $(file4))

.PHONY: all clean