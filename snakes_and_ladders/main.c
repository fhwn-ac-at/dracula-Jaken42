#include <time.h>

// Header for handling input (via cmd line args)
#include "include/utils.h"

// Header for graph functions
#include "include/graph.h"

int main(int argc, char** argv){

    cli_args args = parse_args(argc, argv);

    // This array is soley for freeing the nodes 
    node** cleanup_board = NULL;

    node* board_current = generate_graph(args, &cleanup_board);

    if (!board_current){
        exit(EXIT_FAILURE);
    }

    printf("Exited function. address of graph array: %p\n", cleanup_board);

    /* //Printfs for checking successor pointers
    for (int i = 0; i < board_metadata.size; i++){
        printf("Successors for cell %d:\n", i+1);
        for (int j = 0; j < board_metadata.dice; j++){
            printf("%d: %p | ", j+1, (void*)cleanup_board[i]->successors[j]);
        }
        printf("\n");
    }
    */

    srand48(time(0));

    cleanup_graph(cleanup_board, args.info.size);

    return 0;
}