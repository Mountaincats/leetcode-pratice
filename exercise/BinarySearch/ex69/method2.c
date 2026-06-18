int mySqrt(int x) {
    int l = 0, r = x;
    while (l <= r) {
        int mid = (l + r) / 2;
        if ((long long)mid * mid <= x) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return l - 1;
}