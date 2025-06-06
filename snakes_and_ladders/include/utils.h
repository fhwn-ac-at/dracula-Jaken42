#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <getopt.h>
#include <unistd.h>

#define DEFAULT_WIDTH 10
#define DEFAULT_HEIGHT 10

typedef struct game_meta {
    int width;
    int height;
    int size;
    int dice;
} game_meta;

typedef struct cli_args {
    game_meta info;
    int** specials;
    int num_specials;
} cli_args;

/**
 * @brief Tests a given string regarding long conversion. 
 * 
 * @param optarg Target string.
 * 
 * @attention FOR parse_args(). NOT 1:1 REUSABLE!
 */
long int test_long_conversion(const char* optarg);

cli_args parse_args(int argc, char** argv);