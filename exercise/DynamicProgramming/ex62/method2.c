int uniquePaths(int m, int n) {
    if (m > n) {
        m = m ^ n;
        n = m ^ n;
        m = m ^ n;
    }

    long long res = 1;
    for (int x = n, y = 1; y < m; x++, y++) {
        res = res * x / y;
    }

    return res;
}