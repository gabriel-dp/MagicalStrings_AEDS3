#include <stdio.h>
#include <stdlib.h>

#include "../include/args.h"
#include "../include/files.h"
#include "../include/stone.h"
#include "../include/strategy.h"
#include "../include/thread.h"
#include "../include/time.h"

int main(int argc, char* argv[]) {
    // Receives inputPath and strategy from user command line
    char* inputPath;
    int strategy;
    getArgs(argc, argv, &inputPath, &strategy);

    // Selects strategy function
    int (*pfunction)(char*, char*, int);
    switch (strategy) {
        case KMP_STRATEGY:
            pfunction = KMP;
            break;
        case BMH_STRATEGY:
            pfunction = BMH;
            break;
        case SHIFTAND_STRATEGY:
            pfunction = shiftAND;
            break;
        default:
            strategy = BRUTEFORCE_STRATEGY;
            pfunction = bruteforce;
            break;
    }
    printf("\nStrategy %d\n\n", strategy);

    // Receives inputStones and creates results array
    StoneArray inputStones = getStonesFromFile(inputPath);
    int* results = (int*)malloc(sizeof(int) * inputStones.length);
    solveStoneArray(&inputStones, results, pfunction);

    // Saves results on output
    char* outputPath = generateOutputPath(inputPath);
    saveStonesFile(outputPath, results, inputStones.length);

    // Deallocates all data
    freeStoneArray(&inputStones);
    free(results);
    free(outputPath);

    return 0;
}
