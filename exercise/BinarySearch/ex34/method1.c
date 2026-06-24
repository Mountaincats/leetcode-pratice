/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* ans = malloc(sizeof(int) * 2);
    ans[0] = -1;
    ans[1] = -1;

    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    if (left == numsSize || nums[left] != target) return ans;
    ans[0] = left;

    left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] <= target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    ans[1] = left - 1;

    *returnSize = 2;
    return ans;
}