## 动态规划（Dynamic Programming, DP）
[TOC]

### 一、理论
动态规划是一种通过将复杂问题分解为重叠子问题，并存储子问题的解来避免重复计算，从而求解最优化问题的算法范式。它既是“递归”思想的延伸，也是“空间换时间”的典型应用。

**1. 问题特性**
- **重叠子问题**
- **最优子结构**：问题的最优解可以由其子问题的最优解有效地构造出来。
- **无后效性**：给定一个确定的状态，它的未来发展只与当前状态有关，而与过去经历的所有状态无关。

**2. 三要素**
- **状态定义（Definition）**：数组 dp 也称为 dp 表
- **状态转移方程（Transition）**
- **边界条件（Initialization）**

**3. 实现方式**
- **自顶向下（Top-Down）**：常用记忆化递归实现，代码直观，符合思维习惯，但可能有递归栈溢出的风险。
- **自底向上（Bottom-Up）**：效率更高，无栈溢出风险，是竞赛和工程的首选。

**4. 重要操作**
- **滚动变量 / 滚动数组**：一种空间优化技巧。
- **状态压缩**：用 1 位二进制位表示一个状态，优化空间复杂度、提高状态数据的处理并行度和提高缓存利用率。
- **遍历顺序**：在二维 DP 中，正序或倒序遍历会影响后续计算的正确性。

---

### 二、模型
动态规划的核心是将问题抽象为**状态定义 + 转移方程 + 边界条件**的数学模型，根据状态的维度和决策模型，主要分为以下几类经典模型。

#### (1) 线性 DP（Linear DP）
**问题特征**：状态转移沿着线性顺序（如数组下标）进行。
**典型案例**：最长递增子序列（LIS）、最长公共子序列（LCS）、最大子数组和。

**1. 最长递增子序列（LIS）**
- **定义**：`dp[i]` 表示以 `nums[i]` 结尾的最长递增子序列的长度。
- **转移**：`dp[i] = max(dp[j] + 1)`，其中 `0 <= j < i` 且 `nums[j] < nums[i]`。
- **复杂度**：$O(n^2)$。

```c
#include <stdio.h>

// 返回最长递增子序列的长度
int lengthOfLIS(int* nums, int n) {
    if (n == 0) return 0;
    int dp[n];
    int ans = 1;
    
    // 1. 初始化：每个元素至少可以单独成为一个子序列
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    
    // 2. 状态转移
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > ans) ans = dp[i];
    }
    return ans;
}
```

**2. 最大子数组和（Kadane算法）**
- **定义**：`dp[i]` 表示以 `nums[i]` 结尾的最大子数组和。
- **转移**：`dp[i] = max(nums[i], dp[i-1] + nums[i])`。
- **优化**：由于 `dp[i]` 只依赖 `dp[i-1]`，可以使用变量代替数组，空间复杂度优化为 $O(1)$。

```c
int maxSubArray(int* nums, int n) {
    int curr_sum = nums[0];
    int max_sum = nums[0];
    for (int i = 1; i < n; i++) {
        // 状态转移：延续之前的子数组 or 从当前元素重新开始
        curr_sum = (curr_sum + nums[i] > nums[i]) ? curr_sum + nums[i] : nums[i];
        if (curr_sum > max_sum) {
            max_sum = curr_sum;
        }
    }
    return max_sum;
}
```

#### (2) 背包问题（Knapsack Problem）
**问题特征**：给定容量和一堆物品（重量、价值），求最大价值。
**核心逻辑**：遍历物品时，容量必须从大到小遍历（为了保证 `dp[j-w]` 是上一轮物品的结果，而不是本轮已更新的结果）。

**1. 0-1 背包（每个物品选或不选）**
- **定义**：`dp[j]` 表示容量为 `j` 的背包能获得的最大价值。
- **转移**：`dp[j] = max(dp[j], dp[j - weight[i]] + value[i])`。

```c
#include <string.h>

#define MAXC 1000

// 0-1 Knapsack
int knapsack01(int* weights, int* values, int n, int capacity) {
    int dp[MAXC] = {0}; // 初始化为0
    
    // 遍历物品
    for (int i = 0; i < n; i++) {
        // 遍历容量（必须倒序！）
        for (int j = capacity; j >= weights[i]; j--) {
            // 不选 dp[j] vs 选 dp[j-weight[i]] + value[i]
            if (dp[j - weights[i]] + values[i] > dp[j]) {
                dp[j] = dp[j - weights[i]] + values[i];
            }
        }
    }
    return dp[capacity];
}
```

**2. 完全背包（每个物品无限次）**
- **区别**：容量遍历顺序改为**正序**。因为物品可以重复选，所以 `dp[j-weight]` 可以是本轮已经更新过的值（即已经选过一次该物品）。
- **转移**：`dp[j] = max(dp[j], dp[j - weight[i]] + value[i])`。（代码同0-1背包，仅循环顺序不同）

```c
// Complete Knapsack
int knapsackComplete(int* weights, int* values, int n, int capacity) {
    int dp[MAXC] = {0};
    
    for (int i = 0; i < n; i++) {
        // 遍历容量（正序！允许重复使用物品）
        for (int j = weights[i]; j <= capacity; j++) {
            if (dp[j - weights[i]] + values[i] > dp[j]) {
                dp[j] = dp[j - weights[i]] + values[i];
            }
        }
    }
    return dp[capacity];
}
```

#### (3) 区间 DP（Interval DP）
**问题特征**：状态由两个端点 `l` 和 `r` 定义，通过合并小区间得到大区间的解。
**典型案例**：石子合并、戳气球、最长回文子串。
**套路**：枚举区间长度 `len`，枚举左端点 `l`，计算右端点 `r`，最后枚举分割点 `k`。

```c
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INF 0x3f3f3f3f

// 石子合并问题
// dp[i][j] 表示合并 i 到 j 堆石子的最小代价
int mergeStones(int* stones, int n) {
    // 前缀和，用于快速计算区间和
    int prefixSum[n + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + stones[i];
    }

    int dp[n][n];
    // 初始化：长度为1的区间代价为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
        dp[i][i] = 0;
    }

    // 枚举区间长度
    for (int len = 2; len <= n; len++) {
        // 枚举左端点
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1; // 右端点
            // 枚举分割点
            for (int k = i; k < j; k++) {
                // 合并左边和右边，加上本次合并的代价（区间总和）
                dp[i][j] = MIN(dp[i][j], dp[i][k] + dp[k+1][j] + prefixSum[j+1] - prefixSum[i]);
            }
        }
    }
    return dp[0][n-1];
}
```

#### (4) 树形 DP（Tree DP）
**问题特征**：在树的结构上进行递归 DP。通常后序遍历（先算子树，再算根节点）。
**典型案例**：二叉树中的最大路径和、打家劫舍 III（不能偷相邻的节点）。

```c
// 打家劫舍 III (House Robber III)
// 返回数组 [不偷当前节点的最大值, 偷当前节点的最大值]
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void dfs(TreeNode* root, int* rob, int* not_rob) {
    if (!root) {
        *rob = 0;
        *not_rob = 0;
        return;
    }
    
    int left_rob, left_not_rob;
    int right_rob, right_not_rob;
    
    dfs(root->left, &left_rob, &left_not_rob);
    dfs(root->right, &right_rob, &right_not_rob);
    
    // 偷当前节点：左右孩子都不能偷
    *rob = root->val + left_not_rob + right_not_rob;
    // 不偷当前节点：左右孩子可选择偷或不偷，取最大值
    *not_rob = (left_rob > left_not_rob ? left_rob : left_not_rob) +
               (right_rob > right_not_rob ? right_rob : right_not_rob);
}

int rob(TreeNode* root) {
    int rob_root, not_rob_root;
    dfs(root, &rob_root, &not_rob_root);
    return rob_root > not_rob_root ? rob_root : not_rob_root;
}
```

#### (5) 状态压缩 DP（Bitmask DP）
**问题特征**：当状态集合很小（如 n <= 20）时，用一个整数的二进制位来表示集合的状态。
**典型案例**：旅行商问题（TSP）、棋盘放置问题。

```c
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INF 0x3f3f3f3f

// 旅行商问题 (TSP)
// dp[S][i]: 当前访问过的城市集合为 S，当前位于城市 i 的最短路径
int tsp(int dist[][4], int n) {
    int size = 1 << n; // 状态总数 2^n
    int dp[size][n];
    
    // 初始化：从 0 出发
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[1][0] = 0; // 初始状态：只访问了城市0 (二进制 0001)，花费为0

    // 遍历所有状态
    for (int S = 1; S < size; S++) {
        for (int i = 0; i < n; i++) {
            if (dp[S][i] == INF) continue;
            // 尝试从 i 走到 j
            for (int j = 0; j < n; j++) {
                // 如果 j 还没有被访问过
                if (!(S & (1 << j))) {
                    int newS = S | (1 << j); // 将 j 加入集合
                    dp[newS][j] = MIN(dp[newS][j], dp[S][i] + dist[i][j]);
                }
            }
        }
    }
    
    // 计算回到起点的距离
    int ans = INF;
    int finalS = size - 1; // 所有城市都访问过了
    for (int i = 0; i < n; i++) {
        ans = MIN(ans, dp[finalS][i] + dist[i][0]);
    }
    return ans;
}
```
