#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int src, dest, weight;
};

// Bellman-Ford algorithm to find shortest paths from source
// Returns 0 if no negative weight cycle exists, else -1
int bellmanFord(int V, int E, struct Edge edges[], int src, int dist[]) {
    // Initialize distances from source to all vertices as infinite
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Relax all edges V-1 times (dynamic programming iterative update)
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative weight cycles by one more relaxation
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            return -1;  // Negative cycle detected
        }
    }

    return 0;  // No negative cycle detected
}

int main() {
    int V, E, src;
    printf("Enter number of vertices and edges: ");
    scanf("%d%d", &V, &E);
    struct Edge* edges = (struct Edge*) malloc(E * sizeof(struct Edge));
    printf("Enter edges (src dest weight):\n");
    for(int i = 0; i < E; i++) {
        scanf("%d%d%d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }
    printf("Enter source vertex: ");
    scanf("%d", &src);

    int dist[V];
    int result = bellmanFord(V, E, edges, src, dist);
    if (result == -1) {
        printf("Graph contains a negative weight cycle\n");
    } else {
        printf("Vertex Distance from Source\n");
        for (int i = 0; i < V; i++)
            printf("%d \t\t %d\n", i, dist[i]);
        printf("\nTime Complexity: O(V * E) where V = %d, E = %d\n", V, E);
    }

    free(edges);
    return 0;
}
