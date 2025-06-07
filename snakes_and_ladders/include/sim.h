#pragma once

#include "graph.h"
#include "utils.h"

typedef struct sim_result {
    size_t* rolls;
    unsigned int num_rolls;
    int dnf;
} sim_result;

/**
 * @brief Runs a game sim and returns statistics of the run.asm
 * 
 * @param pos Starting position.
 * @param game_info Metadata on the board and game.
 * 
 * @returns sim_result struct with dice sequence, num of rolls and an int designating success (0) or failure (1).
 */
sim_result run_sim(node* pos, game_meta game_info, size_t roll_limit);
