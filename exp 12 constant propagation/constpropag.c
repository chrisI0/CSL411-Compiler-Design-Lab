#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int n, i, j, k, isNum;
    int val[26] = {0};      /* value of each variable a-z */
    int isConst[26] = {0};  /* 1 if variable holds a constant */
    char lhs, rhs[50], out[100];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements (like a = 10):\n");
    for (i = 0; i < n; i++) {
        scanf(" %c = %s", &lhs, rhs);

        /* replace constant variables in right side with their values */
        k = 0;
        for (j = 0; rhs[j] != '\0'; j++) {
            if (isalpha(rhs[j]) && isConst[rhs[j] - 'a'])
                k += sprintf(out + k, "%d", val[rhs[j] - 'a']);
            else
                out[k++] = rhs[j];
        }
        out[k] = '\0';

        /* if right side is only digits, left variable is a constant */
        isNum = 1;
        for (j = 0; out[j] != '\0'; j++)
            if (!isdigit(out[j]))
                isNum = 0;

        isConst[lhs - 'a'] = isNum;      /* reassignment updates this */
        if (isNum)
            val[lhs - 'a'] = atoi(out);

        printf("%c = %s\n", lhs, out);
    }
    return 0;
}