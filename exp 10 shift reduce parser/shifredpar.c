#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char lhs[100][20], rhs[100][10][20];
int rhs_len[100];

char input[100][20];      // input tokens
int in_cnt = 0;

char stack[100][20];      // parser stack
int top = 0;

// Reads one token from s starting at pos, returns its length
int getToken(char *s, int pos, char *tok)
{
    char *words[] = {"id", "then", "else", "if"};
    for (int k = 0; k < 4; k++)
    {
        int l = strlen(words[k]);
        if (strncmp(&s[pos], words[k], l) == 0)
        {
            strcpy(tok, words[k]);
            return l;
        }
    }
    tok[0] = s[pos];                     // any other symbol is a single character
    tok[1] = '\0';
    if (isupper(s[pos]) && s[pos + 1] == '\'')   // non-terminal like E'
    {
        tok[1] = '\'';
        tok[2] = '\0';
        return 2;
    }
    return 1;
}

// Try to reduce the top of the stack. Returns 1 if a reduction was done.
int tryReduce()
{
    int best = -1;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(rhs[i][0], "#") == 0) continue;   // skip epsilon productions
        if (rhs_len[i] > top) continue;              // stack too small

        int match = 1;
        for (int j = 0; j < rhs_len[i]; j++)
            if (strcmp(stack[top - rhs_len[i] + j], rhs[i][j]) != 0)
            {
                match = 0;
                break;
            }

        // choose the longest matching right side
        if (match && (best == -1 || rhs_len[i] > rhs_len[best]))
            best = i;
    }

    if (best == -1) return 0;

    top -= rhs_len[best];                 // pop the right side
    strcpy(stack[top++], lhs[best]);      // push the left side
    return 1;
}

int main()
{
    printf("Enter number of productions : ");
    scanf("%d", &n);
    printf("Enter productions in the form E -> E+E :\n");

    for (int i = 0; i < n; i++)
    {
        char buf[100];
        scanf("%s -> %s", lhs[i], buf);

        int len = strlen(buf), pos = 0;
        rhs_len[i] = 0;
        while (pos < len)
            pos += getToken(buf, pos, rhs[i][rhs_len[i]++]);
    }

    char str[100];
    printf("Enter the string to be parsed:\n");
    scanf("%s", str);

    int len = strlen(str), pos = 0;
    while (pos < len)
        pos += getToken(str, pos, input[in_cnt++]);

    int ip = 0;
    while (1)
    {
        while (tryReduce());              // reduce as much as possible

        if (ip == in_cnt) break;          // no input left

        strcpy(stack[top++], input[ip++]);   // shift
    }

    if (top == 1 && strcmp(stack[0], lhs[0]) == 0)
        printf("String is accepted\n");
    else
        printf("String is rejected\n");

    return 0;
}

/*
Sample input:

Enter number of productions : 4
E -> E+E
E -> E*E
E -> (E)
E -> id

String: id+id*id   ->  String is accepted
String: id+*id     ->  String is rejected
*/