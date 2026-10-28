%{
#include <stdio.h>
int vowels = 0;
int consonants = 0;
%}

%%
[aeiouAEIOU]      { vowels++; }
[a-zA-Z]          { consonants++; }
.|\n              { /* Ignore all other characters like spaces, punctuation, and newlines */ }
%%

int main()
{
    printf("Enter the input string (Press Ctrl+D to finish):\n");
    yylex();
    
    printf("\n--- Results ---\n");
    printf("Total Vowels: %d\n", vowels);
    printf("Total Consonants: %d\n", consonants);
    return 0;
}

int yywrap()
{
    return 1;
}
