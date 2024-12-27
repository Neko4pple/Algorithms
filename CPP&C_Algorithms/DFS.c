#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

void dfs(int graph[MAX_NODES][MAX_NODES], int node, bool visited[MAX_NODES], int destination);

int main() {
    int graph[MAX_NODES][MAX_NODES] = {0};
    bool visited[MAX_NODES] = {false};

    int numNodes, numEdges;
    scanf("%d %d", &numNodes, &numEdges);

    // Reading edges
    for (int i = 0; i < numEdges; ++i) {
        char source, destination;
        scanf(" %c %c", &source, &destination);

        int sourceNode = source - 'a';
        int destNode = destination - 'a';

        // Assuming directed edges
        graph[sourceNode][destNode] = 1;
    }

    int numDestinations;
    scanf("%d", &numDestinations);

    // Reading destinations
    for (int i = 0; i < numDestinations; ++i) {
        int destination;
        scanf("%d", &destination);

        printf("Destination %d: ", destination);

        // Clear visited array for each destination
        for (int j = 0; j < MAX_NODES; ++j) {
            visited[j] = false;
        }

        dfs(graph, 0, visited, destination - 1); // Start DFS from node 'a'

        // Print the visited nodes in ascending order
        for (int j = 0; j < MAX_NODES; ++j) {
            if (visited[j]) {
                printf("%c ", j + 'a');
            }
        }

        printf("\n");
    }

    return 0;
}

void dfs(int graph[MAX_NODES][MAX_NODES], int node, bool visited[MAX_NODES], int destination) {
    visited[node] = true;

    for (int i = 0; i < MAX_NODES; ++i) {
        if (graph[node][i] && !visited[i]) {
            if (i == destination) {
                visited[i] = true; // Mark destination as visited
                return;
            }
            dfs(graph, i, visited, destination);
        }
    }
}
