#include <stdio.h>
#include <stdlib.h>

// Declare Lex functions/variables so the C compiler knows they exist
extern FILE *yyin;
extern int yylex();

int main() {
    char filename[100];
    
    printf("Enter the name of the file to analyze: ");
    scanf("%99s", filename);
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }
    
    // Set Lex to read from our file pointer
    yyin = file;
    
    printf("\n--- Lexical Analysis Results ---\n");
    yylex(); // This invokes the lexical analyzer
    printf("---------------------------------\n");
    
    fclose(file);
    return 0;
}
