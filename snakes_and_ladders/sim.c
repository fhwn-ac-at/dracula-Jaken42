#include "include/sim.h"

/**
 * @brief Rolls a random number for a dice with a given number of faces
 * 
 * @param dice_faces Size of dice.
 * @param bias Determines where the bias lies. |
 * 1: Lower numbers |
 * 2: Center numbers |
 * 3: Higher numbers |
 * 
 * @returns Random number with given bias.
 */
size_t random_roll(size_t dice_faces, int bias) {

    if (dice_faces == 1){
        return 0;
    }

    double factor = drand48();

    switch (bias){
        
        case UNBIASED:
            break;

        // Bias towards lower numbers
        case 1:
            factor = pow(factor, 2);
            break;

        // Bias towards center numbers (bell curve)
        case 2:
            factor = (drand48() + drand48() + drand48() + drand48() + drand48()) / 5.0;
            break;
            
        // Bias towards higher numbers
        case 3:
            factor = 1.0 - pow(1.0 - factor, 2);
            break;
    }

    return (size_t)(factor * dice_faces);
}

sim_result run_sim(node* pos, game_meta info, size_t roll_limit, int dice_bias){
    
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
        size_t roll;
        
        roll = random_roll(info.dice, dice_bias);
        

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
