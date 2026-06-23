/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void mergeSort(int* nums, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid + 1, r);

    int i = l, j = mid + 1;
    int cnt = 0;
    int* tmp = malloc(sizeof(int) * (r - l + 1));
    while (i <= mid && j <= r) {
        if (nums[i] <= nums[j]) tmp[cnt++] = nums[i++];
        else tmp[cnt++] = nums[j++];
    }
    while (i <= mid) {
        tmp[cnt++] = nums[i++];
    }
    while (j <= r) {
        tmp[cnt++] = nums[j++];
    }

    memcpy(nums + l, tmp, (r - l + 1) * sizeof(int));
    free(tmp);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    mergeSort(nums, 0, numsSize - 1);
    *returnSize = numsSize;

    return nums;
}

/* alloc global tmp array */

// void mergeSort(int* nums, int* tmp, int l, int r) {
//     if (l >= r) return;
//     int mid = (l + r) / 2;
//     mergeSort(nums, tmp, l, mid);
//     mergeSort(nums, tmp, mid + 1, r);

//     int i = l, j = mid + 1;
//     int cnt = 0;
//     while (i <= mid && j <= r) {
//         if (nums[i] <= nums[j]) tmp[cnt++] = nums[i++];
//         else tmp[cnt++] = nums[j++];
//     }
//     while (i <= mid) {
//         tmp[cnt++] = nums[i++];
//     }
//     while (j <= r) {
//         tmp[cnt++] = nums[j++];
//     }

//     memcpy(nums + l, tmp, (r - l + 1) * sizeof(int));
// }

// int* sortArray(int* nums, int numsSize, int* returnSize) {
//     int* tmp = malloc(sizeof(int) * numsSize);
//     mergeSort(nums, tmp, 0, numsSize - 1);
//     *returnSize = numsSize;
//     free(tmp);
//     return nums;
// }