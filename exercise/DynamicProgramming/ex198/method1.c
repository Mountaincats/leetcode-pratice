#define max(a, b) ((a) > (b) ? (a) : (b))

int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];

    int p = nums[0];
    int q = max(nums[0], nums[1]);
    for (int i = 2; i < numsSize; i++) {
        p = max(p + nums[i], q);
        p = p ^ q;
        q = p ^ q;
        p = p ^ q;
    }

    return q;
}