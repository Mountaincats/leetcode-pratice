/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 1 << numsSize;
    int** ans = malloc(sizeof(int*) * (*returnSize));
    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));

    int* choice = malloc(sizeof(int) * numsSize);

    for (int mask = 0; mask < *returnSize; mask++) {
        int size = 0;
        for (int i = 0; i < numsSize; i++) {
            if ((mask >> i) & 1) {
                choice[size++] = nums[i];
            }
        }
        int* tmp = malloc(sizeof(int) * size);
        memcpy(tmp, choice, sizeof(int) * size);
        ans[mask] = tmp;
        (*returnColumnSizes)[mask] = size;
    }

    free(choice);
    return ans;
}