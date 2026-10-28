%{
#include <stdio.h>
%}

/* Regular Expressions definitions */
DIGIT       [0-9]
NUMBER      {DIGIT}+
DECIMAL     {DIGIT}+\.{DIGIT}+
LETTER      [a-zA-Z_]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*

%%

"if"|"else"|"while"|"for"|"int"|"float"|"void"|"return" { printf("Keyword: %s\n", yytext); }

{IDENTIFIER}       { printf("Identifier: %s\n", yytext); }
{DECIMAL}|{NUMBER} { printf("Numeral: %s\n", yytext); }

"+"|"-"|"*"|"/"|"="|"=="|"<"|">"|"<="|">=" { printf("Operator: %s\n", yytext); }

"{"|"}"|"("|")"|";"|"," { printf("Punctuation: %s\n", yytext); }

[ \t\n]+           { /* Ignore whitespace */ }

.                  { printf("Unknown Character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
