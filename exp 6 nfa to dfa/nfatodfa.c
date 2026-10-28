#include <stdio.h>

#define MAX 10

int main() {
    int n, symbols;
    int transition[MAX][MAX][MAX];
    int dfa[MAX][MAX];
    int states[MAX][MAX] = {0};
    int dfaCount = 1;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("\nStates are numbered from 0 to %d\n", n - 1);

    // Input NFA transition matrices
    for (int s = 0; s < symbols; s++) {
        printf("\nEnter transition matrix for symbol %c (0/1):\n", 'a' + s);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &transition[s][i][j]);
    }

    // Initial DFA state = {0}
    states[0][0] = 1;

    // Subset construction
    for (int i = 0; i < dfaCount; i++) {

        for (int s = 0; s < symbols; s++) {

            int newState[MAX] = {0};

            // Find all states reachable on symbol
            for (int j = 0; j < n; j++) {
                if (states[i][j]) {
                    for (int k = 0; k < n; k++) {
                        if (transition[s][j][k])
                            newState[k] = 1;
                    }
                }
            }

            // Check if this set already exists
            int found = -1;

            for (int j = 0; j < dfaCount; j++) {
                int same = 1;

                for (int k = 0; k < n; k++) {
                    if (states[j][k] != newState[k]) {
                        same = 0;
                        break;
                    }
                }

                if (same) {
                    found = j;
                    break;
                }
            }

            // If new set, add it
            if (found == -1) {
                found = dfaCount++;

                for (int k = 0; k < n; k++)
                    states[found][k] = newState[k];
            }

            dfa[i][s] = found;
        }
    }

    // Display DFA states
    printf("\nDFA States:\n");

    for (int i = 0; i < dfaCount; i++) {
        printf("D%d = { ", i);

        for (int j = 0; j < n; j++)
            if (states[i][j])
                printf("%d ", j);

        printf("}\n");
    }

    // Display DFA transition table
    printf("\nDFA Transition Table:\n");

    printf("State\t");
    for (int s = 0; s < symbols; s++)
        printf("%c\t", 'a' + s);

    printf("\n");

    for (int i = 0; i < dfaCount; i++) {
        printf("D%d\t", i);

        for (int s = 0; s < symbols; s++)
            printf("D%d\t", dfa[i][s]);

        printf("\n");
    }

    return 0;
}
