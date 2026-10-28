
%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token FOR TYPE ID NUM RELOP INC_DEC ASSIGN_OP

%left '+' '-'
%left '*' '/'


%%
start:
    for_loop {
        printf("Valid for loop syntax\n");
    }
    ;

for_loop:
    FOR '(' TYPE ID '=' expr ';' expr RELOP expr ';' ID INC_DEC ')' body
    ;

body:
    '{' statements '}'
    | statement
    ;

statements:
    statements statement
    | /* empty */
    ;

statement:
    ID '=' expr ';'
    | ID INC_DEC ';'
    | INC_DEC ID ';'
    | ';'
    ;

expr:
    expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | ID
    | NUM
    ;

%%


void yyerror(const char *s)
{
    printf("Invalid for loop syntax\n");
}

int main(void)
{
    printf("Enter a C for loop:\n");
    yyparse();
    return 0;
}
