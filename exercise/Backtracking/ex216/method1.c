/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    int** ans = malloc(sizeof(int*) * 2000);
    int* colans = malloc(sizeof(int) * 2000);

    int* combine = malloc(sizeof(int) * k);
    int size = 0;
    int sum = 0;

    void dfs(int depth, int start) {
        if (size == k) {
            if (sum == n) {
                int* tmp = malloc(sizeof(int) * k);
                memcpy(tmp, combine, sizeof(int) * k);
                ans[*returnSize] = tmp;
                colans[(*returnSize)++] = k;
            }
            return;
        }

        for (int i = start; i <= 9; i++) {
            if (sum + i > n) return;
            sum += i;
            combine[size++] = i;
            dfs(depth + 1, i + 1);
            sum -= i;
            size--;
        }
    }

    dfs(0, 1);

    free(combine);

    *returnColumnSizes = colans;
    return ans;
}