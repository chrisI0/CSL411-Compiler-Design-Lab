#include <stdio.h>

#define MAX 20

int main() {
    int n, m, t[MAX][MAX], f[MAX] = {0};
    int g[MAX], ng[MAX], nf, i, j, k, s, changed;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter transition table:\n");
    for (i = 0; i < n; i++)
        for (s = 0; s < m; s++)
            scanf("%d", &t[i][s]);

    printf("Enter number of final states: ");
    scanf("%d", &nf);

    printf("Enter final states: ");
    for (i = 0; i < nf; i++) {
        scanf("%d", &j);
        f[j] = 1;
    }

    /* Initial groups: 0 = non-final, 1 = final */
    for (i = 0; i < n; i++)
        g[i] = f[i];

    /* Refine groups */
    do {    
        changed = 0; // flag to check if any group changed

        for (i = 0; i < n; i++)
            ng[i] = -1;

        int count = 0;

        for (i = 0; i < n; i++) {
            if (ng[i] != -1)
                continue;

            ng[i] = count;

            for (j = i + 1; j < n; j++) {
                if (g[i] != g[j])
                    continue;

                int same = 1;

                for (s = 0; s < m; s++)
                    if (g[t[i][s]] != g[t[j][s]])
                        same = 0;

                if (same)
                    ng[j] = count;
            }

            count++;
        }

        for (i = 0; i < n; i++) {
            if (g[i] != ng[i])
                changed = 1;
            g[i] = ng[i];
        }

    } while (changed);

    /* Display groups */
    int groups = 0;

    for (i = 0; i < n; i++)
        if (g[i] + 1 > groups)
            groups = g[i] + 1;

    printf("\nMinimized States:\n");

    for (i = 0; i < groups; i++) {
        printf("G%d = { ", i);
        for (j = 0; j < n; j++)
            if (g[j] == i)
                printf("%d ", j);
        printf("}\n");
    }

    /* Minimized transition table */
    printf("\nMinimized DFA:\n");
    printf("State\t");

    for (s = 0; s < m; s++)
        printf("%c\t", 'a' + s);

    printf("\n");

    for (i = 0; i < groups; i++) {
        for (j = 0; j < n; j++)
            if (g[j] == i)
                break;

        printf("G%d\t", i);

        for (s = 0; s < m; s++)
            printf("G%d\t", g[t[j][s]]);

        printf("\n");
    }

    return 0;
}