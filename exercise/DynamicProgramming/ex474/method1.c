#define max(a, b) ((a) > (b) ? (a) : (b))

void getZerosOnes(int* ZerosOnes, char* str) {
    int lentth = strlen(str);
    for (int i = 0; i < lentth; i++) {
        ZerosOnes[str[i] - '0']++;
    }
}

int findMaxForm(char** strs, int strsSize, int m, int n) {
    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < strsSize; i++) {
        int ZerosOnes[2];
        memset(ZerosOnes, 0, sizeof(ZerosOnes));
        getZerosOnes(ZerosOnes, strs[i]);
        int zeros = ZerosOnes[0], ones = ZerosOnes[1];
        for (int j = m; j >= zeros; j--) {
            for (int k = n; k >= ones; k--) {
                dp[j][k] = max(dp[j][k], dp[j - zeros][k - ones] + 1);
            }
        }
    }

    return dp[m][n];
}