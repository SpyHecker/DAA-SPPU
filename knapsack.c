#include <stdio.h>
#include <stdlib.h>

// Structure for items
struct Item {
    int value;
    int weight;
    float ratio;
};

// Function to compare items for sorting
int compare(const void *a, const void *b) {
    float r1 = ((struct Item *)a)->ratio;
    float r2 = ((struct Item *)b)->ratio;
    return (r2 - r1) > 0 ? 1 : -1;
}

// Fractional Knapsack using Greedy
float fractionalKnapsack(struct Item items[], int n, int capacity) {
    // Calculate value/weight ratio and sort
    for (int i = 0; i < n; i++)
        items[i].ratio = (float)items[i].value / items[i].weight;
    qsort(items, n, sizeof(struct Item), compare);

    float totalValue = 0;
    int currentWeight = 0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            int remainingWeight = capacity - currentWeight;
            totalValue += items[i].ratio * remainingWeight;
            break;
        }
    }
    return totalValue;
}

// 0/1 Knapsack using Dynamic Programming
int knapsack01(int values[], int weights[], int n, int capacity) {
    int dp[capacity + 1];
    for (int i = 0; i <= capacity; i++)
        dp[i] = 0;

    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            if (dp[w - weights[i]] + values[i] > dp[w])
                dp[w] = dp[w - weights[i]] + values[i];
        }
    }
    return dp[capacity];
}

int main() {
    int n, capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    struct Item items[n];
    int values[n], weights[n];

    printf("Enter values and weights for each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d (value weight): ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
        values[i] = items[i].value;
        weights[i] = items[i].weight;
    }

    // Solve using both methods
    float fractionalResult = fractionalKnapsack(items, n, capacity);
    int zeroOneResult = knapsack01(values, weights, n, capacity);

    printf("\nResults:\n");
    printf("Fractional Knapsack (Greedy): %.2f\n", fractionalResult);
    printf("0/1 Knapsack (Dynamic): %d\n", zeroOneResult);

    return 0;
}