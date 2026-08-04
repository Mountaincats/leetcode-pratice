/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// method1 需要知道数据范围来确定哈希表大小，能处理的数据范围有限的同时还会因数据大小影响使用的存储空间大小

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
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
        bool hash[21] = {false};
        for (int i = 0; i < numsSize; i++) {
            if (select[i] || hash[nums[i] + 10]) continue;
            hash[nums[i] + 10] = true;
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