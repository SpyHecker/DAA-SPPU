#include <stdio.h>
#include <stdlib.h>
#define N 10
#define INF 99999

int n, final_path[N+1];
int visited[N];
int min_cost = INF;

// Function to find the minimum edge cost having an end at the vertex i
int firstMin(int cost[][N], int i) {
    int min = INF;
    for (int k = 0; k < n; k++)
        if (cost[i][k] < min && i != k)
            min = cost[i][k];
    return min;
}

// Function to find the second minimum edge cost having an end at the vertex i
int secondMin(int cost[][N], int i) {
    int first = INF, second = INF;
    for (int j=0; j<n; j++) {
        if (i == j)
            continue;
        if (cost[i][j] <= first) {
            second = first;
            first = cost[i][j];
        } else if (cost[i][j] <= second && cost[i][j] != first)
            second = cost[i][j];
    }
    return second;
}

// Recursive function that takes as arguments:
// current bound, current weight, level, and current path
void TSPRec(int cost[][N], int curr_bound, int curr_weight, int level, int curr_path[]) {
    // when we reach the last level, update minimum cost
    if (level == n) {
        if (cost[curr_path[level-1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + cost[curr_path[level-1]][curr_path[0]];
            if (curr_res < min_cost) {
                for (int i = 0; i < n; i++)
                    final_path[i] = curr_path[i];
                final_path[n] = curr_path[0];
                min_cost = curr_res;
            }
        }
        return;
    }

    // go to the nearest city not visited
    for (int i = 0; i < n; i++) {
        if (cost[curr_path[level-1]][i] != 0 && visited[i] == 0) {
            int temp = curr_bound;
            curr_weight += cost[curr_path[level-1]][i];

            // Different computation of curr_bound for level 1 and other levels
            if (level == 1)
                curr_bound -= ((firstMin(cost, curr_path[level-1]) + firstMin(cost, i)) / 2);
            else
                curr_bound -= ((secondMin(cost, curr_path[level-1]) + firstMin(cost, i)) / 2);

            if (curr_bound + curr_weight < min_cost) {
                curr_path[level] = i;
                visited[i] = 1;
                TSPRec(cost, curr_bound, curr_weight, level+1, curr_path);
            }

            curr_weight -= cost[curr_path[level-1]][i];
            curr_bound = temp;
            visited[i] = 0;
        }
    }
}

// Solves the TSP and prints the min cost and the path
void TSP(int cost[][N]) {
    int curr_path[N+1];
    int curr_bound = 0;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    // Compute initial lower bound for the root node
    for (int i = 0; i < n; i++)
        curr_bound += (firstMin(cost, i) + secondMin(cost, i));
    curr_bound = curr_bound & 1 ? curr_bound/2 + 1 : curr_bound/2;
    visited[0] = 1;
    curr_path[0] = 0;

    TSPRec(cost, curr_bound, 0, 1, curr_path);

    printf("\nMinimum cost: %d\n", min_cost);
    printf("Path: ");
    for (int i = 0; i <= n; i++)
        printf("%d ", final_path[i]);
    printf("\n");
}

int main() {
    printf("Enter number of cities: ");
    scanf("%d", &n);
    int cost[N][N];
    printf("Enter the cost matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);
    TSP(cost);
    return 0;
}
