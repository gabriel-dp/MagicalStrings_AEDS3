#ifndef STRATEGY_H
#define STRATEGY_H

#include "stone.h"

int solveStone(Stone stone, int pfunction(char* substring, char* string));
void revertString(char* string);
int bruteforce(char* substring, char* string);

#endif
