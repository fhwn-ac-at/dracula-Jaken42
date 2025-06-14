#include <time.h>

// Header for handling input (via cli args)
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

    // This array is for freeing the nodes and for finding snakes and ladders later for printing
    node** cleanup_board = NULL;

    node* board_start = generate_graph(args, &cleanup_board);

    if (!board_start){
        exit(EXIT_FAILURE);
    }

    if (DEBUG) printf("Exited function. address of graph array: %p\n", (void*)cleanup_board);

    srand48(time(NULL));

    sim_result* results = malloc(sizeof(sim_result) * args.sample_size);

    if (!results){
        free(args.specials);
        cleanup_graph(cleanup_board, args.info);
        free(cleanup_board);
        fprintf(stderr, "Simulation result array malloc failed!\n");
        exit(EXIT_FAILURE);
    }

    unsigned long total_rolls = 0;  // Only from winning simulations
    unsigned long total_wins = 0;
    size_t fastest_sim = 0;

    for (size_t i = 0; i < args.sample_size; i++){
        results[i] = run_sim(board_start, args.info, args.roll_limit, args.distribution);
        
        // If sim error
        if (results[i].dnf < 0){
            for (size_t j = 0; j >= 0; j--) {
                free(results[j].rolls);
            }
            free(args.specials);
            cleanup_graph(cleanup_board, args.info);
            free(cleanup_board);
            fprintf(stderr, "Error allocating space for a simulation roll array!\n");
            exit(EXIT_FAILURE);
        }

        // If sim success, add num rolls to total roll counter
        if (!results[i].dnf){
            total_rolls += results[i].num_rolls;
            total_wins++;
        } 
        
        // Replace fastest sim if applicable
        if (!results[i].dnf && ((i > 0 && fastest_sim == 0) || results[i].num_rolls < results[fastest_sim].num_rolls)){
            fastest_sim = i+1;
        }
    }

    double average_rolls = (double)total_rolls / total_wins;

    printf("+-----------------------+\n| Simulation statistics |\n+-----------------------+\n|\n");
    printf("| Sample size: %lu\n", args.sample_size);
    printf("| Board size: %lu x %lu\n", args.info.width, args.info.height);
    printf("| Dice size: %lu\n", args.info.dice);
    printf("| Dice roll limit: %lu\n", args.roll_limit);
    printf("| Amount of snakes and ladders: %lu\n", args.num_specials);
    if (!fastest_sim){
        printf("| No simulation got to the finish!\n+------------------------------------------------------------------------------------+");
    } else {
        printf("+------------------------------------------------------------------------------------+\n|\n");
        printf("| Average number of rolls to win: %.4f\n", average_rolls);
        printf("| Fastest simulation:\n| Simulation #%lu with %u rolls\n", fastest_sim-1, results[fastest_sim-1].num_rolls);
        printf("| Rolls in this simulation:\n|");
        for (unsigned int i = 0; i < results[fastest_sim-1].num_rolls; i++){
            printf(" %lu ", results[fastest_sim-1].rolls[i]);
            
            if (i+1 < results[fastest_sim-1].num_rolls) printf("->");
            
            if ((i + 1) % 9 == 0) printf("\n|");
        }
        printf("\n+------------------------------------------------------------------------------------+");

    }

    printf("\n");

    if (args.num_specials){

        printf("|\n| List of snakes and Ladders and times they were touched (Total %lu):\n", args.num_specials);
        
        // Get snake statistics, save in variables
        size_t snake_counter = 0;
        size_t snake_touch_total = 0;
        for (size_t i = 0; i < args.info.size; i++){
            if (!args.specials[i] || i < args.specials[i]) continue;
            snake_touch_total += cleanup_board[args.specials[i]]->times_touched;
        }

        // Print snake statistics
        for (size_t i = 0; i < args.info.size; i++){
            if (!args.specials[i] || i < args.specials[i]) continue;
            
            snake_counter++;
            printf("| Snake #%lu (From %lu to %lu) - ", snake_counter, i+1, args.specials[i]+1);
            if (cleanup_board[args.specials[i]]->times_touched){
                printf("Touched %lu times in total (%.2f%% of all snake traversals)\n", cleanup_board[args.specials[i]]->times_touched, ((float)cleanup_board[args.specials[i]]->times_touched / snake_touch_total) * 100.0f);
            } else {
                printf("Never touched\n");
            }
        }

        // Get snake statistics, save in varaibles
        size_t ladder_counter = 0;
        size_t ladder_touch_total = 0;
        for (size_t i = 0; i < args.info.size; i++){
            if (!args.specials[i] || i > args.specials[i]) continue;
            ladder_touch_total += cleanup_board[args.specials[i]]->times_touched;
        }

        // Print ladder statistics
        for (size_t i = 0; i < args.info.size; i++){
            if (!args.specials[i] || i > args.specials[i]) continue;
            
            ladder_counter++;
            
            printf("| Ladder #%lu (From %lu to %lu) - ", ladder_counter, i+1, args.specials[i]+1);
            if (cleanup_board[args.specials[i]]->times_touched){
                printf("Touched %lu times in total (%.2f%% of all ladder traversals)\n", cleanup_board[args.specials[i]]->times_touched, ((float)cleanup_board[args.specials[i]]->times_touched / ladder_touch_total) * 100.0f);
            } else {
                printf("Never touched\n");
            }
        }

        printf("+------------------------------------------------------------------------------------+\n");
    }

    
    for (size_t i = 0; i < args.sample_size; i++) {
        free(results[i].rolls);
    }
    free(args.specials);
    cleanup_graph(cleanup_board, args.info);
    free(cleanup_board);

    return 0;
}
