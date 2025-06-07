#include <time.h>

// Header for handling input (via cmd line args)
#include "include/utils.h"

// Header for graph functions
#include "include/graph.h"

// Header for simulation functions
#include "include/sim.h"

int main(int argc, char** argv){

    cli_args args = parse_args(argc, argv);

    printf("Num of specials: %lu\n", args.num_specials);
    for (size_t i = 0; i < args.num_specials; i++){
        if(args.specials[i]) printf("Start %lu, End %lu\n", i, args.specials[i]);
    }

    // This array is soley for freeing the nodes 
    node** cleanup_board = NULL;

    node* board_start = generate_graph(args, &cleanup_board);

    free(args.specials);

    if (!board_start){
        exit(EXIT_FAILURE);
    }

    printf("Exited function. address of graph array: %p\n", (void*)cleanup_board);

    //Printfs for checking successor pointers
    for (size_t i = 0; i < args.info.size+1; i++){
        printf("Successors for cell %lu:\n", i);
        for (size_t j = 0; j < args.info.dice; j++){
            printf("%lu: %p | ", j+1, (void*)cleanup_board[i]->successors[j]);
            if (cleanup_board[i]->special) break;
        }
        printf("\n\n");
    }
    

    srand48(time(0));

    sim_result results = run_sim(board_start, args.info);

    printf("Results of sim:\n");
    printf("Number of rolls: %d\n", results.num_rolls);
    if (results.dnf) printf("Did not finish!\n"); else printf("Finished successfully!\n");

    if (results.rolls) free(results.rolls);

    cleanup_graph(cleanup_board, args.info.size+1);

    return 0;
}
