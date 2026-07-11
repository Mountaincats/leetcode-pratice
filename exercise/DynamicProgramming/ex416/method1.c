#define max(a, b) ((a) > (b) ? (a) : (b))

bool canPartition(int* nums, int numsSize) {
    if (numsSize < 2) return false;
    
    int sum = nums[0], maxNum = nums[0];
    for (int i = 1; i < numsSize; i++) {
        sum += nums[i];
        maxNum = max(nums[i], maxNum);
    }

    if (sum & 1) return false;
    int target = sum >> 1;
    if (maxNum > target) return false;

    bool dp[target + 1];
    memset(dp, 0, sizeof(dp));

    dp[0] = true;
    dp[nums[0]] = true;
    for (int i = 1; i < numsSize; i++) {
        for (int j = target; j >= nums[i]; j--) {
            dp[j] = dp[j] | dp[j - nums[i]];
        }
    }

    return dp[target];
}