/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    int ansSize = 1;
    for (int i = 1; i <= k; i++) {
        ansSize = ansSize * (n - i + 1) / i;
    }

    int** ans = malloc(sizeof(int*) * ansSize);
    int* colans = malloc(sizeof(int) * ansSize);

    int* state = malloc(sizeof(int) * k);

    void dfs(int state_size, int select) {
        if (state_size == k) {
            int* tmp = malloc(sizeof(int) * k);
            memcpy(tmp, state, sizeof(int) * k);
            ans[*returnSize] = tmp;
            colans[(*returnSize)++] = state_size;
            return;
        }

        for (int i = select; i < n; i++) {
            state[state_size] = i + 1;
            dfs(state_size + 1, i + 1);
        }
    }

    dfs(0, 0);

    free(state);

    *returnColumnSizes = colans;
    return ans;
}