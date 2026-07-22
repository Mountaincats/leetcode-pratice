int findLengthOfLCIS(int* nums, int numsSize) {
    int len = 1;
    int start = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] <= nums[i - 1]) start = i;
        len = fmax(len, i - start + 1);
    }

    return len;
}