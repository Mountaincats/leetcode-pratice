/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void adjust(int* nums, int i, int numsSize) {
    int j;
    int temp;
    temp = nums[i];
    j = 2 * i + 1; // 指向i的左孩子
    while (j < numsSize) {
        if (j + 1 < numsSize && nums[j] < nums[j + 1]) j++; // j指向孩子中的大值
        if (temp < nums[j]) { //如果孩子大
            nums[(j - 1) / 2] = nums[j]; //大孩子换到父结点
            j = 2 * j + 1; // 指向左孩子
        }
        else break;
    }
    nums[(j - 1) / 2] = temp; //当前j的结点赋值为temp
}

void heapSort(int* nums, int numsSize) {
    int i;
    int temp;
    for (i = numsSize / 2 - 1; i >= 0; i--) adjust(nums, i, numsSize);
    for (i = numsSize - 1 ; i >= 1; i--) {
        temp = nums[i];
        nums[i] = nums[0];
        nums[0] = temp;
        adjust(nums, 0, i);
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    heapSort(nums, numsSize);
    *returnSize = numsSize;
    return nums;
}