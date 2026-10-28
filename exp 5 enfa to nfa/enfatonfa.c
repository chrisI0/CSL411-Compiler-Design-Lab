#include <stdio.h>

#define MAX 10

int main() {
    int n, symbols;
    int epsilon[MAX][MAX], eclosure[MAX][MAX] = {0};

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("\nStates are numbered from 0 to %d\n", n - 1);

    printf("\nEnter epsilon transition matrix (0/1):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &epsilon[i][j]);
            // Every state reaches itself (i == j) plus direct epsilon edges
            eclosure[i][j] = (i == j) || epsilon[i][j];
        }
    }

    // Floyd-Warshall Algorithm for Transitive Closure
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                eclosure[i][j] |= (eclosure[i][k] && eclosure[k][j]);

    printf("\nEpsilon Closures:\n");
    for (int i = 0; i < n; i++) {
        printf("E-Closure(%d) = { ", i);
        for (int j = 0; j < n; j++)
            if (eclosure[i][j]) printf("%d ", j);
        printf("}\n");
    }

    for (int sym = 0; sym < symbols; sym++) {
        int matrix[MAX][MAX];
        printf("\nEnter transition matrix for symbol %c (0/1):\n", 'a' + sym);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &matrix[i][j]);

        printf("\nNFA Transition for symbol %c:\n", 'a' + sym);
        for (int i = 0; i < n; i++) {
            printf("δ(%d,%c) = { ", i, 'a' + sym);
            for (int target = 0; target < n; target++) {
                int reaches = 0;
                // Check if i -> j (via eps), j -> k (via sym), and k -> target (via eps)
                for (int j = 0; j < n && !reaches; j++) {
                    for (int k = 0; k < n && !reaches; k++) {
                        if (eclosure[i][j] && matrix[j][k] && eclosure[k][target])
                            reaches = 1;
                    }
                }
                if (reaches) printf("%d ", target);
            }
            printf("}\n");
        }
    }

    return 0;
} 
