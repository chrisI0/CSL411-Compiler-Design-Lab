#include <stdio.h>

#define MAX 20

int n, adj[MAX][MAX], visited[MAX];

// Standard Depth First Search
void dfs(int state) {
    visited[state] = 1;
    for (int i = 0; i < n; i++) {
        if (adj[state][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int t, src, dest;
    char sym;

    printf("Number of states & transitions: ");
    if (scanf("%d %d", &n, &t) != 2 || n <= 0 || n > MAX) return 1;

    // Read transitions
    printf("<state> <transition e/a/b> <state>\n");
    for (int i = 0; i < t; i++) {
        scanf("%d %c %d", &src, &sym, &dest);
        if (sym == 'e' || sym == 'E') {
            adj[src][dest] = 1;
        }
    }

    // Compute and print epsilon closure for each state
    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < n; i++) {
        // Reset visited array for current state's search
        for (int j = 0; j < n; j++) visited[j] = 0;

        dfs(i);

        // Print all states reachable from state 'i'
        printf("e-Closure(q%d) = { ", i);
        for (int j = 0; j < n; j++) {
            if (visited[j]) printf("q%d ", j);
        }
        printf("}\n");
    }

    return 0;
}
