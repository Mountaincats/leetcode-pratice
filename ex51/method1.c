/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

static bool valid(int* queen, int* col_use, int row, int col) {
    for(int i = 0; i < row; i++) {
        if(i + queen[i] == row + col || i - queen[i] == row - col || col_use[col]) return false;
    }
    return true;
}

void solve(int n, int depth, int* returnSize, char*** solutions, int* queen, int* col_use) {
    if(depth == n) {
        char** solution = malloc(sizeof(char*) * n);
        for(int i = 0; i < n; i++) {
            char* row = malloc(sizeof(char) * (n+1));
            memset(row, '.', n);
            row[queen[i]] = 'Q';
            row[n] = '\0';
            solution[i] = row;
        }

        solutions[*returnSize] = solution;
        (*returnSize)++;
        return;
    }
    for(int i = 0; i < n; i++) {
        queen[depth] = i;
        if(!valid(queen, col_use, depth, i)) {
            continue;
        };
        col_use[i] = 1;
        solve(n, depth+1, returnSize, solutions, queen, col_use);
        col_use[i] = 0;
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    char*** solutions = malloc(sizeof(char**) * 500);

    int queen[n];
    int col_use[n];
    memset(col_use, 0, sizeof(int) * n);
    solve(n, 0, returnSize, solutions, queen, col_use);

    int* returnColumn = malloc(*returnSize * sizeof(int));
    for(int i = 0; i < *returnSize; i++) {
        returnColumn[i] = n;
    }
    
    *returnColumnSizes = returnColumn;

    return solutions;
}