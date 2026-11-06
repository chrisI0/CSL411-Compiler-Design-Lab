#include <stdio.h>
#include <ctype.h>
#include <string.h>

int prec(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int main() {
    char s[50], post[100], op[50], st[20][10];
    char qop[20], qa1[20][10], qa2[20][10], qres[20][10];
    int i, p = 0, top = -1, sp = -1, t = 0, n = 0;

    printf("Enter expression (like a=b+c*d): ");
    scanf("%s", s);
    for (i = 2; s[i] != '\0'; i++) {
        char c = s[i];
        if (isalnum(c)) {
            while (isalnum(s[i]))            /* read the whole operand */
                post[p++] = s[i++];
            post[p++] = ' ';
            i--;
        }
        else if (c == '(')
            op[++top] = c;
        else if (c == ')') {
            while (op[top] != '(') {
                post[p++] = op[top--];
                post[p++] = ' ';
            }
            top--;
        } else {
            while (top >= 0 && prec(op[top]) >= prec(c)) {
                post[p++] = op[top--];
                post[p++] = ' ';
            }
            op[++top] = c;
        }
    }
    while (top >= 0) {
        post[p++] = op[top--];
        post[p++] = ' ';
    }
    post[p] = '\0';
    for (i = 0; post[i] != '\0'; i++) {
        if (post[i] == ' ')
            continue;
        if (isalnum(post[i])){
            int k=0;
            ++sp;
            while (isalnum(post[i]))
                st[sp][k++]=post[i++];
            st[sp][k]='\0';
        
        } else {
            char *b = st[sp--];
            char *a = st[sp--];
            t++;
            qop[n] = post[i];
            strcpy(qa1[n], a);
            strcpy(qa2[n], b);
            sprintf(qres[n], "t%d", t);
            n++;
            sprintf(st[++sp], "t%d", t);
        }
    }
    qop[n] = '=';
    strcpy(qa1[n], st[sp]);
    strcpy(qa2[n], "-");
    sprintf(qres[n], "%c", s[0]);
    n++;
    printf("\nThree Address Code:\n");
    for (i = 0; i < n - 1; i++)
        printf("%s = %s %c %s\n", qres[i], qa1[i], qop[i], qa2[i]);
    printf("%s = %s\n", qres[n - 1], qa1[n - 1]);
    printf("\nQuadruple:\n");
    printf("No.\tOp\tArg1\tArg2\tResult\n");
    for (i = 0; i < n; i++)
        printf("%d\t%c\t%s\t%s\t%s\n", i, qop[i], qa1[i], qa2[i], qres[i]);
    return 0;
}