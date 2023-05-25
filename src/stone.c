#include "../include/stone.h"

#include <stdlib.h>

// Creates a new empty Stone array
StoneArray createStoneArray(int length) {
    StoneArray newArray;
    newArray.data = (Stone*)malloc(sizeof(Stone) * length);
    newArray.length = length;

    return newArray;
}

// Deallocates data from a StoneArray
void freeStoneArray(StoneArray* array) {
    free((*array).data);
}