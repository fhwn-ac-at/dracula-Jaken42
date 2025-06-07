#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct node node;

struct node {
    node** successors;
    size_t special;
};

/**
 * @brief Generates the graph representation of the game board.
 * 
 * @param args CLI args from parse_args() (see utils.h). Contains board info, snake and ladder positions and number of snakes and ladders.
 * @param meta_start Pointer to an array of node pointers. An array of pointers to all nodes is saved into this parameter. Used for freeing memory via cleanup_graph().  
 * 
 * @return Pointer to first node on board or NULL if error occured.
 */
node* generate_graph(cli_args args, node*** meta_start);

/**
 * @brief frees all nodes (n = count) from node pointer array followed by the array itself. 
 * 
 * @param target Target array to free.
 * @param count Length of target array.
 */
void cleanup_graph(node** target, game_meta info);
