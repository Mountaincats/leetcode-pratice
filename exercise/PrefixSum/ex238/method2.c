/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int *ans = malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;

    ans[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        ans[i] = ans[i - 1] * nums[i - 1];
    }

    for (int i = numsSize - 1, L_product = 1; i >= 0; i--) {
        ans[i] = ans[i] * L_product;
        L_product *= nums[i];
    }

    return ans;
}