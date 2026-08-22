int maxSubArray(int* nums, int numsSize) {
    int sum = nums[0];
    int max_sum = sum;
    for (int i = 1; i < numsSize; i++) {
        sum = sum <= 0 ? nums[i] : nums[i] + sum;
        max_sum = fmax(sum, max_sum);
    }
    return max_sum;
}