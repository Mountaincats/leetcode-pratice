/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;

    // 异或交换 swap 在 a 和 b 指向同一地址时会把值清零，不建议使用，比如本代码中使用会有问题
    // *a = *a ^ *b;
    // *b = *a ^ *b;
    // *a = *a ^ *b;
}

int partition(int* nums, int left, int right) {
    int i = left + rand() % (right - left + 1);
    int pivot = nums[i];
    swap(&nums[i], &nums[left]);

    i = left + 1;
    int j = right;
    while (true) {
        while (i <= j && nums[i] < pivot) {
            i++;
        }
        while (i <= j && nums[j] > pivot) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(&nums[i], &nums[j]);
        i++;
        j--;
    }

    swap(&nums[left], &nums[j]);
    return j;
}

void quickSort(int* nums, int left, int right) {
    bool ordered = true;
    for (int i = left; i < right; i++) {
        if (nums[i] > nums[i + 1]) {
            ordered = false;
            break;
        }
    }
    if (ordered) return;

    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    srand(time(NULL));
    quickSort(nums, 0, numsSize - 1);

    *returnSize = numsSize;
    return nums;
}