#include "include/utils.h"

long test_long_conversion(const char* optarg){
    
    char* end_ptr; 
    errno = 0;
    
    long test = strtol(optarg, &end_ptr, 10);
    
    while(*end_ptr == ' ' || *end_ptr == '\t' || *end_ptr == '\n'){
        end_ptr++;
    }

    if (*end_ptr != '\0' || optarg[0] == '-'){
        fprintf(stderr, "Parameter invalid!\n");
        exit(EXIT_FAILURE);
    }

    if ((test == LONG_MAX || test ==  LONG_MIN) && errno == ERANGE){
        fprintf(stderr, "Parameter caused over- or underflow!\n");
        exit(EXIT_FAILURE);
    }

    return test;
}

cli_args parse_args(int argc, char** argv){
    cli_args args = {
        .info.width = DEFAULT_WIDTH,
        .info.height = DEFAULT_HEIGHT,
        .info.size = DEFAULT_WIDTH * DEFAULT_HEIGHT,
        .info.dice = 6,
        .specials = NULL,
        .num_specials = 0,
    };
    
    int opt;
    
    while((opt = getopt(argc, argv, "w:h:d:s:")) != -1){
        
        switch (opt) {
            case -1:
                //printf("Arg reading done.\n");
                break;

            case 'w':
                args.info.width = test_long_conversion(optarg);
                if (args.info.width < 1){
                    fprintf(stderr, "Width parameter invalid! Width must be at least 1.\n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'h':
                args.info.height = test_long_conversion(optarg);
                if (args.info.height < 1){
                    fprintf(stderr, "Width parameter invalid! Width must be at least 1.\n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'd':
                args.info.dice = test_long_conversion(optarg);
                if (args.info.dice < 1){
                    fprintf(stderr, "Width parameter invalid! Width must be at least 1.\n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 's':
                if (optind >= argc-1 || optopt == 's'){
                    fprintf(stderr, "-s requires two arguments!\n");
                    exit(EXIT_FAILURE);
                }

                //long from = test_long_conversion(optarg);
                //long to = test_long_conversion(argv[++optind]); // be careful: check bounds!
                //add_ladder(from, to);
                break;

            case '?':
                fprintf(stderr, "Usage: %s [-w <width>] [-h <height>] [-d <die faces>] [-s <special end 1> <special end 2>]\n", argv[0]);
                exit(EXIT_FAILURE);
            
            case ':':
                fprintf(stderr, "Missing argument for option -%c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }
    
    args.info.size = args.info.width * args.info.height;
    /*
    if (args.input_path == NULL || args.output_path == NULL){
        fprintf(stderr, "Usage: %s -i <input> -o <output> [-s <buffer_size>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (strcmp(args.input_path, args.output_path) == 0){
        fprintf(stderr, "Cannot copy file into itself!\n");
        exit(EXIT_FAILURE);
    }
    */
    return args;
}