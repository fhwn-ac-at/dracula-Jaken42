CC = clang
CFLAGS = -Wall -Wextra --std=c17

all: adjacency_matrix.out

adjacency_matrix.out:
	$(CC) $(CFLAGS) -o adjacency_matrix.out adjacency_matrix/adjacency_matrix.c

clean:
	rm -f *.out

.PHONY: all clean