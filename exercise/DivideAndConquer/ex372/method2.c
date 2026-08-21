#define MOD 1337

int modpow(int x, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (long)res * x % MOD;
        }
        x = (long)x * x % MOD;
        n >>= 1;
    }

    return res;
}

int superPow(int a, int* b, int bSize) {
    int res = 1;

    for (int i = 0; i < bSize; i++) {
        res = (long)modpow(res, 10) * modpow(a, b[i]) % MOD;
    }

    return res;
}