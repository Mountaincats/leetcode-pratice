## 堆
[TOC]

### 一、理论
**1. 基本定义**
- 堆是一种**完全二叉树**数据结构，通常用**数组**实现，其索引往往从 1 开始，称为`1-based indexing`，但也可以从 0 开始，称为`0-based indexing`。
  - 从 1 开始索引的数学表示更简单，但也会浪费一个元素的存储空间
  - 两种索引方式**没有性能差距**

- 根据节点与其子节点的关系，分为两种类型：
    | 类型 | 性质 |
    |------|------|
    | **大顶堆** | 任意节点 $\ge$ 其子节点，堆顶为最大值 |
    | **小顶堆** | 任意节点 $\le$ 其子节点，堆顶为最小值 |

**2. 数组表示**
- 索引从 1 开始的堆数组 `heap[]`：
  - 父节点：`parent = child / 2`
  - 左子节点：`left = parent * 2`
  - 右子节点：`right = parent * 2 + 1`
- 索引从 0 开始的堆数组 `heap[]`：
  - 父节点：`parent = (child - 1) / 2`
  - 左子节点：`left = parent * 2 + 1`
  - 右子节点：`right = parent * 2 + 2`

**3. 核心操作及时间复杂度**
| 操作 | 说明 | 时间复杂度 |
|------|------|-----------|
| `push`（插入） | 将新元素插入堆尾，再向上调整（`sift-up`） | $O(\log n)$ |
| `pop`（删除堆顶） | 堆顶与堆尾交换，删除堆尾，再从堆顶向下调整（`sift-down`） | $O(\log n)$ |
| `top`（取堆顶） | 直接访问堆顶元素 | $O(1)$ |
| **建堆** | 将无序数组原地调整为堆 | $O(n)$ |

> **注意**：建堆复杂度 $O(n)$ 而非 $O(n \log n)$，因为底层节点少、调整层数少，逐层累加后总复杂度为线性级别。
> 
> **a. 建堆的两种方式**
> - **Floyd 算法（自底向上建堆）**：从最后一个非叶子节点开始向前遍历，对每个节点执行 `sift-down`。这是标准建堆方式，复杂度 **$O(n)$**
> - **逐个插入建堆**：从空堆开始，对数组每个元素调用 `push`。复杂度 **$O(n\log n)$**，不推荐
> 
> **b. Floyd 算法复杂度 $O(n)$ 的证明**
> - 堆是**完全二叉树**和堆是**满二叉树**的分析结果是一致的，所以可以**假设堆是满二叉树**。高度 $H = \lfloor \log_2 n \rfloor$。设叶子层为第 $h$ 层，第 $h$ 层节点数最多为 $2^h$，该层节点向下调整最多 $H - h$ 层
> - 总比较次数上界：
>   $$
>   \begin{aligned}
>   T(n) &\le \sum_{h=0}^{H} 2^h \cdot (H - h) = 2^H \sum_{k=0}^{H} \frac{k}{2^k} < 2^H \cdot 2 < 2n
>   \end{aligned}
>   $$
>   其中 $\sum_{k=0}^{\infty} \frac{k}{2^k} = 2$ 为已知收敛级数
> - 直观理解：叶子节点约占总节点数一半，调整层数为 $0$；倒数第二层约占 $1/4$，调整层数为 $1$……高层节点调整层数多但数量指数级减少，两者相乘后被常数倍 $n$ 控制
> 
> **c. 逐个插入建堆算法复杂度 $O(n \log n)$ 的证明**
> 逐个插入模拟的是一个**动态过程**：假设堆里已经有 $k$ 个元素了，现在要把第 $k+1$ 个元素插进去。
> - **最坏情况**：每次插入的新元素，都有可能一路“冒泡”到堆顶。
> - **代价计算**：
>     - 插入第 1 个元素：堆大小为 1，调整 $O(0)$ 次（不用动）。
>     - 插入第 2 个元素：堆大小为 2，最坏调整 $O(1)$ 次。
>     - 插入第 3、4 个元素：堆大小为 3 或 4，最坏调整 $O(\log 3)$ 或 $O(\log 4)$ 次。
>     - ...
>     - **插入第 $n$ 个元素**：此时堆的大小已经是 $n-1$ 了，这个新元素最坏可能需要调整 $O(\log n)$ 次才能到达合适的位置。
> - 把每次插入的最坏调整次数累加起来：
$$T(n) = \log 1 + \log 2 + \log 3 + ... + \log n$$
这其实就是：
$$T(n) = \sum_{k=1}^{n} \log k = \log (n!)$$
> 根据斯特林公式（Stirling's approximation），$n!$ 约等于 $(n/e)^n$，所以：
> $$\log(n!) \approx n \log n - n$$
> 这就得到了 **$O(n \log n)$** 的复杂度。

**4. 常见应用**
- **优先队列**：动态获取最大/最小元素
- **Top-K 问题**：维护大小为 K 的堆
- **堆排序**：升序用小顶堆，降序用大顶堆
- **Dijkstra / Prim 等图算法**：高效取最小权值边

---

### 二、实现详解
> - 通过**比较函数指针**统一实现大顶堆和小顶堆，只需修改 `cmp` 函数即可切换堆类型
> - 索引从 1 开始，父子节点计算更直观

#### (1) 结构体与比较函数
**1. 比较函数的设计逻辑**
- `cmp(a, b)` 返回 `true` 表示 **a 比 b 更接近堆顶**（a 优先级更高）
  - `push` 中：若子节点比父节点优先级更高，则交换（上浮）
  - `pop` 中：选择两个子节点中优先级更高的与父节点比较，若子节点优先级更高则交换（下沉）
```c
struct Heap {
    int* heap;         // 堆数组，索引从 1 开始
    int heapSize;      // 当前堆中元素个数
    bool (*cmp)(int, int);  // 比较函数指针，决定堆类型
};

// cmp 返回 true 表示 a 优先级更高（应上浮）
// 小顶堆：父节点 <= 子节点
bool cmpMin(int a, int b) { return a < b; }

// 大顶堆：父节点 >= 子节点
bool cmpMax(int a, int b) { return a > b; }
```



#### (2) 初始化
```c
void init(struct Heap* obj, int n, bool (*cmp)(int, int)) {
    // 分配 n+1 空间，索引 0 不使用
    obj->heap = malloc(sizeof(int) * (n + 1));
    obj->heapSize = 0;
    obj->cmp = cmp;
}
```

#### (3) 插入（push）
- 新元素放入堆尾（`heapSize + 1` 位置）
- 不断与父节点比较，若优先级更高则交换
- 直到到达堆顶（`parent == 0`）或堆性质恢复
```c
void push(struct Heap* obj, int val) {
    int child = ++(obj->heapSize), parent = child >> 1;
    obj->heap[child] = val;
    // 向上调整（sift-up）
    while (parent) {
        if (obj->cmp(obj->heap[child], obj->heap[parent])) {
            swap(&(obj->heap[child]), &(obj->heap[parent]));
            child = parent;
            parent = child >> 1;
        } else {
            break;  // 堆性质已满足，停止上浮
        }
    }
}
```

#### (4) 删除堆顶（pop）
- 堆顶元素用堆尾元素替换
- 从堆顶开始，与优先级最高的子节点比较并交换
- 直到没有子节点或堆性质恢复
```c
void pop(struct Heap* obj) {
    // 堆顶用堆尾替换
    obj->heap[1] = obj->heap[(obj->heapSize)--];
    int parent = 1, child = parent << 1;
    // 向下调整（sift-down）
    while (child <= obj->heapSize) {
        // 选择两个子节点中优先级更高的
        if (child + 1 <= obj->heapSize && 
            obj->cmp(obj->heap[child + 1], obj->heap[child])) {
            child++;
        }
        // 若子节点优先级高于父节点，则交换
        if (obj->cmp(obj->heap[child], obj->heap[parent])) {
            swap(&(obj->heap[child]), &(obj->heap[parent]));
            parent = child;
            child = parent << 1;
        } else {
            break;  // 堆性质已满足，停止下沉
        }
    }
}
```

#### (5) 取堆顶
```c
int top(struct Heap* obj) {
    return obj->heap[1];
}
```

#### (6) 建堆（Floyd算法）
- 先将无序数组拷贝到堆数组（索引从1开始）
- 找到**最后一个非叶子节点**：`n / 2`（完全二叉树中，索引大于 `n/2` 的节点均为叶子节点）
- 从该节点开始向前遍历，对每个节点执行 `sift-down` 操作
```c
// 向下调整（sift-down），供建堆调用
void siftDown(struct Heap* obj, int parent) {
    int child = parent << 1;
    while (child <= obj->heapSize) {
        // 选择两个子节点中优先级更高的
        if (child + 1 <= obj->heapSize && 
            obj->cmp(obj->heap[child + 1], obj->heap[child])) {
            child++;
        }
        // 若子节点优先级高于父节点，则交换
        if (obj->cmp(obj->heap[child], obj->heap[parent])) {
            swap(&(obj->heap[child]), &(obj->heap[parent]));
            parent = child;
            child = parent << 1;
        } else {
            break;
        }
    }
}

// Floyd 算法建堆：将已有数组原地调整为堆
void buildHeap(struct Heap* obj, int* arr, int n) {
    // 将数组拷贝到堆中（索引从1开始）
    for (int i = 0; i < n; i++) {
        obj->heap[i + 1] = arr[i];
    }
    obj->heapSize = n;
    // 从最后一个非叶子节点开始，向前遍历执行向下调整
    for (int i = n / 2; i >= 1; i--) {
        siftDown(obj, i);
    }
}
```

#### (7) 使用示例
```c
// 创建小顶堆
struct Heap h;
// 切换为大顶堆只需将 `init` 时的比较函数改为 `cmpMax`：
init(&h, 100, cmpMin);

push(&h, 5);
push(&h, 2);
push(&h, 8);
push(&h, 1);

// 依次弹出：1, 2, 5, 8
while (h.heapSize > 0) {
    printf("%d ", top(&h));
    pop(&h);
}
```
