/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    *returnSize = 0;

    int ansSize = 1;
    for (int i = 2; i <= numsSize; i++) {
        ansSize *= i;
    }
    int **ans = malloc(sizeof(int *) * ansSize);
    int *colans = malloc(sizeof(int) * ansSize);

    int *state = malloc(numsSize * sizeof(int));
    bool *selected = calloc(numsSize, sizeof(bool));

    void dfs(int state_size) {
        if (state_size == numsSize) {
            int *tmp = malloc(sizeof(int) * numsSize);
            memcpy(tmp, state, sizeof(int) * numsSize);
            ans[*returnSize] = tmp;
            colans[(*returnSize)++] = state_size;
        }
        for (int i = 0; i < numsSize; i++) {
            if (selected[i]) continue;
            selected[i] = true;
            state[state_size] = nums[i];
            dfs(state_size + 1);
            selected[i] = false;
        }
    }

    dfs(0);

    free(state);
    free(selected);

    *returnColumnSizes = colans;
    return ans;
}