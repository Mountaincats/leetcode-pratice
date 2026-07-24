## 其它算法
[TOC]

### 一、摩尔投票法
给定一个大小为 **$n$** 的整数数组，找出其中所有出现超过 **$\lfloor n / m \rfloor, \; (m \ge 2, \; m \in Z)$** 次的元素。

---

### 二、快速幂
**1. 朴素连乘**
快速幂的本质是将**指数 $n$ 拆解为二进制**，从而将 **$O(n)$** 次的乘法降低到 **$O(\log n)$** 次。

以计算 **$a^n$** 为例：
- 朴素算法：乘 **$n$** 次，**$O(n)$**
- 快速幂：利用 **$n$** 的二进制表示，只算 **$\lfloor \log_2 n \rfloor + 1$** 次，时间复杂度为 **$O(\log n)$**

> 任何一个整数 $n$ 都可以表示为二进制：
> **$$n = b_k \cdot 2^k + b_{k-1} \cdot 2^{k-1} + \cdots + b_1 \cdot 2^1 + b_0 \cdot 2^0$$**
> 
> 因此：
> **$$a^n = a^{b_k \cdot 2^k} \cdot a^{b_{k-1} \cdot 2^{k-1}} \cdots a^{b_0 \cdot 2^0}$$**
> 
> 其中 **$b_i \in \{0, 1\}$**，只有当 **$b_i = 1$** 时才需要将该项乘入结果。

```c
long long pow_fast(long long a, int n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) {          // n 是奇数
            res *= a;
        }
        a *= a;               // 底数平方
        n >>= 1;              // n 除以 2
    }
    return res;
}

// 防止溢出的版本，调用示例如下
// pow_mod(2, 1000000000, MOD);
#define MOD 1000000007
long long pow_mod(long long a, int n, long long mod) {
    long long res = 1 % mod;
    a %= mod;
    while (n > 0) {
        if (n & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}
```

**2. 矩阵快速幂**
如果一个问题可以转化为求解一个 **$m$** 阶矩阵的 **$n$** 次方的形式，那么可以用快速幂来加速计算。
> 一次矩阵乘法的时间复杂度为 **$O(m^3)$**，矩阵乘法的次数为 **$O(\log n)$**。
> 故矩阵快速幂的时间复杂度为 **$O(m^3 \log n)$**， 空间复杂度为 **$O(1)$**。
```c
typedef struct Matrix {
    int n; // 方阵阶数
    long long **mat;
} Matrix;

/* 创建矩阵 */
Matrix createMatrix(int n) {
    Matrix a;
    a.n = n;
    a.mat = (long long **)malloc(n * sizeof(long long *));
    for (int i = 0; i < n; i++) {
        a.mat[i] = (long long *)calloc(n, sizeof(long long));
    }
    return a;
}

/* 矩阵乘法 */
Matrix multiply(Matrix a, Matrix b) {
    Matrix c = createMatrix(a.n);
    for (int i = 0; i < a.n; i++) {
        for (int k = 0; k < a.n; k++) {          // 这里交换 j,k 顺序可小幅优化缓存
            if (a.mat[i][k] == 0) continue;      // 稀疏优化（可选）
            for (int j = 0; j < a.n; j++) {
                c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return c;
}

/* 矩阵快速幂 */
Matrix matrixPow(Matrix a, int n) {
    // 初始化为单位矩阵
    Matrix ret = createMatrix(a.n);
    for (int i = 0; i < a.n; i++) {
        ret.mat[i][i] = 1;
    }

    while (n > 0) {
        if (n & 1) {
            ret = multiply(ret, a);
        }
        a = multiply(a, a);
        n >>= 1;
    }
    return ret;
}
```
> - **齐次线性递推**
对于形如 **$f(n)=\sum_{i=1}^{m} a_i f(n-i)$** 的**齐次线性递推式**，可以将其转化为矩阵形式，从而利用矩阵快速幂高效求解。
> 
>   构造 **$m \times m$** 的状态转移矩阵如下：
> 
>   $$
    \begin{bmatrix}
    a_1 & a_2 & a_3 & \cdots & a_m \\
    1   & 0   & 0   & \cdots & 0   \\
    0   & 1   & 0   & \cdots & 0   \\
    \vdots & \vdots & \ddots & \ddots & \vdots \\
    0   & 0   & \cdots & 1   & 0
    \end{bmatrix}
    $$
> 
>   该矩阵满足：
> 
>   $$
    \begin{bmatrix}
    f(n) \\
    f(n-1) \\
    \vdots \\
    f(n-m+1)
    \end{bmatrix}
    =
    \begin{bmatrix}
    a_1 & a_2 & \cdots & a_m \\
    1   & 0   & \cdots & 0   \\
    \vdots & \vdots & \ddots & \vdots \\
    0   & 0   & \cdots & 0
    \end{bmatrix}
    \begin{bmatrix}
    f(n-1) \\
    f(n-2) \\
    \vdots \\
    f(n-m)
    \end{bmatrix}
    $$
> 
> - **非齐次线性递推**
>   非齐次线性递推在某些情况下，可以通过**变量替换**将其转化为齐次形式。
>   考虑递推式：
>   **$$f(x) = (2x - 6)c + f(x-1) + f(x-2) + f(x-3)$$**
> 
>   观察发现其非齐次项 **$(2x - 6)c$** 含有关于 **$x$** 的一次项。进行如下变换：
> 
>   $$
    \begin{aligned}
    f(x) + xc &= f(x-1) + f(x-2) + f(x-3) + (2x - 6)c + xc \\
    &= [f(x-1) + (x-1)c] + [f(x-2) + (x-2)c] + [f(x-3) + (x-3)c]
    \end{aligned}
    $$
> 
>   令 $g(x) = f(x) + xc$，则原递推式转化为**齐次线性递推**：
>   $$g(x) = g(x-1) + g(x-2) + g(x-3)$$
> 
>   此时即可构造相应的转移矩阵，使用矩阵快速幂进行求解。
