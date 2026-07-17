#define max(a, b) ((a) > (b) ? (a) : (b))

int robrange(int* nums, int start, int end) {
    int p = nums[start], q = max(nums[start], nums[start + 1]);

    for (int i = start + 2; i <= end; i++) {
        p = max(p + nums[i], q);
        p = p ^ q;
        q = p ^ q;
        p = p ^ q;
    }

    return q;
}

int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];
    if (numsSize == 2) return max(nums[0], nums[1]);

    return max(robrange(nums, 0, numsSize - 2), robrange(nums, 1, numsSize - 1));
}