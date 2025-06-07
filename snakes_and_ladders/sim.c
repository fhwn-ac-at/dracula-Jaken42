#include "include/sim.h"

#define ROLL_LIMIT 1000

size_t random_roll(size_t dice_faces){
    
    // Hellish bitshifting to achieve random number as large as size_t for huge board variants
    size_t rand_size_large = ((size_t)lrand48() << 31) | (size_t)lrand48();
    
    return rand_size_large % dice_faces; 
}

sim_result run_sim(node* pos, game_meta info){
    sim_result result = {
        .dnf = 0,
        .num_rolls = 0,
        .rolls = malloc(sizeof(size_t) * ROLL_LIMIT)
    };

    if(!result.rolls){
        result.rolls = NULL;
        fprintf(stderr, "Malloc for roll array failed!\n");
        result.dnf = 1;
        return result;
    }

    struct current {
        node* field;
        size_t abs_pos;
    } current;

    current.field = pos; 
    current.abs_pos = 0;

    while (current.abs_pos != info.size && result.num_rolls < ROLL_LIMIT){
        size_t roll = random_roll(info.dice);

        if (current.field->successors[roll]){
           
            if (current.field->successors[roll]->special){

                current.field = current.field->successors[roll]->successors[0];
                current.abs_pos = current.field->successors[roll]->special;
            }  else {
            current.abs_pos += roll + 1; 
            current.field = current.field->successors[roll];
            }
        }

        result.rolls[result.num_rolls] = roll;
        result.num_rolls ++;
    }

    if (current.abs_pos != info.size) result.dnf = 1;

    return result;
}
