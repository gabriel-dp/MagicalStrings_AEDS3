#ifndef THREAD_H
#define THREAD_H

#include "stone.h"

typedef struct {
    int id;
    int* result;
    int (*pfunction)(char*, char*, int);
    Stone stone;
} ThreadArgs;

void* solveStoneThread(void* threadArgs);

#endif