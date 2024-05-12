#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Variable variableTable[HASH_SIZE]; // Use a simple array instead of linked list

// Function to initialize the table
void initializeTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        variableTable[i].identifier = NULL;
    }
}

// Hash function: form hash value for string s
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASH_SIZE;
}

Variable *lookup(char *identifier) {
    unsigned index = hash(identifier);
    unsigned i = index;

    int count = 0;
    do {
        if (variableTable[i].identifier != NULL && strcmp(identifier, variableTable[i].identifier) == 0) {
            return &variableTable[i]; // Found
        }
        i = (i + count * count) % HASH_SIZE; // Quadratic probing
        count++;
    } while (variableTable[i].identifier != NULL && i != index);

    return NULL; // Not found
}

Variable *insert(char *identifier, int size) {
    unsigned index = hash(identifier);
    unsigned i = index;

    int count = 0;
    do {
        if (variableTable[i].identifier == NULL || strcmp(identifier, variableTable[i].identifier) == 0) {
            variableTable[i].identifier = strdup(identifier);
            variableTable[i].size = size;
            variableTable[i].value = 0; // Initialize value to 0
            return &variableTable[i];
        }
        i = (i + count * count) % HASH_SIZE; // Quadratic probing
        count++;
    } while (variableTable[i].identifier != NULL && i != index);

    return NULL; // Hash table is full
}

void printTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (variableTable[i].identifier != NULL) {
            printf("Variable: hash: %d, identifier: %s, size: %d, value: %d\n",
                   i, variableTable[i].identifier, variableTable[i].size, variableTable[i].value);
        }
    }
}
