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

    for (int i = bSize - 1; i >= 0; i--) {
        res = (long)res * modpow(a, b[i]) % MOD;
        a = modpow(a, 10);
    }

    return res;
}