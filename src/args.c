#include "../include/args.h"

#include <stdio.h>
#include <stdlib.h>

// Interrupts program execution if there is an error at args
void errorAtArgs(char* message) {
    printf("ARGS ERROR - %s\n", message);
    exit(EXIT_FAILURE);
}

// Gets inputPath and strategy from user command line
void getArgs(int argc, char* argv[], char** inputPath, int* strategy) {
    // Checks args quantity
    if (argc != 3) {
        errorAtArgs("Correct usage: ./tp3 {inputPath} {strategy}");
    }

    // Updates both values based on given args
    *inputPath = argv[1];
    *strategy = atoi(argv[2]);
}