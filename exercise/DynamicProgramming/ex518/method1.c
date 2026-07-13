int change(int amount, int* coins, int coinsSize) {
    unsigned long long int dp[amount + 1];
    dp[0] = 1;
    for(int j = 1; j < amount + 1; j++){
        dp[j] = 0;
    }
    for(int i = 0; i < coinsSize; i++){
        for(int j = coins[i]; j < amount + 1; j++){
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[amount];
}