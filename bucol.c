#include "bucol.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool declareVariable(char *varName, int size) {
    if (lookup(varName) != NULL) {
        printf("Error: variable %s already declared\n", varName);
        return false;
    }

    if (insert(varName, size) == NULL) {
        printf("Error: unable to insert variable %s\n", varName);
        return false;
    }

    return true;
}

bool moveIDtoID(char *sourceID, char *destID) {
    Variable *src = lookup(sourceID);
    Variable *dest = lookup(destID);

    if (src == NULL) {
        printf("Error: variable %s not declared\n", sourceID);
        return false;
    }
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", destID);
        return false;
    }

    dest->value = src->value;
    return true;
}

bool moveINTtoID(char *intLiteral, char *destID) {
    Variable *dest = lookup(destID);

    if (dest == NULL) {
        printf("Error: variable %s not declared\n", destID);
        return false;
    }

    dest->value = atoi(intLiteral);
    return true;
}

bool addIDtoID(char *sourceID, char *destID) {
    Variable *src = lookup(sourceID);
    Variable *dest = lookup(destID);

    if (src == NULL) {
        printf("Error: variable %s not declared\n", sourceID);
        return false;
    }
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", destID);
        return false;
    }

    dest->value += src->value;
    return true;
}

bool addINTtoID(char *intLiteral, char *destID) {
    Variable *dest = lookup(destID);

    if (dest == NULL) {
        printf("Error: variable %s not declared\n", destID);
        return false;
    }

    dest->value += atoi(intLiteral);
    return true;
}

bool checkIsDeclared(char *varName) {
    if (lookup(varName) == NULL) {
        printf("Error: variable %s not declared\n", varName);
        return false;
    }
    return true;
}

bool isIntLiteral(char *token) {
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}
