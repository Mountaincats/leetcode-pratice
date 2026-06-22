/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
    // i 代表的是待插入元素的索引，也代表待插入元素的目前插入位置
    for (int i = 1; i < numsSize; i++) {
        int ins = nums[i];
        // j 代表的是待插入元素的目前插入位置的前一个元素的索引
        int j = i - 1;
        while (j >= 0 && ins < nums[j]) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = ins;
    }


    *returnSize = numsSize;
    return nums;
}