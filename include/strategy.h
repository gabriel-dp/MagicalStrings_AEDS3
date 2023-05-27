#ifndef STRATEGY_H
#define STRATEGY_H

#include "stone.h"

int solveStone(Stone stone, int pfunction(char* substring, char* string, int reverse));
char* reverseString(char* string);

int bruteforce(char* substring, char* string, int reverse);

int* preprocessKMP(char* substring);
int KMP(char* substring, char* string, int reverse);

#endif
