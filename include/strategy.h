#ifndef STRATEGY_H
#define STRATEGY_H

#include "stone.h"

enum strategy {
    KMP_STRATEGY = 1,
    BMH_STRATEGY,
    SHIFTAND_STRATEGY,
    BRUTEFORCE_STRATEGY
};

int solveStone(Stone stone, int pfunction(char* substring, char* string, int reverse));
char* reverseString(char* string);

int bruteforce(char* substring, char* string, int reverse);

int* preprocessKMP(char* substring, int length);
int KMP(char* substring, char* string, int reverse);

int* preprocessBMH(char* substring, int length);
int BMH(char* substring, char* string, int reverse);

unsigned int* preprocessShiftAND(char* substring, int length);
int shiftAND(char* substring, char* string, int reverse);

#endif
