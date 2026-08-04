/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), compare);

    *returnSize = 0;

    int ansSize = 1;
    for (int i = 1; i <= numsSize; i++) {
        ansSize *= i;
    }

    int** ans = malloc(sizeof(int*) * ansSize);
    int* colans = malloc(sizeof(int) * ansSize);

    int* state = malloc(sizeof(int) * numsSize);
    bool* select = calloc(numsSize, sizeof(bool));

    void dfs(int state_size) {
        if (state_size == numsSize) {
            int* tmp = malloc(sizeof(int) * numsSize);
            memcpy(tmp, state, sizeof(int) * numsSize);
            ans[*returnSize] = tmp;
            colans[(*returnSize)++] = state_size;
            return;
        }
        for (int i = 0; i < numsSize; i++) {
            if (select[i] || (i > 0 && nums[i] == nums[i - 1]) && !select[i - 1]) continue;
            select[i] = true;
            state[state_size] = nums[i];

            dfs(state_size + 1);

            select[i] = false;
        }
    }

    dfs(0);

    *returnColumnSizes = colans;
    return ans;
}