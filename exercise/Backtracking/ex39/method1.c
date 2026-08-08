/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), cmp);

    *returnSize = 0;

    int** ans = malloc(sizeof(int*) * 150);
    int* colans = malloc(sizeof(int) * 150);

    int* combine = malloc(sizeof(int) * 20);

    int sum = 0;
    void dfs(int size, int start) {
        if (sum == target) {
            int* tmp = malloc(sizeof(int) * size);
            memcpy(tmp, combine, sizeof(int) * size);
            ans[*returnSize] = tmp;
            colans[(*returnSize)++] = size;
            return;
        }

        for (int i = start; i < candidatesSize; i++) {
            if (sum + candidates[i] > target) {
                break;
            }
            sum += candidates[i];
            combine[size] = candidates[i];
            dfs(size + 1, i);
            sum -= candidates[i];
        }
    }

    dfs(0, 0);

    free(combine);
    *returnColumnSizes = colans;
    return ans;
}