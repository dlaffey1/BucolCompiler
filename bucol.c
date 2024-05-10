#include "bucol.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INT_SIZE 12

bool declareVariable(char *identifier, int size) {
    // Previous declaration check
    if (lookup(identifier) != NULL) {
        printf("Error: variable %s already declared\n", identifier);
        return false;
    }
    // Size check
    if (size > MAX_INT_SIZE) {
        printf("Error: variable %s size %d exceeds maximum size %d\n", identifier,
               size, MAX_INT_SIZE);
        return false;
    }
    // Insert
    Variable *newVar = insert(identifier, size);
    if (newVar == NULL) {
        printf("Error: cannot insert variable %s\n", identifier);
        return false;
    }
    return true;
}

bool moveIDtoID(char *source_id, char *dest_id) {
    Variable *source = lookup(source_id);
    Variable *dest = lookup(dest_id);

    // Declaration guards
    if (source == NULL) {
        printf("Error: variable %s not declared\n", source_id);
        return false;
    }
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

    // Move
    dest->value = source->value;
    return true;
}

bool moveINTtoID(char *int_literal, char *dest_id) {
    Variable *dest = lookup(dest_id);

    // Declaration guard
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

    // Assign
    dest->value = atoi(int_literal);
    return true;
}

bool addIDtoID(char *source_id, char *dest_id) {
    Variable *source = lookup(source_id);
    Variable *dest = lookup(dest_id);

    // Declaration guards
    if (source == NULL) {
        printf("Error: variable %s not declared\n", source_id);
        return false;
    }
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

    // Add
    dest->value += source->value;
    return true;
}

bool addINTtoID(char *int_literal, char *dest_id) {
    Variable *dest = lookup(dest_id);

    // Declaration guard
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

    // Add
    dest->value += atoi(int_literal);
    return true;
}

bool checkIsDeclared(char *id) {
    if (lookup(id) == NULL) {
        printf("Error: variable %s not declared\n", id);
        return false;
    }
    return true;
}

bool isIntLiteral(char *token) {
    // Implementation logic to check if token is an integer literal
    // For example:
    // Check if the string consists of digits only
    // You can use strtol or sscanf for more robust checking
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}