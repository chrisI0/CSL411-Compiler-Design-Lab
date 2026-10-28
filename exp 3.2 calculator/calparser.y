%{
#include <stdio.h>
#include <stdlib.h>

/* Declaration of lexer functions */
int yylex(void);
void yyerror(const char *s);
%}

/* Define the semantic data type for tokens and rules */
%union {
    double num;
}

/* Associate NUMBER and expr with the double type */
%token <num> NUMBER
%type <num> expr

/* Operator precedence and associativity */
%left '+' '-'
%left '*' '/'
%right UMINUS  /* For handling negative numbers like -5 */

%%

calc:
    expr '\n'       { printf("Result: %g\n", $1); exit(0); }
    ;

expr:
    expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { 
                        if ($3 == 0) {
                            yyerror("Division by zero!");
                        }
                        $$ = $1 / $3; 
                    }
    | '-' expr %prec UMINUS { $$ = -$2; } /* Unary minus */
    | '(' expr ')'   { $$ = $2; }
    | NUMBER        { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

int main(void) {
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
