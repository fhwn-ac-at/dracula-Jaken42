#include "include/utils.h"

/**
 * @brief Tests a given string regarding size_t conversion. 
 * 
 * @param optarg Target string.
 * 
 * @returns The number. success is set to a non-zero value if an error occured.
 * 
 * @attention For parse_args(). NOT REUSABLE!
 */
size_t test_size_conversion(char* optarg, int* error){

    char* end_ptr = optarg; 
    errno = 0;

    while(*end_ptr == ' ' || *end_ptr == '\t' || *end_ptr == '\n'){
        end_ptr++;
    }

    if(*end_ptr == '-'){
        fprintf(stderr, "No parameters may be smaller than 1!\n");
        (*error)++;
        return 0;
    }
    
    unsigned long long test = strtoul(optarg, &end_ptr, 10);
    
    if (test == 0){
        fprintf(stderr, "No parameters may be smaller than 1!\n");
        (*error)++;
        return 0;
    }

    while(*end_ptr == ' ' || *end_ptr == '\t' || *end_ptr == '\n'){
        end_ptr++;
    }

    if (*end_ptr != '\0' || end_ptr == optarg){
        fprintf(stderr, "Parameter is invalid!\n");
        (*error)++;
        return 0;
    }

    if ((test == ULLONG_MAX && errno == ERANGE) || test > SIZE_MAX){
        fprintf(stderr, "Parameter caused overflow!\n");
        (*error)++;
        return 0;
    }

    return (size_t)test;
}

cli_args parse_args(int argc, char** argv){
    cli_args args = {
        .info.width = DEFAULT_WIDTH,
        .info.height = DEFAULT_HEIGHT,
        .info.size = DEFAULT_WIDTH * DEFAULT_HEIGHT,
        .info.dice = DEFAULT_DICE_FACES,
        .specials = NULL,
        .num_specials = 0,
        .sample_size = DEFAULT_SAMPLE_SIZE,
        .roll_limit = DEFAULT_ROLL_LIMIT,
        .distribution = UNBIASED
    };
    
    int opt;

    special_pos* temp_special_array = NULL;

    int check_error = 0;
    
    while((opt = getopt(argc, argv, "w:h:d:u:r:n:s:")) != -1){
        
        switch (opt) {
            case -1:
                //printf("Arg reading done.\n");
                break;

            // Board width
            case 'w':

                args.info.width = test_size_conversion(optarg, &check_error);
                if (check_error){
                    if (temp_special_array) free(temp_special_array);
                    exit(EXIT_FAILURE);
                }
                break;
            
            // Board height
            case 'h':
                args.info.height = test_size_conversion(optarg, &check_error);
                if (check_error){
                    if (temp_special_array) free(temp_special_array);
                    exit(EXIT_FAILURE);
                }
                break;
            
            // Num of dice faces
            case 'd':
                args.info.dice = test_size_conversion(optarg, &check_error);
                if (check_error){
                    if (temp_special_array) free(temp_special_array);
                    exit(EXIT_FAILURE);
                }
                break;
            
            // Flag for normal distribution, 1 for start, 2 for center, 3 for end bias
            case 'u':
                args.distribution = (int)test_size_conversion(optarg, &check_error);
                if (check_error){
                    if (temp_special_array) free(temp_special_array);
                    exit(EXIT_FAILURE);
                }

                if (args.distribution > 3){
                    if (temp_special_array) free(temp_special_array);
                    fprintf(stderr, "-u requires a valid number between 1 and 3 as an argument!\n\t1 - Bias to lower numbers\n\t2 - Bias to center numbers\n\t3 - Bias to higher numbers\n");
                }

                break;
            
            // Random roll limit before attempts are aborted
            case 'r':

                args.roll_limit = test_size_conversion(optarg, &check_error);
                if (check_error){
                    if (temp_special_array) free(temp_special_array);
                    exit(EXIT_FAILURE);
                }
                break;
            
            // Sample size
            case 'n':

                args.sample_size = test_size_conversion(optarg, &check_error);
                if (check_error){
                    if (temp_special_array) free(temp_special_array);
                    exit(EXIT_FAILURE);
                }
                break;

            // A special declaration. can either be snake or ladder. 
            // Puts it in a malloc'd array of a special type. 
            // Must be processed in a separate function.
            case 's':
                if (optind >= argc || optopt == 's'){
                    if (temp_special_array) free(temp_special_array);
                    fprintf(stderr, "-s requires two arguments!\n");
                    exit(EXIT_FAILURE);
                }
 
                args.num_specials++;

                if (temp_special_array == NULL){
                    temp_special_array = malloc(sizeof(special_pos));
                    if (!temp_special_array){
                        fprintf(stderr, "Malloc for snake and ladder array failed! Exiting...\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    special_pos* test = realloc(temp_special_array, sizeof(special_pos) * args.num_specials);
                    if (!test){
                        free(temp_special_array);
                        fprintf(stderr, "Realloc for snake and ladder array failed! Exiting...\n");
                        exit(EXIT_FAILURE);
                    }
                }

                temp_special_array[args.num_specials-1].start = test_size_conversion(optarg, &check_error);
                temp_special_array[args.num_specials-1].end = test_size_conversion(argv[optind++], &check_error);

                if (check_error){
                    free(temp_special_array);
                    exit(EXIT_FAILURE);
                }

                if (temp_special_array[args.num_specials-1].start == temp_special_array[args.num_specials-1].end){
                    free(temp_special_array);
                    fprintf(stderr, "A snake or ladder cannot end in the same field it starts in!\n");
                    exit(EXIT_FAILURE);
                }

                if (temp_special_array[args.num_specials-1].start == temp_special_array[args.num_specials-1].end){
                    free(temp_special_array);
                    fprintf(stderr, "A snake or ladder cannot end in the same field it starts in!\n");
                    exit(EXIT_FAILURE);
                }

                for (size_t i = 0; i < args.num_specials-1; i++){
                    if (temp_special_array[args.num_specials-1].start == temp_special_array[i].start || 
                        temp_special_array[args.num_specials-1].start == temp_special_array[i].end ||
                        temp_special_array[args.num_specials-1].end == temp_special_array[i].start || 
                        temp_special_array[args.num_specials-1].end == temp_special_array[i].end){

                        free(temp_special_array);
                        fprintf(stderr, "No two snakes or ladders can start or end in the same field!\n");
                        exit(EXIT_FAILURE);
                    }
                }

                break;

            case '?':
                if (temp_special_array) free(temp_special_array);
                fprintf(stderr, "Usage: %s [-w <width>] [-h <height>] [-d <die faces>] [-r <simulation roll limit>] [-n number of simulations] [-s <special end 1> <special end 2>]\n", argv[0]);
                exit(EXIT_FAILURE);
            
            case ':':
                if (temp_special_array) free(temp_special_array);
                fprintf(stderr, "Missing argument for option -%c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }

    // Overflow check for size
    if (args.info.width > SIZE_MAX / args.info.height){
        if (temp_special_array) free(temp_special_array);
        fprintf(stderr, "Board size too large! please do not make a board with more than %lu fields\n", SIZE_MAX);
        exit(EXIT_FAILURE);
    }

    args.info.size = args.info.width * args.info.height;
    
    // making the snake and ladder array
    args.specials = malloc(sizeof(size_t) * args.info.size);
    if (!args.specials){
        if (temp_special_array) free(temp_special_array);
        fprintf(stderr, "Board size too large! please do not make a board with more than %lu fields\n", SIZE_MAX);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < args.info.size; i++){
        args.specials[i] = 0;
    }

    for (size_t i = 0; i < args.num_specials; i++){
        args.specials[temp_special_array[i].start-1] = temp_special_array[i].end-1;
        if (args.specials[temp_special_array[i].start-1] == args.info.size-1){
            free(temp_special_array);
            free(args.specials);
            fprintf(stderr, "The final field in the board cannot be a special end point!\n");
            exit(EXIT_FAILURE);
        }
    }

    free(temp_special_array);

    if (args.specials[args.info.size-1]){
        free(args.specials);
        fprintf(stderr, "The final field in the board cannot be a special starting point!\n");
        exit(EXIT_FAILURE);
    }

    //printf("idx of last node: %lu | snake value: %lu\n", args.info.size-1, args.specials[args.info.size-1]);

    return args;
}
