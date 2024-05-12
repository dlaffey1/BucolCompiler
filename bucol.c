#include "bucol.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool declareVariable(char *identifier, int size) {
    if (lookup(identifier) != NULL) {
        printf("Error: variable %s already declared\n", identifier);
        return false;
    }

    if (insert(identifier, size) == NULL) {
        printf("Error: cannot insert variable %s\n", identifier);
        return false;
    }

    return true;
}

bool moveIDtoID(char *source_id, char *dest_id) {
    Variable *source = lookup(source_id);
    Variable *dest = lookup(dest_id);

    if (source == NULL) {
        printf("Error: variable %s not declared\n", source_id);
        return false;
    }
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

    dest->value = source->value;
    return true;
}

bool moveINTtoID(char *int_literal, char *dest_id) {
    Variable *dest = lookup(dest_id);

    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

    dest->value = atoi(int_literal);
    return true;
}

bool addIDtoID(char *source_id, char *dest_id) {
    Variable *source = lookup(source_id);
    Variable *dest = lookup(dest_id);

    if (source == NULL) {
        printf("Error: variable %s not declared\n", source_id);
        return false;
    }
    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

    dest->value += source->value;
    return true;
}

bool addINTtoID(char *int_literal, char *dest_id) {
    Variable *dest = lookup(dest_id);

    if (dest == NULL) {
        printf("Error: variable %s not declared\n", dest_id);
        return false;
    }

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
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}
