#include "../include/strategy.h"

#include <stdlib.h>
#include <string.h>

#include "../include/stone.h"

// Try to find the solution with the given strategy
int solveStone(Stone stone, int pfunction(char* substring, char* string)) {
    // Solve with the normal string
    int result = pfunction(stone.hability, stone.description);

    // Solve with the reverse string if did not find the result
    if (result == -1) {
        revertString(stone.hability);
        result = pfunction(stone.hability, stone.description);
        if (result != -1) result = abs(result + 1 - (int)strlen(stone.description));
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
    int m = strlen(substring);
    int n = strlen(string);

    for (int i = 0; i < n; i++) {
        int match = 1;
        for (int j = 0; j < m; j++) {
            if (substring[j] != string[(j + i) % n]) {
                match = 0;
                break;
            }
        }
        if (match) return i;
    }

    return -1;
}
