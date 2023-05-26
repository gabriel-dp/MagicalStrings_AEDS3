#include "../include/thread.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/stone.h"
#include "../include/strategy.h"
#include "../include/time.h"

// Function to solve the stone inside a thread
void* solveStoneThread(void* threadArgs) {
    // Converts args to ThreadArgs type
    ThreadArgs* args = (ThreadArgs*)threadArgs;

    // Finds result monitoring the elapsed time
    Time startTime = getRealTime();
    *(args->result) = solveStone(args->stone, args->pfunction);
    Time endTime = getRealTime();

    // Prints result data
    printf("Stone %d = (%d)\nElapsed time = %Lf\n\n", args->id + 1, *(args->result) + 1, endTime - startTime);

    // Deallocates args data
    free(args);

    return NULL;
}