#include "../include/strategy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stone.h"

// Try to find the solution with the given strategy
int solveStone(Stone stone, int pfunction(char* substring, char* string, int reverse)) {
    // Solve with the normal strings
    int result = pfunction(stone.hability, stone.description, 0);

    // Solve with the reverse substring if did not found the result
    if (result == -1) {
        char* reverseHability = reverseString(stone.hability);
        result = pfunction(reverseHability, stone.description, 1);
        free(reverseHability);
    }

    return result;
}

// Reverts all chars from a string
char* reverseString(char* string) {
    int length = strlen(string);

    char* reverse = malloc(length + 1);
    strcpy(reverse, string);

    for (int i = 0; i < length / 2; i++) {
        char aux = reverse[i];
        reverse[i] = reverse[length - i - 1];
        reverse[length - i - 1] = aux;
    }

    return reverse;
}

/*--------------------------------------------------
    Brute Force
--------------------------------------------------*/

// Finds a substring in a string using brute force
int bruteforce(char* substring, char* string, int reverse) {
    int m = strlen(substring);
    int n = strlen(string);

    int i, j;
    for (i = 0; i < n; i++) {
        int match = 1;
        for (j = 0; j < m; j++) {
            if (substring[j] != string[(j + i) % n]) {
                match = 0;
                break;
            }
        }
        if (match) {
            if (reverse)
                return (i + j - 1) % n;
            return i;
        }
    }

    return -1;
}

/*--------------------------------------------------
    KMP (Knuth-Morris-Pratt)
--------------------------------------------------*/

// Computes the prefix array for the given substring.
int* preprocessKMP(char* substring) {
    int length = strlen(substring);
    int* prefix = (int*)malloc(sizeof(int) * length);

    int j = -1;
    prefix[0] = j;

    for (int i = 1; i < length; i++) {
        while (j > -1 && substring[j + 1] != substring[i]) {
            j = prefix[j];
        }
        if (substring[i] == substring[j + 1]) {
            j++;
        }
        prefix[i] = j;
    }

    return prefix;
}

// Finds a substring in a string using KMP search
int KMP(char* substring, char* string, int reverse) {
    int* prefix = preprocessKMP(substring);
    int m = strlen(substring);
    int n = strlen(string);

    int k = -1;
    for (int i = 0; i < n; i++) {
        while (k > -1 && substring[k + 1] != string[i]) {
            k = prefix[k];
        }
        if (substring[k + 1] == string[i]) {
            k++;
            while (i >= n - 1 && substring[k + 1] == string[(i + 1) % n]) {
                i++;
                k++;
            }
        }
        if (k == m - 1) {
            free(prefix);
            if (reverse) return i % n;
            return (i - k) % n;
        }
    }

    free(prefix);
    return -1;
}

/*--------------------------------------------------
    BMH (Boyer-Moore-Horspool)
--------------------------------------------------*/

// Preprocess shift of each char in the alphabet for BMH search
int* preprocessBMH(char* substring) {
    const int ALPHABET_CHARS = 256;
    int* shift = (int*)malloc(sizeof(int) * ALPHABET_CHARS);

    int length = strlen(substring);

    for (int i = 0; i < ALPHABET_CHARS; i++) {
        shift[i] = length;
    }

    for (int i = 1; i < length; i++) {
        shift[(int)substring[i - 1]] = length - i;
    }

    return shift;
}

// Finds a substring in a string using BMH search
int BMH(char* substring, char* string, int reverse) {
    int* shift = preprocessBMH(substring);
    int m = strlen(substring);
    int n = strlen(string);

    int i = m;
    int k, j;
    while (i <= n) {
        k = i;
        j = m;
        while (string[k - 1] == substring[j - 1] && j > 0) {
            k--;
            j--;
        }
        if (j == 0) {
            free(shift);
            if (reverse) return k - 1 + m;
            return k;
        }
        i += shift[(int)string[i - 1]];
    }

    free(shift);
    return -1;
}