%option case-insensitive
%option noyywrap
%{
#include "parser.tab.h" /* token definitions from the parser */
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
%}

CHAR [A-Za-z1-9-]

%%
[ \r\t\n]* ;

"." return(FULLSTOP);
";" return(SEP);

"BEGINING" return(BEGINING);
"BODY" return(BODY);
"END" return(END);


^X+ {
    yylval.size = strlen(yytext);
//   printf("Read token X: %s\n", yytext); // Add this line for debug
    return(CAPACITY);
}
"TO" return(TO);
"MOVE" return(MOVE);
"ADD" return(ADD);
"PRINT" return(PRINT);
"INPUT" return(INPUT);

[A-Za-z][A-Za-z1-9-]* {
    yylval.str = strdup(yytext);
//    printf("Read token ID: %s\n", yytext);
    return(ID);
}



[Xx]{CHAR}*[^Xx .";]{CHAR}* { 
    // Check if the token is purely numeric
    bool isNumeric = true;
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (!isdigit(yytext[i])) {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        yylval.str = strdup(yytext);
//        printf("Read token INTLITERAL: %s\n", yytext);
        return(INTLITERAL);
    } else {
        // Handle the case where the token is not purely numeric
//        printf("Syntax error: Invalid token: %s\n", yytext);
        // You can add additional error handling or return a different token here if needed
        return(0); // Returning 0 to indicate an error
    }
}

[0-9]+ { 
    yylval.str = strdup(yytext);
//   printf("Read token INTLITERAL: %s\n", yytext); // Debug print for INTLITERAL token
    return(INTLITERAL);
}



\"[^";.]*\" { 
    yylval.str = strdup(yytext);
//    printf("Read token STRINGLITERAL: %s\n", yytext); // Debug print for STRINGLITERAL token
    return(STRINGLITERAL);
}

. return(0);
%%