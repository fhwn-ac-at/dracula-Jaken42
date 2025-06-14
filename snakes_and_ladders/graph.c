#include "include/graph.h"

#define DEBUG 0

/**
 * @brief Allocates a graph node on the heap.
 * 
 * @param num_successors number of successors of each node, depends on number of faces on dice.
 * 
 * @return Pointer to node or NULL if malloc failed.
 */
node* create_node(size_t num_successors){
    node* result = (node*)malloc(sizeof(node)); 

    if (!result){
        return NULL;
    }

    result->successors = malloc(sizeof(node*) * num_successors);

    if (!result->successors){
        free(result);
        return NULL;
    }

    result->times_touched = 0;

    return result;
}

node* generate_graph(cli_args args, node*** graph_array){

    *graph_array = (node**)malloc(sizeof(node*) * (args.info.size+1));
    
    if (!(*graph_array)){
        fprintf(stderr, "Error allocating space for node array! Exiting...\n");
        return NULL;
    }

    // Allocate space for Nodes
    for (size_t i = 0; i < args.info.size+1; i++){
        (*graph_array)[i] = create_node(args.info.dice);
        
        // If malloc fails, free older nodes and return
        if (!(*graph_array)[i]){
            for (size_t j = i-1; j >= 0; j--){
                
                for (size_t k = 0; k < args.info.dice; k++){
                    free((*graph_array)[j]->successors[k]);
                }
                free((*graph_array)[j]);
                (*graph_array)[j] = NULL;
            }
            free(graph_array);
            free(args.specials);
            fprintf(stderr, "Error allocating space for graph nodes! Exiting...\n");
            return NULL;
        }
    }

    if (DEBUG) printf("Created %lu nodes\n", args.info.size+1);

    // Assign successors for i
    for (size_t i = 0; i < args.info.size+1; i++){

        if (i > 0 && args.specials[i-1]){
            (*graph_array)[i]->successors[0] = (*graph_array)[args.specials[i-1]];
            (*graph_array)[i]->special = args.specials[i-1];

        } else {

        // For every successor pointer, set it correctly or set it to NULL if out of bounds
            for (size_t j = 0; j < args.info.dice; j++){
                
                if (j + i < args.info.size){
                    (*graph_array)[i]->successors[j] = (*graph_array)[i+1+j];
                } else {
                    (*graph_array)[i]->successors[j] = NULL;
                }
                
                (*graph_array)[i]->special = 0;
            }
        }
    }

    if (DEBUG) printf("Set successors for all %lu nodes, returning from func\n", args.info.size+1);

    return (*graph_array)[0];
}

void cleanup_graph(node** target, game_meta info){
    
    for (size_t i = 0; i < info.size+1; i++){
        
        free(target[i]->successors);
        free(target[i]);
    }

    if (DEBUG) printf("Cleaning up all %lu nodes\n", info.size+1);
}
