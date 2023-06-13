#ifndef STRATEGY_H
#define STRATEGY_H

#include "stone.h"

#define ALPHABET_CHARS 26
#define ALPHABET_START 97

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

unsigned __int128* preprocessShiftAND(char* substring, int length);  // a unsigned __int128 allows create a 128bit number
int shiftAND(char* substring, char* string, int reverse);

#endif
