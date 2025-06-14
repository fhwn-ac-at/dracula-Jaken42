CC = clang
CFLAGS = -Wall -Wextra -pedantic --std=gnu99
file = snakes_and_ladders/example/default

file1 = snakes_and_ladders/example/normal_board
file2 = snakes_and_ladders/example/oneshot
file3 = snakes_and_ladders/example/whoops_all_1s
file4 = snakes_and_ladders/example/impossible_difficulty
file5 = snakes_and_ladders/example/coin_toss
file6 = snakes_and_ladders/example/infinite_loop
file7 = snakes_and_ladders/example/low_bias
file8 = snakes_and_ladders/example/mid_bias
file9 = snakes_and_ladders/example/high_bias

all: snl.out lv.out adjacency_matrix.out

snl.out: snakes_and_ladders/main.c snakes_and_ladders/graph.c snakes_and_ladders/utils.c snakes_and_ladders/sim.c
	$(CC) $(CFLAGS) -o snl.out $^ -lm

lv.out:
	$(CC) $(CFLAGS) -o lv.out las_vegas/main.c

adjacency_matrix.out:
	$(CC) $(CFLAGS) -o adjacency_matrix.out adjacency_matrix/adjacency_matrix.c

clean:
	rm -f *.out

# Runs with a default preset board from the default file
run:
	./snl.out $(shell cat $(file))

# Runs with an example preset board from the default file
run1:
	./snl.out $(shell cat $(file1))

# Runs with a board that forces a 100 roll on a d100.
run2:
	./snl.out $(shell cat $(file2))

# Runs with a board that forces 100 rolls with a d1.
run3:
	./snl.out $(shell cat $(file3))

# Runs a board that can never finish due to the set limit and the dice and board sizes.
run4:
	./snl.out $(shell cat $(file4))

# Runs with a board that simulates doing a coin toss until you get a certain side.
run5:
	./snl.out $(shell cat $(file5))

# Runs with a board that causes an infinite loop with snakes camping the exit.
run6:
	./snl.out $(shell cat $(file6))

# Runs with a normal example board with bias towards lower numbers.
run7:
	./snl.out $(shell cat $(file7))

# Runs with a normal example board with bias towards center numbers.
run8:
	./snl.out $(shell cat $(file8))

# Runs with a normal example board with bias towards higher numbers.
run9:
	./snl.out $(shell cat $(file9))

.PHONY: all clean