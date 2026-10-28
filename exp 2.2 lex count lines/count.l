%{
int lines = 0;
int words = 0;
int chars = 0;
%}

%%
\n      { lines++; chars++; }
[^\t\n ]+ { words++; chars += yyleng; }
.       { chars++; }
%%

int main()
{
    printf("Enter your text (Press Ctrl+D or type 'q' on a new line to finish):\n");
    yylex();
    printf("\n--- Results ---\n");
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);
    return 0;
}

int yywrap()
{
    return 1;
}
