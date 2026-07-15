#define min(a, b) ((a) < (b) ? (a) : (b))

int coinChange(int* coins, int coinsSize, int amount) {
    int max = amount + 1;
    int dp[max];
    dp[0] = 0;

    for (int i = 1; i < max; i++) {
        dp[i] = max;
    }

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coinsSize; j++) {
            if (coins[j] <= i) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}