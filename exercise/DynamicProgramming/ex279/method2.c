#define min(a, b) ((a) < (b) ? (a) : (b))

int numSquares(int n) {
    int f[n + 1];
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        int min_n = INT_MAX;
        for (int j = 1; j * j <= i; j++) {
            min_n = min(min_n, f[i - j * j]);
        }
        f[i] = min_n + 1;
    }

    return f[n];
}