/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    int ansSize = pow(2, numsSize);
    int** ans = malloc(sizeof(int*) * ansSize);
    int* colans = malloc(sizeof(int) * ansSize);

    int* state = malloc(sizeof(int) * numsSize);
    int stateSize = 0;

    void dfs(int i) {
        if (i == numsSize) {
            int* tmp = malloc(sizeof(int) * stateSize);
            memcpy(tmp, state, sizeof(int) * stateSize);
            ans[*returnSize] = tmp;
            colans[(*returnSize)++] = stateSize;
            return;
        }

        dfs(i + 1);

        state[stateSize++] = nums[i];
        dfs(i + 1);
        stateSize--;
    }

    dfs(0);

    free(state);

    *returnColumnSizes = colans;
    return ans;
}