%{
#include <stdio.h>
#include <stdlib.h>

/* Declaration of lexer functions required by YACC */
int yylex(void);
void yyerror(const char *s);
%}

/* Define the tokens that will be received from the lexer */
%token NUMBER

/* Define operator precedence and associativity */
/* Lowest precedence at the top, highest at the bottom */
%left '+' '-'
%left '*' '/'

%%

/* Grammar Rules */

calc:
    expr '\n'       { printf("Valid arithmetic expression!\n"); exit(0); }
    ;

expr:
    expr '+' expr   { }
    | expr '-' expr { }
    | expr '*' expr { }
    | expr '/' expr { }
    | '(' expr ')'   { }
    | NUMBER        { }
    ;

%%

/* C Code Section */

void yyerror(const char *s) {
    fprintf(stderr, "Invalid arithmetic expression!\n");
    exit(1);
}

int main(void) {
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
