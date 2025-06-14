#pragma once

#include <math.h>

#include "graph.h"
#include "utils.h"

/**
 * @brief Struct of results of a game simulation.
 */
typedef struct sim_result {
    size_t* rolls;              /**< Array of rolls taken during simulation. */
    unsigned int num_rolls;     /**< Number of rolls taken during simulation. */
    int dnf;                    /**< Integer designating either an error (-1), sim success (0) or sim failure (1) */
} sim_result;

/**
 * @brief Runs a game sim and returns statistics of the run.asm
 * 
 * @param pos Starting position.
 * @param game_info Metadata on the board and game.
 * @param dice_bias Flag do determine if a bias should be introduced into the RNG, and if so, where the bias should lie.
 * 
 * @returns sim_result struct with dice sequence, num of rolls and an int designating error (-1)m, success (0) or failure (1).
 */
sim_result run_sim(node* pos, game_meta game_info, size_t roll_limit, int dice_bias);
