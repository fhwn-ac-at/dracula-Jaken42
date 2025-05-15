#include <stdio.h>
#include <stdlib.h>

#define NOF_VERTICES 5
#define NOF_EDGES 6

typedef struct edge {
    int from;
    int to;
    int weight;
} edge;

void matrix_print(int size, int** matrix){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int** adjacency_matrix(int vertex_count, int edge_count, edge edge_list[edge_count]){
    int** result = malloc(sizeof(int*)*vertex_count);
    for (int i = 0; i < vertex_count; i++){
        result[i] = malloc(sizeof(int)*vertex_count);
    }

    for (int i = 0; i < edge_count; i++){
        result[edge_list[i].from][edge_list[i].to] = edge_list[i].weight;
        result[edge_list[i].to][edge_list[i].from] = -edge_list[i].weight;
    }

    return result;
}


int main(void){
    //int matrix[NOF_VERTICES][NOF_VERTICES] = { {0} };
    
    //matrix_print(NOF_VERTICES, (int**)matrix);

    edge edge_list[6] = {
        {0, 3, 2},
        {2, 1, 5},
        {4, 0, 1},
        {3, 1, 0},
        {1, 2, 3},
        {1, 4, 5}
    };

    int** result = adjacency_matrix(NOF_VERTICES, NOF_EDGES, edge_list);

    matrix_print(NOF_VERTICES, result);

    for (int i = 0; i < NOF_VERTICES; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}
