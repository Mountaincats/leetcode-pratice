char* longestPalindrome(char* s) {
    int n = strlen(s);
    if(n < 2) return s;

    int maxlen = 1;
    int begin = 0;

    bool dp[n][n];
    for(int i = 0; i < n; i++){
        dp[i][i] = true;
    }

    for(int L = 2; L <= n; L++) {
        for(int i = 0; i < n; i++) {
            int j = L + i - 1;
            if(j >= n) break;

            if(s[i] != s[j]) {
                dp[i][j] = false;
            } else {
                if(j - i < 3) {
                    dp[i][j] = true;
                } else {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            }

            if(dp[i][j] && j - i + 1 > maxlen) {
                maxlen = j - i + 1;
                begin = i;
            }
        }
    }

    char* result = (char*)malloc((maxlen + 1) * sizeof(char));
    
    if (result == NULL) {
        return NULL;
    }
    
    strncpy(result, s + begin, maxlen);
    result[maxlen] = '\0';
    
    return result;
}