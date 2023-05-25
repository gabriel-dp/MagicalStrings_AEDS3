#include "../include/files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stone.h"

// Returns the outputPath based on inputPath
char* generateOutputPath(char* inputPath) {
    // Defines default extension to be in the end
    const char* extension = ".out";

    // Creates outputPath adding the extension in the end of the inputPath
    char* newFullPath = malloc(strlen(inputPath) + strlen(extension) + 1);
    strcpy(newFullPath, inputPath);
    strcat(newFullPath, extension);

    // Removes possible dirs in path
    char* outputPath = malloc(strlen(newFullPath) + 1);
    char* token = strtok(newFullPath, "/");
    while (token != NULL) {
        strcpy(outputPath, token);
        token = strtok(NULL, "/");
    }

    // Manages leak memory due dyncamic path strings
    outputPath = realloc(outputPath, strlen(outputPath) + 1);
    free(newFullPath);

    return outputPath;
}

// Interrupts program execution if there is an error at files
void errorAtFiles(char* message) {
    printf("FILE ERROR - %s\n", message);
    exit(EXIT_FAILURE);
}

// Returns the StoneArray of all Stones in input file
StoneArray getStonesFromFile(char* inputPath) {
    // Try to open the input file
    FILE* inputFile = fopen(inputPath, "r");
    if (inputFile == NULL) {
        errorAtFiles("Cannot open input file");
    }

    // Creates StoneArray based on stone amount
    int amount;
    fscanf(inputFile, "%d", &amount);
    StoneArray inputStones = createStoneArray(amount);

    // Fills all Stones data
    for (int i = 0; i < inputStones.length; i++) {
        fscanf(inputFile, "%s %s", inputStones.data[i].hability, inputStones.data[i].description);
    }

    // Closes inputFile
    fclose(inputFile);

    return inputStones;
}

// Saves all results in output file
void saveStonesFile(char* outputPath, int* results, int length) {
    // Try to open the output file
    FILE* outputFile = fopen(outputPath, "w");
    if (outputFile == NULL) {
        errorAtFiles("Cannot open output file");
    }

    // Adds each result in the file
    for (int i = 0; i < length; i++) {
        if (results[i] > 0) {
            fprintf(outputFile, "S %d\n", results[i]);
        } else {
            fprintf(outputFile, "N\n");
        }
    }

    // Closes outputFile
    fclose(outputFile);
}