#define max(a, b) ((a) > (b) ? (a) : (b))

int robrange(int* nums, int start, int end) {
    int p = 0, q = 0;

    for (int i = start; i <= end; i++) {
        p = max(p + nums[i], q);
        p = p ^ q;
        q = p ^ q;
        p = p ^ q;
    }

    return q;
}

int rob(int* nums, int numsSize) {
    return max(nums[0] + robrange(nums, 2, numsSize - 2), robrange(nums, 1, numsSize - 1));
}