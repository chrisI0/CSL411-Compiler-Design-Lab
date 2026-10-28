%{
#include <stdio.h>
%}

%%
"abc"   { printf("ABC"); }
.       { printf("%s", yytext); }
\n      { printf("%s", yytext); }
%%

int main()
{
    printf("Enter the input string: \n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
