#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjList;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    // Initialize adjacency list
    for (int i = 0; i < numVertices; ++i) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform BFS traversal and calculate distances
void BFS(struct Graph* graph, int startVertex, int* maxDistances, int* totalDistances) {
    // Mark all vertices as not visited
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = false;
    }

    // Create a queue for BFS
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = -1, rear = -1;

    // Mark the current node as visited and enqueue it
    visited[startVertex] = true;
    queue[++rear] = startVertex;

    // Initialize distances
    int distances[graph->numVertices];
    for (int i = 0; i < graph->numVertices; ++i) {
        distances[i] = -1;
    }
    distances[startVertex] = 0;

    while (front != rear) {
        // Dequeue a vertex from the queue
        int currentVertex = queue[++front];

        // Update max distances
        if (distances[currentVertex] > maxDistances[0]) {
            maxDistances[0] = distances[currentVertex];
            maxDistances[1] = currentVertex;
        } else if (distances[currentVertex] == maxDistances[0]) {
            // If there are multiple vertices with the same max distance
            maxDistances[1] = (currentVertex < maxDistances[1]) ? currentVertex : maxDistances[1];
        }

        // Get all adjacent vertices of the dequeued vertex
        struct Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[++rear] = adjVertex;
                distances[adjVertex] = distances[currentVertex] + 1;
            }
            temp = temp->next;
        }
    }

    // Calculate total distances
    for (int i = 0; i < graph->numVertices; ++i) {
        if (distances[i] != -1) {
            totalDistances[0] += distances[i];
        } else {
            // If the graph is not connected, set total distances to -1
            totalDistances[0] = -1;
            break;
        }
    }

    free(visited);
    free(queue);
}

// Function to free memory allocated for the graph
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* current = graph->adjList[i];
        while (current) {
            struct Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    int numVertices, numEdges;
    scanf("%d %d", &numVertices, &numEdges);

    // Create a graph with the given number of vertices
    struct Graph* graph = createGraph(numVertices);

    // Add edges to the graph
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int startVertex;
    scanf("%d", &startVertex);

    int maxDistances[2] = {-1, -1}; // {maxDistance, vertex}
    int totalDistances[1] = {0};    // {totalDistance}

    // Perform BFS starting from the specified vertex
    BFS(graph, startVertex, maxDistances, totalDistances);

    // Print the result
    printf("%d %d\n", maxDistances[1], maxDistances[0]);
    printf("%d\n", totalDistances[0]);

    // Free memory allocated for the graph
    freeGraph(graph);

    return 0;
}
