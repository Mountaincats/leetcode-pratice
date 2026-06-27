## 算法主定理（Master Theorem）
主定理用于**求解分治递归式**，专门分析形如 $T(n)$ 的时间复杂度，是算法复杂度分析的核心工具。
[TOC]

---

### 一、定理内容
分治算法通用递归公式：
$$
T(n) = a\,T\left(\frac{n}{b}\right) + f(n)
$$
参数说明：
- $n$：问题规模
- $a \ge 1$：**子问题个数**
- $b > 1$：原问题划分为子问题的**划分比例**（每个子问题规模 $n/b$）
- $f(n)$：**分解+合并**子问题的时间开销

---

### 二、关键判定值
先计算**递归树每层总工作量的临界指数**：
$$
\log_b a
$$
再比较 $f(n)$ 与 $n^{\log_b a}$ 的**渐近阶**，分三种情况。

---

### 三、三大情况
> 记号：$\varepsilon>0$ 为任意小常数。

**1. $f(n) = O\left(n^{\log_b a - \varepsilon}\right)$**
**合并开销 < 递归开销**
结果：
$$
\boldsymbol{T(n) = \Theta\left(n^{\log_b a}\right)}
$$

**2. $f(n) = \Theta\left(n^{\log_b a}\cdot \log^k n\right) \quad (k\ge 0)$**
**合并开销 ≈ 递归开销**
结果：
$$
\boldsymbol{T(n) = \Theta\left(n^{\log_b a}\cdot \log^{k+1} n\right)}
$$
最常用特例：$k=0$ 时
$$T(n) = \Theta\left(n^{\log_b a}\log n\right)$$

**3. $f(n) = \Omega\left(n^{\log_b a + \varepsilon}\right)$**
**合并开销 > 递归开销**
**附加正则条件**：存在常数 $c<1$、足够大的 $n$，满足
$$a\cdot f\left(\frac{n}{b}\right) \le c\cdot f(n)$$
满足则结果：
$$
\boldsymbol{T(n) = \Theta\big(f(n)\big)}
$$

---

### 四、例题
**例1 二分查找**
$$T(n) = T\left(\frac{n}{2}\right) + O(1)$$
$a=1,\ b=2,\ \log_2 1 = 0$
$f(n)=O(1)=\Theta(n^0)$，属于**情况2，k=0**
$$T(n) = \boldsymbol{\Theta(\log n)}$$

**例2 归并排序**
$$T(n) = 2T\left(\frac{n}{2}\right) + O(n)$$
$a=2,\ b=2,\ \log_2 2 = 1$
$f(n)=O(n)=\Theta(n^1)$，属于**情况2，k=0**
$$T(n) = \boldsymbol{\Theta(n\log n)}$$

**例3**
$$T(n) = 9T\left(\frac{n}{3}\right) + n$$
$a=9,\ b=3,\ \log_3 9 = 2$
$f(n)=n = O(n^{2-\varepsilon})$，属于**情况1**
$$T(n) = \boldsymbol{\Theta(n^2)}$$

**例4**
$$T(n) = 3T\left(\frac{n}{4}\right) + n\log n$$
$a=3,\ b=4,\ \log_4 3 \approx 0.792$
$f(n)=n\log n = \Omega(n^{0.792+\varepsilon})$，满足正则条件，**情况3**
$$T(n) = \boldsymbol{\Theta(n\log n)}$$

---

### 五、不适用场景
出现以下形式**不能直接用主定理**，需用递归树/代入法求解：
- 递归式不是 $T(n)=aT(n/b)+f(n)$ 标准形式（如 $T(n)=2T(n-1)+n$）
- $f(n)$ 与 $n^{\log_b a}$ 处于**多项式间隙之间**
- 情况3不满足**正则条件**
