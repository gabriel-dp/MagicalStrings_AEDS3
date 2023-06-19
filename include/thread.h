#ifndef THREAD_H
#define THREAD_H

#include "stone.h"
#include "time.h"

typedef struct {
    Stone* stone;
    int (*pfunction)(char*, char*, int);
    int* result;
    Time startTime, endTime;
} ThreadArgs;

void solveStoneArray(StoneArray* array, int* results, int pfunction(char* substring, char* string, int reverse));
void* stoneThread(void* threadArgs);

#endif