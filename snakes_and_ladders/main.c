#include <time.h>

// Header for handling input (via cmd line args)
#include "include/utils.h"

// Header for graph functions
#include "include/graph.h"

// Header for simulation functions
#include "include/sim.h"

#define DEBUG 0

int main(int argc, char** argv){

    cli_args args = parse_args(argc, argv);

    if (DEBUG){
        printf("Num of specials: %lu\n", args.num_specials);
        for (size_t i = 0; i < args.num_specials; i++){
            if(args.specials[i]) printf("Start %lu, End %lu\n", i, args.specials[i]);
        }
    }

    // This array is soley for freeing the nodes 
    node** cleanup_board = NULL;

    node* board_start = generate_graph(args, &cleanup_board);

    free(args.specials);

    if (!board_start){
        exit(EXIT_FAILURE);
    }

    if (DEBUG) printf("Exited function. address of graph array: %p\n", (void*)cleanup_board);
    
    /*
    if (DEBUG) {
        //Printfs for checking successor pointers
        for (size_t i = 0; i < args.info.size+1; i++){
            printf("Successors for cell %lu:\n", i);
            for (size_t j = 0; j < args.info.dice; j++){
                printf("%lu: %p | ", j+1, (void*)cleanup_board[i]->successors[j]);
                if (cleanup_board[i]->special) break;
            }
            printf("\n\n");
        }
    }
    */

    srand48(time(NULL));

    sim_result* results = malloc(sizeof(sim_result) * args.sample_size);

    if (!results){
        cleanup_graph(cleanup_board, args.info);
        fprintf(stderr, "Simulation result array malloc failed!\n");
        exit(EXIT_FAILURE);
    }

    unsigned long total_rolls = 0;
    size_t fastest_sim = 0;

    for (size_t i = 0; i < args.sample_size; i++){
        results[i] = run_sim(board_start, args.info);
        if (results[i].dnf < 0){
            for (size_t j = 0; j >= 0; j--) {
                free(results[j].rolls);
            }
            fprintf(stderr, "Error allocating space for a simulation roll array!\n");
            exit(EXIT_FAILURE);
        }
        total_rolls += results[i].num_rolls;
        
        if (results[i].num_rolls < results[fastest_sim].num_rolls){
            fastest_sim = i;
        }
    }

    

    //for (size_t i = 0; i < args.sample_size; i++){
    //    total_rolls += results[i].num_rolls;
    //}

    float average_rolls = total_rolls / args.sample_size;

    printf("Results of sims:\n");
    printf("Average number of rolls to win: %.4f\n", average_rolls);
    printf("Fastest simulation:\nSimulation #%lu with %u rolls.\n", fastest_sim, results[fastest_sim].num_rolls);
    printf("Rolls in this simulation:\n|");
    for (unsigned int i = 0; i < results[fastest_sim].num_rolls; i++){
        printf(" %lu |", results[fastest_sim].rolls[i]);
    }
    printf("\n");
    /*
    if (DEBUG) {
        size_t abs_pos = 0;
        for (int i = 0; i < results.num_rolls; i++){
            if (abs_pos + results.rolls[i] <= args.info.size) abs_pos += results.rolls[i];
            printf("Roll #%d: %lu\n - Absolute pos: %lu\n", i+1, results.rolls[i], abs_pos);
        }
    }
    */

    for (size_t i = 0; i < args.sample_size; i++) {
        //printf("Num rolls #%lu: %d\n", i, results[i].num_rolls);
        free(results[i].rolls);
    }

    
    cleanup_graph(cleanup_board, args.info);

    return 0;
}
