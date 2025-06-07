#pragma once

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

typedef struct cli_args {
    game_meta info;
    size_t* specials;
    size_t num_specials;
    size_t sample_size;
    size_t roll_limit;
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
