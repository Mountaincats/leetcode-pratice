## 并查集
[TOC]

### 一、理论
并查集（Disjoint Set Union, DSU）是一种用于维护若干个**不相交集合**的数据结构，其核心操作是**合并集合**与**查找元素所属集合**。由于各集合相互独立，逻辑上可视为多棵“森林”。

- **应用场景**
  - **连通性判断**：判断图中两个点是否连通（如网络连通、社交关系）
  - **连通分量统计**：计算无向图中的连通块数量
  - **最小生成树（Kruskal算法）**：动态维护已选边的连通性，避免成环
  - **等价类划分**：处理具有传递性的等价关系（如“朋友的朋友是朋友”）

- **核心操作及时间复杂度**
    | 操作 | 说明 | 未优化时间复杂度 | 优化后均摊时间复杂度 |
    |------|------|-----------|------|
    | `add` | 将新元素作为独立集合加入 | $O(1)$ | $O(1)$ |
    | `find` | 查找元素所在集合的根节点（含路径压缩） | $O(n)$ | $O(\alpha(n))$ |
    | `union` | 将两个集合合并为一个 | $O(n)$ | $O(\alpha(n))$ |
    | `connected` | 判断两个元素是否属于同一集合 | $O(n)$ | $O(\alpha(n))$ |

    > **注**：$\alpha(n)$ 为阿克曼函数（Ackermann Function）的反函数，**增长极其缓慢**。在可观测的宇宙尺度数据量 $n$ 下，$\alpha(n) \le 5$，因此在实际应用中常视为 **$O(1)$**。

**1. 数据结构本质**
- 逻辑上：多棵**反向树**（孩子指向父节点），每棵树代表一个集合
- 物理上：通常使用**数组或哈希表**存储父子关系，`parent[x] = y` 表示 `x` 的父节点是 `y`
- **根节点特征**：根节点的父节点通常指向自己（或 `-1` / `NULL`），用于标识集合的唯一代表

**2. 两大核心优化**
- **路径压缩（Path Compression）**
  - **思想**：在 `find(x)` 过程中，将 `x` 到根路径上的所有节点直接挂载到根节点下，极大降低树高
  - **效果**：树高被压缩至接近常数（通常为 2），是并查集高效的核心原因
- **按秩合并（Union by Rank）**
  - **思想**：合并时，总是将**规模较小的树**挂到**规模较大的树**的根节点下，避免树退化成链表。
  - **秩（Rank）的两种定义**：
    1. **高度秩（Rank）**：记录以当前节点为根的树的**高度上界**（非精确高度）。路径压缩会改变实际树高，但为了保持高效的合并决策，压缩中**不更新**高度秩，允许其“虚高”。只要它能反映树高的上限，就能保证合并的正确性。
    2. **大小秩（Size）**：记录以当前节点为根的树的**节点总数**。该值不受路径压缩影响，始终保持精确，逻辑更直观，是工程实践中更推荐的方案。
  - **效果**：保证树高严格控制在 $O(\log n)$ 以内，配合路径压缩后实际为常数。

**3. 时间复杂度证明简述**
并查集的时间复杂度分析属于**均摊分析**(Amortized Analysis)范畴，即单次操作可能较慢，但连续多次操作的总开销可以被控制在一个很低的水平。

- **未经优化的朴素并查集：$O(n)$**
  - **成因**：如果不做任何优化，合并操作可能随意连接两棵树。最坏情况下，每次合并都将较深的树挂在较浅的树上，导致树退化成一条链表。
  - **后果**：执行 `find(x)` 时需要遍历整条链，单次查询的时间复杂度与节点数 $n$ 成正比。

- **仅使用路径压缩：$O(\log n)$**
  - **直观理解**：路径压缩虽然能把树压扁，但如果合并操作总是“胡乱”连接（比如总是把大树接到小树上），树高依然会增长。
  - **数学视角**：可以证明，仅靠路径压缩，树高会收敛到 $O(\log n)$。这意味着每次 `find` 操作需要向上追溯 $O(\log n)$ 步。这在工程上已经很快，但不是理论最优。

- **路径压缩 + 按秩合并：$O(\alpha(n))$（理论最优）**
  - **核心概念**：这里的 $\alpha(n)$ 是**阿克曼函数（Ackermann Function）$A(n, m)$ 的反函数**。
  - **增长特性**：$\alpha(n)$ 的增长速度**极其极其缓慢（Extremely Slow-Growing）**。它比 $\log n$、$\log \log n$ 都要慢得多。
    - 对于可以想象的任何规模的输入（例如宇宙中原子的总数 $n \approx 10^{80}$），都有 $\alpha(n) \le 5$。
  - **直观比喻**：按秩合并负责保证树的整体结构不会太畸形（控制宏观形态），路径压缩负责修剪内部的长枝条（优化微观细节）。两者结合，使得树的高度被压缩到了近乎常数的级别。
  - **结论**：在算法分析中，我们通常将 $O(\alpha(n))$ 视为**近似 $O(1)$**。这也是为什么并查集被称为拥有“近乎魔法般效率”的数据结构。

---

### 二、实现详解
> - 采用**数组**实现父子关系，根节点的父节点指向自身
> - 引入**按秩合并**，配合**路径压缩**，达到最优性能
> - 支持动态添加元素（若提前知道数据范围，可直接静态分配数组）
> - **实现方案选择**：下文将分别展示基于**高度秩**和**大小秩**的实现。

#### (1) 结构体定义
```c
#include <stdlib.h>

// 方案 A：基于高度秩 (Rank)
typedef struct {
    int* parent;   // 父节点数组
    int* rank;     // 秩数组（记录树高上界）
    int capacity;
} UnionFindRank;

// 方案 B：基于大小秩 (Size)
typedef struct {
    int* parent;   // 父节点数组
    int* size;     // 大小数组（记录集合元素总数）
    int capacity;
} UnionFindSize;
```

#### (2) 初始化
```c
// 初始化基于高度秩的并查集
UnionFindRank* ufInitRank(int n) {
    UnionFindRank* uf = (UnionFindRank*)malloc(sizeof(UnionFindRank));
    uf->capacity = n;
    uf->parent = (int*)malloc(sizeof(int) * n);
    uf->rank = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0; // 初始树高为 1，秩为 0
    }
    return uf;
}

// 初始化基于大小秩的并查集
UnionFindSize* ufInitSize(int n) {
    UnionFindSize* uf = (UnionFindSize*)malloc(sizeof(UnionFindSize));
    uf->capacity = n;
    uf->parent = (int*)malloc(sizeof(int) * n);
    uf->size = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->size[i] = 1; // 初始每个集合只有自己，大小为 1
    }
    return uf;
}
```

#### (3) 查找（find）
- 递归查找根节点，并在回溯时将路径上所有节点的父节点直接指向根节点
- 非递归版本可避免递归栈溢出，更适合工程实践
- 无论使用哪种秩的定义，`find` 函数的逻辑完全一致，且路径压缩过程**不修改**秩的值。
```c
// 查找 x 的根节点（递归版，带路径压缩）
int ufFind(UnionFindRank* uf, int x) {
    if (uf->parent[x] != x) {
        // 递归查找根节点，并将结果直接赋给父节点（路径压缩）
        uf->parent[x] = ufFind(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

// 查找 x 的根节点（迭代版，带路径压缩，推荐）
int ufFind(UnionFindRank* uf, int x) {
    int root = x;
    while (root != uf->parent[root]) {
        root = uf->parent[root];
    }
    // 路径压缩：将 x 到 root 路径上的所有节点直接挂载到 root 下
    while (x != root) {
        int next = uf->parent[x];
        uf->parent[x] = root;
        x = next;
    }
    return root;
}
```

#### (4) 合并（union）
- **两种方案区别**：
  - **高度秩**：只在两个根的秩相等时，才增加秩。
  - **大小秩**：合并后直接更新新根的集合大小（两树之和）。

```c
// 方案 A：基于高度秩的合并
void ufUnionByRank(UnionFindRank* uf, int x, int y) {
    int rootX = ufFind(uf, x);
    int rootY = ufFind(uf, rootY);
    if (rootX == rootY) return;

    // 按秩合并：小树挂到大树下
    if (uf->rank[rootX] < uf->rank[rootY]) {
        uf->parent[rootX] = rootY;
    } else if (uf->rank[rootX] > uf->rank[rootY]) {
        uf->parent[rootY] = rootX;
    } else {
        // 秩相等，任选一方作为根，秩加 1
        uf->parent[rootY] = rootX;
        uf->rank[rootX]++;
    }
}

// 方案 B：基于大小秩的合并（推荐）
void ufUnionBySize(UnionFindSize* uf, int x, int y) {
    int rootX = ufFind(uf, x);
    int rootY = ufFind(uf, y);
    if (rootX == rootY) return;

    // 按大小合并：小集合挂到大集合
    if (uf->size[rootX] < uf->size[rootY]) {
        uf->parent[rootX] = rootY;
        uf->size[rootY] += uf->size[rootX]; // 更新大小
    } else {
        uf->parent[rootY] = rootX;
        uf->size[rootX] += uf->size[rootY]; // 更新大小
    }
}
```

#### (5) 判断连通性
```c
// 判断 x 和 y 是否属于同一集合
int ufConnected(UnionFindRank* uf, int x, int y) {
    return ufFind(uf, x) == ufFind(uf, y);
}
```

#### (6) 动态添加元素
并查集的“动态添加”通常指**元素值无法在初始化时预知**的场景（例如在线流式数据）。根据元素的值域范围和分布密度，主要有以下三种实现方案：

| 特性 | 预分配（数组） | 倍增扩容（数组） | 哈希表（uthash） |
| :--- | :--- | :--- | :--- |
| **适用场景** | 值域小、已知 | 值域中等、连续 | 值域大、稀疏 |
| **添加复杂度** | **$O(1)$** | **$O(1)$ 均摊** | **$O(1)$** |
| **内存效率** | 低（可能浪费） | 中 | 高 |

**1. 预分配（静态数组）**
- **适用场景**：竞赛或工程中，已知元素取值范围（如 $[0, 10^6]$）。
- **原理**：初始化时直接分配最大可能容量的数组。
- **复杂度**：`add` 操作仅为数组赋值，**严格 $O(1)$**，无扩容开销。

**2. 倍增扩容（动态数组）**
- **适用场景**：无法预知元素上限，但值域相对连续，且内存敏感。
- **原理**：模仿 C++ `vector` 的扩容机制。当容量不足时，申请一块**两倍大小**的新内存，复制旧数据，再释放旧内存。
- **复杂度**：单次扩容为 $O(k)$（$k$ 为当前容量），但通过**均摊分析**，连续 $n$ 次操作的总复杂度为 $O(n)$，即**单次均摊 $O(1)$**。
- **注意**：切忌使用 `newCapacity = x + 1` 这种线性扩容，否则总复杂度会退化为 $O(n^2)$。

```c
// 倍增扩容实现（修正版）
void ufAddSize(UnionFindSize* uf, int x) {
    if (x < uf->capacity) return; // 空间已足够，直接返回

    // 计算新容量：取当前容量的2倍和 x+1 的较大值
    int newCapacity = uf->capacity << 1; // 等价于 uf->capacity * 2
    if (newCapacity <= x) {
        newCapacity = x + 1;
    }

    // 重新分配内存
    int* newParent = (int*)realloc(uf->parent, sizeof(int) * newCapacity);
    int* newSize = (int*)realloc(uf->size, sizeof(int) * newCapacity);
    
    // 内存分配失败处理（工程必备）
    if (!newParent || !newSize) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(newParent);
        free(newSize);
        // 根据实际需求决定是退出还是回滚
        exit(EXIT_FAILURE);
    }
    uf->parent = newParent;
    uf->size = newSize;

    // 初始化新增的槽位
    for (int i = uf->capacity; i < newCapacity; i++) {
        uf->parent[i] = i;
        uf->size[i] = 1;
    }
    uf->capacity = newCapacity;
}
```

**3. 哈希表映射（uthash）**
- **适用场景**：元素值域极大（如 $10^9$）或分布极度稀疏（如 UUID）。
- **原理**：使用哈希表（`uthash`）存储父子关系，而非连续数组。
- **复杂度**：插入和查找均为 **$O(1)$**，无需扩容，但常数开销略大于数组。
- **优势**：彻底解决内存浪费和扩容复制问题，是处理超大数据集的理想选择。

```c
#include "uthash.h"

typedef struct {
    int id;         // Key: 元素值
    int parent;     // Value: 父节点
    int size;       // Value: 集合大小
    UT_hash_handle hh;
} UFNode;

UFNode* ufHash = NULL; // 哈希表头

// 查找（带路径压缩）
int ufHashFind(int x) {
    UFNode* node;
    HASH_FIND_INT(ufHash, &x, node);
    if (!node) return x; // 未找到，视为独立集合（父节点指向自己）

    if (node->parent != x) {
        node->parent = ufHashFind(node->parent);
    }
    return node->parent;
}

// 动态添加（严格 O(1)）
void ufHashAdd(int x) {
    UFNode* node;
    HASH_FIND_INT(ufHash, &x, node);
    if (node) return; // 已存在

    node = (UFNode*)malloc(sizeof(UFNode));
    node->id = x;
    node->parent = x;
    node->size = 1;
    HASH_ADD_INT(ufHash, id, node);
}

// 合并（按大小合并）
void ufHashUnion(int x, int y) {
    int rootX = ufHashFind(x);
    int rootY = ufHashFind(y);
    if (rootX == rootY) return;

    UFNode* nodeX;
    UFNode* nodeY;
    HASH_FIND_INT(ufHash, &rootX, nodeX);
    HASH_FIND_INT(ufHash, &rootY, nodeY);

    // 确保 nodeX 是大集合
    if (nodeX->size < nodeY->size) {
        UFNode* temp = nodeX;
        nodeX = nodeY;
        nodeY = temp;
    }

    nodeY->parent = nodeX->id;
    nodeX->size += nodeY->size;
}
```

#### (7) 资源释放
```c
void ufFreeRank(UnionFindRank* uf) {
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

void ufFreeSize(UnionFindSize* uf) {
    free(uf->parent);
    free(uf->size);
    free(uf);
}
```

#### (8) 使用示例
```c
#include <stdio.h>

int main() {
    // 推荐使用基于大小秩的并查集
    UnionFindSize* uf = ufInitSize(10);
    
    ufUnionBySize(uf, 1, 2);
    ufUnionBySize(uf, 3, 4);
    ufUnionBySize(uf, 1, 3);
    
    printf("1 and 4 connected? %s\n", ufConnected((UnionFindRank*)uf, 1, 4) ? "Yes" : "No");
    printf("Size of set containing 1: %d\n", uf->size[ufFind((UnionFindRank*)uf, 1)]); // 应为 4

    ufFreeSize(uf);
    return 0;
}
```

---

### 三、进阶技巧
**1. 维护附加信息**
- 除了父子关系，可以在并查集中维护集合的附加属性，如：
  - **集合大小**：如上所述，使用 `size` 数组。
  - **集合最值**：合并时更新 `min[root]` / `max[root]`。
  - **边的数量**：用于判断是否存在环（Kruskal 算法）。
- 实现方式：增加对应数组，在 `union` 操作中同步更新。

**2. 无法删除元素的应对**
- 标准并查集不支持删除单个元素（会破坏树结构）。
- 解决方案：
  - **重建法**：定期重建整个并查集。
  - **延迟删除**：标记元素为无效，不物理删除。
  - **时间戳/版本控制**：为每个操作打时间戳，查询时忽略过期信息。

**3. 典型题目模式**
- **连通块计数**：初始化 `count = n`，每次有效 `union` 后 `count--`。
- **最小生成树**：对所有边排序，依次尝试合并两端点，成功则累加权重。
- **等式方程的可满足性**：先合并所有等号关系，再检查不等号是否冲突。
