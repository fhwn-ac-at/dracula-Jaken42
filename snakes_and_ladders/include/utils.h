#pragma once

// For an include
#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

// This one is exclusively for SIZE_MAX
#include <stdint.h>

#include <getopt.h>
#include <unistd.h>

#define DEFAULT_WIDTH 10
#define DEFAULT_HEIGHT 10
#define DEFAULT_DICE_FACES 6

#define UNBIASED 0

// Limit on how many rolls a sim may attempt
#define DEFAULT_ROLL_LIMIT 1000

#define DEFAULT_SAMPLE_SIZE 1000

typedef struct game_meta {
    size_t width;
    size_t height;
    size_t size;
    size_t dice;
} game_meta;

typedef struct special_pos{
    size_t start;
    size_t end;
} special_pos;

/**
 * @brief Struct of results of CLI parsing. Contains parameters for the board and the simulation.
 */
typedef struct cli_args {
    game_meta info;         /**< Struct that contains information on the board or dice. */
    size_t* specials;       /**< Array that stores snake and ladder locations and destinations. For instance, if there is a ladder on cell 0 going to cell 10, specials[0] will be 10. */
    size_t num_specials;    /**< Number of specials. */
    size_t sample_size; 	/**< Number of simulation runs. */
    size_t roll_limit;      /**< Limit of rolls per simulation. */
    int distribution;       /**< Designates distribution of dice. | 0 is uniform and default | 1 is bias to lower numbers | 2 is bias to center numbers | 3 is bias to higher numbers |*/
} cli_args;

/**
 * @brief Gets CLI arguments.
 * 
 * @param argc Number of CLI arguments.
 * @param argv Array of CLI arguments.
 * 
 * @returns Struct that is further used for graph creation. Exits program on its own if an error occured.
 */
cli_args parse_args(int argc, char** argv);
