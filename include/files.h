#ifndef FILES_H
#define FILES_H

#include "stone.h"

void errorAtFiles(char* message);
StoneArray getStonesFromFile(char* inputPath);
char* generateOutputPath(char* inputPath);
void saveStonesFile(char* outputPath, int* results, int length);

#endif