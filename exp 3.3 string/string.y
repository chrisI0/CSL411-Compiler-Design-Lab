
%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token A B

%%
start:
    S '\n' {
        printf("Valid string (Accepted)\n");
        exit(0);
    }
    ;

S:
    A B B
    | A S
    | B S
    ;
%%

void yyerror(const char *s)
{
    printf("Invalid string (Rejected)\n");
    exit(1);
}

int main(void)
{
    printf("Enter string: ");
    yyparse();
    return 0;
}
