#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, nt_cnt = 0;
char lhs[100][100], nts[20][20], rhs[100][10][20];
int rhs_len[100];
char str[100];

int ip = 0;

// Removes direct left recursion:  A -> A x | b   ==>   A -> b A'   and   A' -> x A' | #
void removeLeftRecursion()
{
    int oldN = n;                          // only look at the original productions

    for (int k = 0; k < nt_cnt; k++)
    {
        char *A = nts[k];

        // Step 1: does this non-terminal have a left-recursive production?
        int hasLR = 0;
        for (int i = 0; i < oldN; i++)
            if (strcmp(lhs[i], A) == 0 && strcmp(rhs[i][0], A) == 0)
                hasLR = 1;

        if (!hasLR) continue;              // nothing to fix for this one

        // Step 2: make the new non-terminal name A'
        char newNT[20];
        strcpy(newNT, A);
        strcat(newNT, "'");

        // Step 3: rewrite every production of A
        for (int i = 0; i < oldN; i++)
        {
            if (strcmp(lhs[i], A) != 0) continue;

            if (strcmp(rhs[i][0], A) == 0)
            {
                // A -> A x   becomes   A' -> x A'
                for (int j = 1; j < rhs_len[i]; j++)      // drop the first symbol (A)
                    strcpy(rhs[i][j - 1], rhs[i][j]);
                rhs_len[i]--;
                strcpy(rhs[i][rhs_len[i]++], newNT);      // add A' at the end
                strcpy(lhs[i], newNT);                    // change left side to A'
            }
            else
            {
                // A -> b   becomes   A -> b A'
                if (strcmp(rhs[i][0], "#") == 0)
                    strcpy(rhs[i][0], newNT);             // A -> #  becomes  A -> A'
                else
                    strcpy(rhs[i][rhs_len[i]++], newNT);
            }
        }

        // Step 4: add  A' -> #
        strcpy(lhs[n], newNT);
        strcpy(rhs[n][0], "#");
        rhs_len[n] = 1;
        n++;
    }
}

// Match the list of pending symbols against str starting at ip.
int parse(char pending[][20], int cnt)
{
    if (cnt == 0)
        return str[ip] == '\0';          // all symbols matched: input must be fully consumed

    char *sym = pending[0];

    if (isupper(sym[0]))                 // non-terminal: try each production
    {
        for (int i = 0; i < n; i++)
        {
            if (strcmp(lhs[i], sym) != 0) continue;

            char next[200][20];
            int m = 0;
            for (int j = 0; j < rhs_len[i]; j++)      // production body first
                strcpy(next[m++], rhs[i][j]);
            for (int j = 1; j < cnt; j++)             // then the remaining pending symbols
                strcpy(next[m++], pending[j]);

            int save = ip;
            if (parse(next, m)) return 1;
            ip = save;                                // backtrack
        }
        return 0;
    }

    if (strcmp(sym, "#") == 0)           // epsilon: consume nothing
        return parse(pending + 1, cnt - 1);

    int l = strlen(sym);                 // terminal
    if (strncmp(&str[ip], sym, l) == 0)
    {
        ip += l;
        if (parse(pending + 1, cnt - 1)) return 1;
        ip -= l;                         // backtrack
    }
    return 0;
}

int main()
{
    printf("Enter number of productions : ");
    scanf("%d", &n);
    printf("Enter productions in the form A -> aB (use # for epsilon):\n");

    for (int i = 0; i < n; i++)
    {
        char buf[100];
        scanf("%s -> %s", lhs[i], buf);

        int found = 0;
        for (int j = 0; j < nt_cnt; j++)
            if (strcmp(lhs[i], nts[j]) == 0) found = 1;
        if (!found)
            strcpy(nts[nt_cnt++], lhs[i]);

        int len = strlen(buf), pos = 0;
        rhs_len[i] = 0;
        while (pos < len)
        {
            if (strncmp(&buf[pos], "id", 2) == 0)        { strcpy(rhs[i][rhs_len[i]++], "id");   pos += 2; }
            else if (strncmp(&buf[pos], "if", 2) == 0)   { strcpy(rhs[i][rhs_len[i]++], "if");   pos += 2; }
            else if (strncmp(&buf[pos], "then", 4) == 0) { strcpy(rhs[i][rhs_len[i]++], "then"); pos += 4; }
            else if (strncmp(&buf[pos], "else", 4) == 0) { strcpy(rhs[i][rhs_len[i]++], "else"); pos += 4; }
            else if (isupper(buf[pos]))
            {
                char tok[10] = {buf[pos++], '\0'};
                if (pos < len && buf[pos] == '\'') { tok[1] = buf[pos++]; tok[2] = '\0'; }
                strcpy(rhs[i][rhs_len[i]++], tok);
            }
            else
            {
                char tok[10] = {buf[pos++], '\0'};
                strcpy(rhs[i][rhs_len[i]++], tok);
            }
        }
    }

    char startSym[20];
    strcpy(startSym, lhs[0]);      // save the start symbol BEFORE rewriting

    removeLeftRecursion();         // fix the grammar first

    printf("\nGrammar after removing left recursion:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s -> ", lhs[i]);
        for (int j = 0; j < rhs_len[i]; j++)
            printf("%s", rhs[i][j]);
        printf("\n");
    }

    printf("\nEnter the string to be parsed:\n");
    scanf("%s", str);

    char start[1][20];
    strcpy(start[0], startSym);

    if (parse(start, 1))
        printf("String is accepted\n");
    else
        printf("String is rejected\n");

    return 0;
}

/*
Example with left recursion:

Enter number of productions : 4
A -> aB
A -> bc
A -> Ax
B -> c

Grammar after removing left recursion:
A -> aBA'
A -> bcA'
A' -> xA'
B -> c
A' -> #

String: acxxxxx  -> String is accepted
String: acxxy    -> String is rejected (no segmentation fault)
*/