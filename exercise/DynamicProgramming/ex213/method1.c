#define max(a, b) ((a) > (b) ? (a) : (b))

int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];
    if (numsSize == 2) return max(nums[0], nums[1]);

    int steal_first;
    int p = nums[0], q = max(nums[0], nums[1]);
    for (int i = 2; i < numsSize - 1; i++) {
        p = max(p + nums[i], q);
        p = p ^ q;
        q = p ^ q;
        p = p ^ q;
    }
    steal_first = q;

    p = nums[1], q = max(nums[1], nums[2]);
    for (int i = 3; i < numsSize; i++) {
        p = max(p + nums[i], q);
        p = p ^ q;
        q = p ^ q;
        p = p ^ q;
    }
    q = max(q, steal_first);

    return q;
}