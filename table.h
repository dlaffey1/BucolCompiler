#ifndef TABLE_H
#define TABLE_H

#define HASH_SIZE 1024 // Size of the hash table

typedef struct {
    char *identifier;
    int size;
    int value;
} Variable;

void initializeTable();
Variable *lookup(char *identifier);
Variable *insert(char *identifier, int size);
void printTable();

#endif /* TABLE_H */
