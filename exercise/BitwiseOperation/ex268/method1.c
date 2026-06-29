int compare (const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int missingNumber(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] <= mid) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return left;
}