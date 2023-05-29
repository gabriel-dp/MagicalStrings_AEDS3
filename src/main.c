#include <pthread.h>
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
        case 1:
            pfunction = KMP;
            break;
        case 2:
            pfunction = BMH;
            break;
        case 3:
            pfunction = shiftAND;
            break;
        default:
            pfunction = bruteforce;
            strategy = 4;
            break;
    }

    // Receives inputStones and creates results array
    StoneArray inputStones = getStonesFromFile(inputPath);
    int* results = (int*)malloc(sizeof(int) * inputStones.length);

    // Creates threads
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * inputStones.length);

    // Solves each stone
    printf("\nStrategy %d\n\n", strategy);
    for (int i = 0; i < inputStones.length; i++) {
        // Defines all args for the thread
        ThreadArgs* threadArgs = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        threadArgs->id = i;
        threadArgs->pfunction = pfunction;
        threadArgs->result = &(results[i]);
        threadArgs->stone = inputStones.data[i];

        // Creates thread process
        pthread_create(&threads[i], NULL, solveStoneThread, (void*)threadArgs);
    }

    // Terminates threads
    for (int i = 0; i < inputStones.length; i++) {
        pthread_join(threads[i], NULL);
    }
    free(threads);

    // Saves results on output and deallocates all data
    char* outputPath = generateOutputPath(inputPath);
    saveStonesFile(outputPath, results, inputStones.length);
    freeStoneArray(&inputStones);
    free(results);
    free(outputPath);

    return 0;
}
