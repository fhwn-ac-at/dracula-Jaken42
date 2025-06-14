#include "include/sim.h"

size_t random_roll(size_t dice_faces){
    
    if (dice_faces == 1){
        return 0;
    }

    // drand48 returns a double between 0 and 1. multiply to get one of the dice faces
    return (size_t)(drand48() * dice_faces); 
}

sim_result run_sim(node* pos, game_meta info, size_t roll_limit){
    
    sim_result result = {
        .dnf = 0,
        .num_rolls = 0,
        .rolls = malloc(sizeof(size_t) * roll_limit)
    };

    if(!result.rolls){
        result.rolls = NULL;
        fprintf(stderr, "Malloc for roll array failed!\n");
        result.dnf = -1;
        return result;
    }

    struct current {
        node* field;
        size_t abs_pos;
    } current;

    current.field = pos; 
    current.abs_pos = 0;

    // Main rolling loop
    while (current.abs_pos != info.size && result.num_rolls < roll_limit){
        size_t roll = random_roll(info.dice);

        // If the roll is not out of bounds...
        if (current.field->successors[roll] != NULL){
           
            // If the field we landed on is a snake or ladder
            if (current.field->successors[roll]->special){
                
                // Get new abs position and follow the special path
                current.abs_pos = current.field->successors[roll]->special;
                current.field = current.field->successors[roll]->successors[0];

                // THIS WILL (probably) CAUSE CONCURRENCY ISSUES!
                current.field->times_touched += 1;
            
            }  else {
                current.abs_pos += roll + 1; 
                current.field = current.field->successors[roll];
            }
        }

        result.rolls[result.num_rolls] = roll + 1;
        result.num_rolls++;
    }

    if (current.abs_pos != info.size) result.dnf = 1;

    return result;
}
