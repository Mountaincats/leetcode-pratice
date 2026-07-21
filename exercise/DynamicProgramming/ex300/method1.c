#define max(a, b) ((a) > (b) ? (a) : (b))

int lengthOfLIS(int* nums, int numsSize) {
    int dp[numsSize];
    dp[0] = 1;

    int len = dp[0];

    for (int i = 1; i < numsSize; i++) {
        int sub_max = 0;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) sub_max = max(sub_max, dp[j]);
        }
        dp[i] = sub_max + 1;
        len = max(len, dp[i]);
    }

    return len;
}