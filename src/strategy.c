#include "../include/strategy.h"

#include <stdlib.h>
#include <string.h>

#include "../include/stone.h"

// Try to find the solution with the given strategy
int solveStone(Stone stone, int pfunction(char* substring, char* string)) {
    // Solve with the normal string
    int result = (int)pfunction(stone.hability, stone.description);

    // Solve with the reverse string if did not find the result
    if (!result) {
        revertString(stone.description);
        result = (int)pfunction(stone.hability, stone.description);
        if (result) result = abs(result - 1 - (int)strlen(stone.description));
    }

    return result;
}

// Reverts all chars from a string
void revertString(char* string) {
    for (int i = 0; i < strlen(string) / 2; i++) {
        char aux = string[i];
        string[i] = string[strlen(string) - i - 1];
        string[strlen(string) - i - 1] = aux;
    }
}

// Finds a substring in a string using brute force
int bruteforce(char* substring, char* string) {
    for (int i = 0; i < strlen(string); i++) {
        if (substring[0] == string[i]) {
            int match = 1;
            for (int j = 1; j < strlen(substring); j++) {
                if (substring[j] == string[(j + i) % strlen(string)]) {
                    match = 1;
                } else {
                    match = 0;
                    break;
                }
            }
            if (match) return i + 1;
        }
    }
    return 0;
}
