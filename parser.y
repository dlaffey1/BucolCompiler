%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "bucol.h"
#include "table.h"
extern int yylex();
extern int yyparse();
extern void yyerror(char *s);
extern char *yytext;

bool valid = true;
%}


%union {
    int size;
    char *str; // For ID and STRINGLITERAL
}

%token <str> ID INTLITERAL STRINGLITERAL
%token <size> CAPACITY

%token FULLSTOP BEGINING BODY END TO MOVE ADD INPUT PRINT SEP
%type <str> var operand
%%

program: begining declarations body statements end {
    if (valid) {
        printf("Program is well-formed!\n");
    } else {
        printf("Program is not well-formed!\n");
    }
} 

declarations: declaration | declarations declaration {

}

begining: BEGINING FULLSTOP {
//    printf("BEGINING rule matched\n");
}

body: BODY FULLSTOP {
//   printf("BODY rule matched\n");
}

end: END FULLSTOP {
//    printf("END rule matched\n");
}

statements: statement | statements statement {
    // This means there has to be at least one statement
}
statement: assignment | addition | declaration | input | print | unrecognized_statement

unrecognized_statement: { printf("Unrecognized statement: %s\n", yytext); }

declaration: CAPACITY ID FULLSTOP
{
    valid = valid && declareVariable($2, $1);
    if (!valid) {
//        printf("Declaration rule failed: CAPACITY %s\n", $2);
    } else {
//        printf("Declaration rule succeeded: CAPACITY %s\n", $2);
    }
}

assignment: MOVE INTLITERAL TO ID FULLSTOP
{
    valid = valid && moveINTtoID($2, $4);
//    printf("Assignment: MOVE INTLITERAL %s TO ID %s\n", $2, $4);
}
| MOVE ID TO ID FULLSTOP
{
//    printf("Assignment: MOVE INTLITERAL %s TO ID %s\n", $2, $4);
    valid = valid && moveIDtoID($2, $4);
}



addition: ADD operand TO ID FULLSTOP
{
 //   printf("Addition: ADD operand %s TO ID %s\n", $2, $4);
    valid = valid && addINTtoID($2, $4);
    
}
| ADD ID TO ID FULLSTOP
{
 //   printf("Addition: ADD ID %s TO ID %s\n", $2, $4);
    valid = valid && addIDtoID($2, $4);
    
}
operand: INTLITERAL { $$ = $1; 
//printf("Operand: INTLITERAL %s\n", $1); 
}


input: INPUT input_list FULLSTOP {
//    printf("Input statement: succeeded\n");
}



input_list : var SEP input_list 
		   | var

print: PRINT printlist FULLSTOP {
//    printf("PRINT rule succeeded\n");
}

printlist: {
//    printf("Printlist: empty\n");
}
         | STRINGLITERAL {
//             printf("Printlist: STRINGLITERAL %s\n", $1);
         }
         | var {
//             printf("Printlist: var %s\n", $1);
         }
         | STRINGLITERAL SEP printlist {
//             printf("Printlist: STRINGLITERAL %s SEP\n", $1);
         }
         | var SEP printlist {
//            printf("Printlist: var %s SEP\n", $1);
         }
         ;


var: ID {
   valid = valid && checkIsDeclared($1);
//   printf("Variable: %s\n", $1);
   $$ = $1;
}
%%

extern FILE *yyin;

int main() {
    do {
        yyparse();
    } while (!feof(yyin));
    return 0;
}

// Syntax error handler
void yyerror(char *s) {
    valid = false;
    fprintf(stderr, "Syntax error: %s\n", s);

    printf("Syntax error occurred. Last token read: %s\n", yytext);
}
