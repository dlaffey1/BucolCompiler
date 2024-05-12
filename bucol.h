#ifndef BUCOL_H
#define BUCOL_H
#include <stdbool.h>

bool addIDtoID(char* source_id, char* dest_id);
bool addINTtoID(char* int_literal, char* dest_id);
bool checkIsDeclared(char* id);
bool isIntLiteral(char *token);
bool declareVariable(char* identifier, int size);
bool moveIDtoID(char* source_id, char* dest_id);
bool moveINTtoID(char* int_literal, char* dest_id);
#endif // BUCOL_H