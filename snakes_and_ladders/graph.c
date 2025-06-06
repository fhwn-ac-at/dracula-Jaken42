#include "include/graph.h"

int debug = 1;

node* create_node(void){
    node* result = (node*)malloc(sizeof(node)); 

    if (!result){
        return NULL;
    }

    return result;
}

node* generate_graph(cli_args args, node*** meta_start){

    *meta_start = (node**)malloc(sizeof(node*)*args.info.size);
    
    for (int i = 0; i < args.info.size; i++){
        (*meta_start)[i] = create_node();
        
        // If malloc fails, free older nodes and return
        if (!(*meta_start)[i]){
            for (int j = i-1; j >= 0; j--){
                free((*meta_start)[j]);
                (*meta_start)[j] = NULL;
            }
            fprintf(stderr, "Error allocating space for graph nodes! Exiting...\n");
            return NULL;
        }
    }

    if (debug) printf("Created %d nodes\n", args.info.size);

    // Assign successors
    for (int i = 0; i < args.info.size; i++){

        // For every successor pointer, set it correctly or set it to NULL
        for (int j = 0; j < args.info.dice; j++){
            
            if (j + i < args.info.size){
                (*meta_start)[i]->successors[j] = (*meta_start)[i+1+j];
            } else {
                (*meta_start)[i]->successors[j] = NULL;
            }    
        }
        (*meta_start)[i]->is_special = 0;
    }

    if (debug) printf("Set successors for all %d nodes, returning from func\n", args.info.size);

    return (*meta_start)[0];
}

void cleanup_graph(node** target, int count){
    
    for (int i = 0; i < count; i++){
        free(target[i]);
    }
    free(target);
    if (debug) printf("Cleaning up all %d nodes\n", count);
}
