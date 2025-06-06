#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct node {
    struct node* successors[6];
    int is_special;
} node;

/**
 * @brief Allocates a graph node on the heap.
 * @return Pointer to node or NULL if malloc failed.
 */
node* create_node(void);

/**
 * @brief Generates the graph representation of the game board.
 * 
 * @param info CLI args from utils.h. Contain board info, snake info and ladder info.
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
void cleanup_graph(node** target, int count);
