#include <stdio.h>
#include <stdlib.h>

#include "../include/args.h"
#include "../include/files.h"
#include "../include/stone.h"
#include "../include/strategy.h"
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

    // Solves each stone
    for (int i = 0; i < inputStones.length; i++) {
        // Finds result monitoring the elapsed time
        Time startTime = getRealTime();
        results[i] = solveStone(inputStones.data[i], pfunction);
        Time endTime = getRealTime();

        // Prints result data
        printf("Stone %d = (%d)\n", i + 1, results[i] + 1);
        printf("Elapsed time = %Lf\n\n", endTime - startTime);
    }

    // Saves results on output and deallocates all data
    char* outputPath = generateOutputPath(inputPath);
    saveStonesFile(outputPath, results, inputStones.length);
    freeStoneArray(&inputStones);
    free(results);
    free(outputPath);

    return 0;
}