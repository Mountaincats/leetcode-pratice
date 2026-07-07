int climbStairs(int n) {
    int p = 1, q = 1;
    for (int i = 1; i < n; i++) {
        p = p + q;
        p = p ^ q;
        q = p ^ q;
        p = p ^ q;
    }
    return q;
}