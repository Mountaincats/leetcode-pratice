struct Status {
    int lsum, rsum, msum, isum;
};

struct Status get(int* nums, int l, int r) {
    if (l == r) return (struct Status){nums[l], nums[l], nums[l], nums[l]};
    int mid = (l + r) / 2;
    struct Status l_interval = get(nums, l, mid);
    struct Status r_interval = get(nums, mid + 1, r);

    struct Status res;
    res.lsum = fmax(l_interval.lsum, l_interval.isum + r_interval.lsum);
    res.rsum = fmax(r_interval.rsum, r_interval.isum + l_interval.rsum);
    res.isum = l_interval.isum + r_interval.isum;
    res.msum = fmax(fmax(l_interval.msum, r_interval.msum), l_interval.rsum + r_interval.lsum);

    return res;
}

int maxSubArray(int* nums, int numsSize) {
    return get(nums, 0, numsSize - 1).msum;
}