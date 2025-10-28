#include <stdio.h>
#include <stdlib.h>

int isSafe(int board[], int row, int col, int n) {
    for (int i = 0; i < col; i++) {
        // Check same row or diagonal attacks in previous columns
        if (board[i] == row || abs(board[i] - row) == abs(i - col))
            return 0;
    }
    return 1;
}

int solveNQUtil(int board[], int col, int n) {
    if (col == n) {
        // Print solution
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf(board[j] == i ? "Q " : ". ");
            printf("\n");
        }
        printf("\n");
        return 1; // For all solutions remove 'return 1' and count solutions
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            board[col] = i;
            res = solveNQUtil(board, col + 1, n) || res; // Find all solutions by removing '|| res'
        }
    }
    return res;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    int board[n];
    for (int i = 0; i < n; i++) board[i] = -1;

    if (!solveNQUtil(board, 0, n))
        printf("No solution exists.\n");
    return 0;
}
