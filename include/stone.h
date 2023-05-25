#ifndef STONE_H
#define STONE_H

#define MAX_CHAR_HABILITY 100
#define MAX_CHAR_DESCRIPTION 10000

typedef struct {
    char hability[MAX_CHAR_HABILITY + 1], description[MAX_CHAR_DESCRIPTION + 1];
} Stone;

typedef struct {
    Stone* data;
    int length;
} StoneArray;

StoneArray createStoneArray(int length);
void freeStoneArray(StoneArray* array);

#endif