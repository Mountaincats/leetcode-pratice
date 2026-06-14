/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int *prefix = malloc(sizeof(int) * (numsSize + 1));
    int *suffix = malloc(sizeof(int) * (numsSize + 1));
    int *ans = malloc(sizeof(int) * numsSize);

    prefix[0] = 1;
    suffix[0] = 1;
    *returnSize = numsSize;

    for (int i = 1; i <= numsSize; i++) {
        prefix[i] = prefix[i - 1] * nums[i - 1];
        suffix[i] = suffix[i - 1] * nums[numsSize - i];
    }

    for (int i = 0; i < numsSize; i++) {
        ans[i] = prefix[i] * suffix[numsSize - i - 1];
    }

    free(prefix);
    free(suffix);

    return ans;
}