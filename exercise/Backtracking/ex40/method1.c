/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    qsort(candidates, candidatesSize, sizeof(int), compare);

    int** ans = malloc(sizeof(int*) * 2000);
    int* colans = malloc(sizeof(int) * 2000);

    int* combine = malloc(sizeof(int) * candidatesSize);
    int size = 0;

    int sum = 0;
    bool last_select = true;
    int last = candidates[0];
    void dfs(int depth) {
        if (sum == target) {
            int* tmp = malloc(sizeof(int) * size);
            memcpy(tmp, combine, sizeof(int) * size);
            ans[*returnSize] = tmp;
            colans[(*returnSize)++] = size;
            return;
        }
        else if (depth == candidatesSize) {
            return;
        }

        if ((last_select && candidates[depth] == last || candidates[depth] != last) && sum + candidates[depth] <= target) {
            combine[size] = candidates[depth];
            sum += candidates[depth];
            size++;
            last = candidates[depth];
            last_select = true;
            
            dfs(depth + 1);
            
            sum -= candidates[depth];
            size--;
        }

        last = candidates[depth];
        last_select = false;
        dfs(depth + 1);
    }

    dfs(0);

    free(combine);

    *returnColumnSizes = colans;
    return ans;
}