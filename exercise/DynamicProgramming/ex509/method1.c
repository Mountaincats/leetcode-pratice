struct matrix {
    long long mat[2][2];
};

struct matrix multiply(struct matrix a, struct matrix b) {
    struct matrix c;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c.mat[i][j] = a.mat[i][0] * b.mat[0][j] + a.mat[i][1] * b.mat[1][j];
        }
    }

    return c;
}

struct matrix matricPow(struct matrix a, int n) {
    struct matrix ret;
    ret.mat[0][0] = ret.mat[1][1] = 1;
    ret.mat[0][1] = ret.mat[1][0] = 0;

    while (n > 0) {
        if (n & 1) ret = multiply(a, ret);
        n >>= 1;
        a = multiply(a, a);
    }

    return ret;
}

int fib(int n) {
    struct matrix ret;
    ret.mat[0][0] = ret.mat[0][1] = ret.mat[1][0] = 1;
    ret.mat[1][1] = 0;
    ret = matricPow(ret, n);

    return ret.mat[1][0];
}