#include "include/graph.h"

int debug = 1;

/**
 * @brief Allocates a graph node on the heap.
 * @return Pointer to node or NULL if malloc failed.
 */
node* create_node(void){
    node* result = (node*)malloc(sizeof(node)); 

    if (!result){
        return NULL;
    }

    return result;
}

node* generate_graph(cli_args args, node*** meta_start){

    *meta_start = (node**)malloc(sizeof(node*) * (args.info.size+1));
    
    for (size_t i = 0; i < args.info.size+1; i++){
        (*meta_start)[i] = create_node();
        
        // If malloc fails, free older nodes and return
        if (!(*meta_start)[i]){
            for (size_t j = i-1; j >= 0; j--){
                free((*meta_start)[j]);
                (*meta_start)[j] = NULL;
            }
            free(args.specials);
            fprintf(stderr, "Error allocating space for graph nodes! Exiting...\n");
            return NULL;
        }
    }

    if (debug) printf("Created %lu nodes\n", args.info.size);

    // Assign successors for i
    for (size_t i = 0; i < args.info.size+1; i++){

        if (i > 0 && args.specials[i-1]){
            (*meta_start)[i]->successors[0] = (*meta_start)[args.specials[i-1]];
            (*meta_start)[i]->special = args.specials[i-1];

        } else {

        // For every successor pointer, set it correctly or set it to NULL if out of bounds
            for (size_t j = 0; j < args.info.dice+1; j++){
                
                if (j + i < args.info.size){
                    (*meta_start)[i]->successors[j] = (*meta_start)[i+1+j];
                } else {
                    (*meta_start)[i]->successors[j] = NULL;
                }
                
                (*meta_start)[i]->special = 0;
            }
        }
    }

    if (debug) printf("Set successors for all %lu nodes, returning from func\n", args.info.size);

    return (*meta_start)[0];
}

void cleanup_graph(node** target, int count){
    
    for (int i = 0; i < count; i++){
        if (target[i]) free(target[i]);
    }

    if (debug) printf("Cleaning up all %d nodes\n", count);
}
