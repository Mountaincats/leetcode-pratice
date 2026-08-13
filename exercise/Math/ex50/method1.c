double myPow(double x, int n) {
    if (x == 0) return 0;

    long i = n;
    if (i < 0) {
        x = 1 / x;
        i = -i;
    }

    double ans = 1.0;
    while (i > 0) {
        if (i & 1) {
            ans *= x;
        }
        x *= x;
        i >>= 1;
    }

    return ans;
}