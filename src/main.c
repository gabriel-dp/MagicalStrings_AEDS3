#include <stdio.h>
#include <stdlib.h>

#include "../include/args.h"
#include "../include/files.h"
#include "../include/stone.h"
#include "../include/time.h"

int main(int argc, char* argv[]) {
    // Receives inputPath and strategy from user command line
    char* inputPath;
    int strategy;
    getArgs(argc, argv, &inputPath, &strategy);

    // Generates outputPath from inputPath
    char* outputPath = generateOutputPath(inputPath);

    // Receives inputStones and creates results array
    StoneArray inputStones = getStonesFromFile(inputPath);
    int* results = (int*)malloc(sizeof(int) * inputStones.length);

    // Solves each stone
    printf("\nStrategy %d\n\n", strategy);
    for (int i = 0; i < inputStones.length; i++) {
        // Initializes timer
        Time startTime = getRealTime();

        // Finds result based on given strategy number
        int result;
        switch (strategy) {
            case 1:
                result = 1;
                break;
            case 2:
                result = 2;
                break;
            case 3:
                result = 3;
                break;
            default:
                result = 0;
                break;
        }
        results[i] = result;

        // Finish timer
        Time endTime = getRealTime();

        // Prints data
        printf("Stone %d = (%d)\n", i + 1, result);
        // printf("%s|%s\n", inputStones.data[i].hability, inputStones.data[i].description);
        printf("Elapsed time = %Lf\n\n", endTime - startTime);
    }

    // Saves results on output and deallocates results
    saveStonesFile(outputPath, results, inputStones.length);
    freeStoneArray(&inputStones);
    free(results);
    free(outputPath);

    return 0;
}