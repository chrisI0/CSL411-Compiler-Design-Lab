#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    for (int i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

void flushBuffer(char buffer[], int *j) {
    if (*j > 0) {
        buffer[*j] = '\0';
        *j = 0;
        if (isKeyword(buffer)) {
            printf("Keyword:    %s\n", buffer);
        } else if (isdigit(buffer[0])) {
            printf("Constant:   %s\n", buffer);
        } else {
            printf("Identifier: %s\n", buffer);
        }
    }
}

int main() {
    char ch;
    char buffer[100];
    char operators[] = "+-*/=<>";
    int j = 0;

    printf("===Lexical Analyzer ===\n\n");

    while ((ch = getchar()) != EOF) {
        // Handle Preprocessor Includes (e.g., #include <stdio.h>)
if (ch == '#') {
    flushBuffer(buffer, &j); // Clear any pending tokens
    
    int k = 0;
    buffer[k++] = ch; // Store '#'
    
    // Read until the end of the line (capturing "include <stdio.h>")
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (k < 99) { // Avoid buffer overflow
            buffer[k++] = ch;
        }
    }
    buffer[k] = '\0';
    printf("Preprocessor: %s\n", buffer);
    continue;
}
        // Handle String Literals (Everything inside " ")
        if (ch == '"') {
            flushBuffer(buffer, &j); // Flush anything before the string
            int k = 0;
            buffer[k++] = ch;
            while ((ch = getchar()) != EOF && ch != '"') {
                buffer[k++] = ch;
            }
            buffer[k++] = '"';
            buffer[k] = '\0';
            printf("String:     %s\n", buffer);
            continue;
        }

        // Check for Operators (Added < and >)
        int isOperator = 0;
        for (int i = 0; i < 7; ++i) {
            if (ch == operators[i]) {
                flushBuffer(buffer, &j);
                printf("Operator:   %c\n", ch);
                isOperator = 1;
                break;
            }
        }
        if (isOperator) continue;

        // Check for Special Characters (Added #)
        if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '#' || ch == ',' || ch == '.') {
            flushBuffer(buffer, &j);
            printf("Special Ch: %c\n", ch);
            continue;
        }

        // Build Alphanumeric Buffers
        if (isalnum(ch) || ch == '_') {
            buffer[j++] = ch;
        } 
        else if (isspace(ch)) {
            flushBuffer(buffer, &j);
        }
    }

    flushBuffer(buffer, &j);
    return 0;
}