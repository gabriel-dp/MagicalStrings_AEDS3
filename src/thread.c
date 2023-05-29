#include "../include/thread.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/stone.h"
#include "../include/strategy.h"
#include "../include/time.h"

// Solves a stone array using threads
void solveStoneArray(StoneArray* array, int* results, int pfunction(char* substring, char* string, int reverse)) {
    // Creates threads array
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * array->length);
    ThreadArgs* threadsArgs = (ThreadArgs*)malloc(sizeof(ThreadArgs) * array->length);

    // Initializes pthreads
    for (int i = 0; i < array->length; i++) {
        // Defines all args for the thread
        threadsArgs[i].id = i;
        threadsArgs[i].stone = &(array->data[i]);
        threadsArgs[i].pfunction = pfunction;
        threadsArgs[i].result = &(results[i]);

        // Creates thread process
        pthread_create(&threads[i], NULL, stoneThread, (void*)&threadsArgs[i]);
    }

    // Terminates pthreads
    for (int i = 0; i < array->length; i++) {
        pthread_join(threads[i], NULL);

        // Prints result data
        printf("Stone %d = (%d)\nElapsed time = %Lf\n\n", i + 1, results[i] + 1, threadsArgs[i].elapsedTime);
    }

    // Deallocates threads and threadsArgs
    free(threads);
    free(threadsArgs);
}

// Function to solve the stone inside a thread
void* stoneThread(void* threadArgs) {
    // Converts args to ThreadArgs type
    ThreadArgs* args = (ThreadArgs*)threadArgs;

    // Finds result monitoring the elapsed time
    Time startTime = getRealTime();
    *(args->result) = solveStone(*(args->stone), args->pfunction);
    Time endTime = getRealTime();

    // Returns elapsed time
    args->elapsedTime = endTime - startTime;

    return NULL;
}