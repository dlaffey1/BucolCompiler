%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "src/bucol.h"

extern int yylex();
extern int yyparse();
extern void yyerror(char *s);

bool valid = true;
%}

%union {
    int size;
    char *str; // For ID
}

%token <str> ID INTLITERAL STRINGLITERAL
%token <size> CAPACITY

%token ENDSTMT BEGINING BODY END TO MOVE ADD INPUT PRINT SEP
%%

program: begining declarations body statements end {
    if (valid) {
        printf("Program is well-formed!\n");
    } else {
        printf("Program is not well-formed!\n");
    }
} 

declarations: declaration | declarations declaration {
    // This means there has to be at least one declaration
}

begining: BEGINING ENDSTMT

body: BODY ENDSTMT

end: END ENDSTMT

statements: statement | statements statement {
    // This means there has to be at least one statement
}

statement: assignment | addition | declaration | input | print 

declaration: CAPACITY ID ENDSTMT
{
} 

assignment: MOVE ID TO ID ENDSTMT
{
}


addition: ADD INTLITERAL TO ID ENDSTMT
{
}


input: INPUT inputlist ENDSTMT

inputlist: var SEP inputlist | var 

print: PRINT printlist ENDSTMT

printlist: var | STRINGLITERAL | var SEP printlist | STRINGLITERAL SEP printlist

var: ID {
   }
%%

extern FILE *yyin;

int main() {
    yyparse();
    return 0;
}

// Syntax error handler
void yyerror(char *s) {
    valid = false;
    fprintf(stderr, "Syntax error: %s at line %d, column %d\n", s, yylineno, yyleng);
}

