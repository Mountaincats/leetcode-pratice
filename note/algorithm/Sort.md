## 排序
[TOC]

### 一、实际常用的数组排序算法总结
| 算法 | 最好时间复杂度 | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 稳定性 | 使用场景 |
|------|------|------|------|-----------|--------|-----------|
| **Timsort** | $O(n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | 稳定 | Python `sorted()` / Java `Collections.sort()` |
| **快速排序** | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ 平均<br>$O(n)$ 最坏 | 不稳定 | C++ `sort`、通用内排序 |
| **归并排序** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | 稳定 | 链表、外部排序 |
| **堆排序** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(1)$ | 不稳定 | TopK、优先队列场景 |
| **插入排序** | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | 稳定 | 小数组、几乎有序的数据 |
| **计数排序** | $O(n+k)$ | $O(n+k)$ | $O(n+k)$ | $O(k)$ | 稳定 | 整数、值域小 |
| **桶排序** | $O(n)$ | $O(n)$ | $O(n^2)$ | $O(n+k)$ | 取决于桶内 | 均匀分布数据 |
| **基数排序** | $O(d \cdot n)$ | $O(d \cdot n)$ | $O(d \cdot n)$ | $O(n+k)$ | 稳定 | 定长整数/字符串 |

---

### 二、详细说明
#### (1) Timsort

**1. 算法说明**
**本质：归并排序 + 插入排序的自适应混合算法**

Timsort 的核心思想是：**现实数据往往部分有序**，与其强行拆分，不如先识别已有的有序片段（称为 `run`），再用归并合并。

- **找 run**：从左到右扫描，识别已经有序的子数组（升序或降序，降序会被反转）
- **补足 run**：run 长度小于 `MIN_RUN`（通常 32~64）时，用插入排序将其扩展到 `MIN_RUN`
- **合并 run**：用栈维护 run 序列，保证相邻 run 的长度满足 `run[i] > run[i+1] + run[i+2]`（避免不平衡合并）
- **galloping mode**：合并时发现某一侧连续多个元素都小于另一侧当前元素，则批量拷贝跳过比较

> 总结：Timsort 在有大量预存有序性的数据上接近 $O(n)$，最坏情况仍保持 $O(n \log n)$，且稳定

**2. 示例代码**
```c
/* 
 * Timsort 工业实现极复杂（Python CPython 中实现约 5000+ 行），
 * 此处给出核心流程示意，帮助理解其混合策略
 */

// 插入排序：用于补足短 run
void insertion_sort(int* arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 合并两个有序区间 [l, m) 和 [m, r)
void merge(int* arr, int* temp, int l, int m, int r) {
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i < m) temp[k++] = arr[i++];
    while (j < r) temp[k++] = arr[j++];
    for (i = l; i < r; i++) arr[i] = temp[i];
}

/*
 * 完整 Timsort 还需：
 * - run 检测（count_run()）
 * - MIN_RUN 计算
 * - run 栈维护与平衡合并
 * - galloping mode 优化
 * 实际工程中建议直接调用标准库排序接口
 */
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| Python `sorted()` / Java `Arrays.sort()` | 综合性能最优，现实数据通常部分有序 |
| 用户输入数据、日志时间戳 | 天然存在局部有序性 |
| 需要稳定排序 | Timsort 保持相等元素的相对顺序 |


#### (2) 快速排序

**1. 算法说明**
**本质：分治 + 原地划分**

- 选取一个 pivot（基准值），通过一次 partition 将数组划分为：
  - 左侧：所有 `< pivot` 的元素
  - 右侧：所有 `>= pivot` 的元素
- pivot 最终落在正确位置上，递归处理左右子区间

> **最坏情况 $O(n^2)$**：发生在数组已排序且 pivot 固定选最左/最右时
> **工业级改进（Introsort）**：当递归深度超过阈值时切换为堆排序，避免退化

**partition 的循环不变式**（双向扫描）：
- `[left, i)` 区间内所有元素 `< pivot`
- `(j, right]` 区间内所有元素 `> pivot`
- `[i, j]` 区间内元素未处理
- 循环结束时 `i >= j`，`j` 即为 pivot 的最终位置

**2. 示例代码**
```c
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    
    /*
     * 不使用异或交换的原因：
     * 当 a 和 b 指向同一地址时，异或交换会将该值清零：
     *     *a = *a ^ *a = 0
     *     *b = 0 ^ 0 = 0
     *     *a = 0 ^ 0 = 0
     * 临时变量交换无此问题，且现代编译器会优化掉开销
     */
}

int partition(int* nums, int left, int right) {
    // 随机化 pivot：避免有序数组触发最坏情况 O(n²)
    int i = left + rand() % (right - left + 1);
    int pivot = nums[i];
    swap(&nums[i], &nums[left]);  // pivot 移到最左
    
    i = left + 1;
    int j = right;
    while (true) {
        // i 向右移动，直到遇到 >= pivot 的元素
        while (i <= j && nums[i] < pivot) {
            i++;
        }
        // j 向左移动，直到遇到 <= pivot 的元素
        while (i <= j && nums[j] > pivot) {
            j--;
        }
        if (i >= j) {
            break;
        }
        // 交换：将大元素移到右侧，小元素移到左侧
        swap(&nums[i], &nums[j]);
        i++;
        j--;
    }
    
    // j 停在最后一个 <= pivot 的位置，放入 pivot
    swap(&nums[left], &nums[j]);
    return j;
}

void quickSort(int* nums, int left, int right) {
    // 有序性检测：已有序的区间直接返回，避免无效递归
    bool ordered = true;
    for (int i = left; i < right; i++) {
        if (nums[i] > nums[i + 1]) {
            ordered = false;
            break;
        }
    }
    if (ordered) return;
    
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| 通用内排序 | 平均 $O(n \log n)$，常数因子小，缓存友好 |
| C++ `std::sort` | 底层为 introsort（快排 + 堆排 + 插入） |
| 不需要稳定性 | 快排不稳定，但大多数业务不依赖稳定排序 |


#### (3) 归并排序

**1. 算法说明**
**本质：分治 + 有序合并**

- 将数组递归拆分为两半，分别排序
- 将两个已排序的子数组合并为一个有序数组

> **关键性质**：
> - 最坏情况也是 $O(n \log n)$，不依赖数据分布
> - 稳定排序
> - 需要 $O(n)$ 额外空间

**合并过程的循环不变式**：
- `i` 指向左数组未处理部分的起点
- `j` 指向右数组未处理部分的起点
- `k` 指向结果数组下一个写入位置
- `[0, k)` 区间已全部正确填充

**2. 示例代码**
```c
// 合并两个有序区间 [l, m) 和 [m, r)
void merge(int* arr, int* temp, int l, int m, int r) {
    int i = l, j = m, k = l;
    // 循环不变式：temp[0..k) 已正确填充
    while (i < m && j < r) {
        if (arr[i] <= arr[j]) {    // <= 保证稳定性
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    // 剩余元素直接拷贝
    while (i < m) temp[k++] = arr[i++];
    while (j < r) temp[k++] = arr[j++];
    // 拷回原数组
    for (i = l; i < r; i++) arr[i] = temp[i];
}

void merge_sort(int* arr, int* temp, int l, int r) {
    if (r - l <= 1) return;         // 区间长度 <= 1，自然有序
    int m = l + (r - l) / 2;
    merge_sort(arr, temp, l, m);
    merge_sort(arr, temp, m, r);
    merge(arr, temp, l, m, r);
}

/*
 * 调用方式：
 * int* temp = malloc(sizeof(int) * n);
 * merge_sort(arr, temp, 0, n);
 * free(temp);
 */
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| 链表排序（LeetCode 148） | 不需要随机访问，合并只需修改指针 |
| 外部排序 | 数据无法一次性放入内存，可分段读入归并 |
| 逆序对问题（LeetCode 315/493） | 合并时可统计跨区间的逆序对数量 |
| 需要稳定性 | 等值元素相对顺序保持不变 |


#### (4) 堆排序

**1. 算法说明**
**本质：选择排序 + 堆数据结构**

- **建堆**：将数组原地调整为大顶堆（父节点 ≥ 子节点）
- **排序**：反复将堆顶（最大值）与末尾交换，缩小堆范围，向下调整

> **关键性质**：
> - 最坏 $O(n \log n)$，不受数据分布影响
> - 原地排序，$O(1)$ 空间
> - 不稳定

**向下调整（sift down）的循环不变式**：
- 以 `root` 为根的子树，除 root 外，左右子树都满足堆性质
- 每次比较 root 与较大子节点，若违反堆性质则交换

**2. 示例代码**
```c
// 向下调整：保证以 root 为根的子树满足大顶堆性质
void sift_down(int* arr, int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    // 找出 root、left、right 三者中的最大值
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    
    if (largest != root) {
        int tmp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = tmp;
        sift_down(arr, n, largest);    // 递归调整受影响的子树
    }
}

// 建堆：自底向上对所有非叶子节点做 sift_down
void build_heap(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        sift_down(arr, n, i);
    }
}

void heap_sort(int* arr, int n) {
    build_heap(arr, n);                 // O(n) 建堆
    for (int i = n - 1; i > 0; i--) {
        // 堆顶（最大值）放到末尾
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        sift_down(arr, i, 0);           // 调整剩余 i 个元素
    }
}
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| TopK 问题（LeetCode 215） | 建堆 $O(n)$ + K 次弹出 $O(K \log n)$ |
| 数据流中位数（LeetCode 295） | 双堆（大顶堆 + 小顶堆）维护 |
| 优先队列 | 堆是优先队列的经典实现 |
| 内存受限环境 | $O(1)$ 额外空间，原地排序 |


#### (5) 插入排序

**1. 算法说明**
**本质：构建有序序列，逐个插入**

- 维护 `[0, i)` 为已排序区间
- 每次将 `arr[i]` 插入到已排序区间的正确位置
- 类似整理扑克牌的过程

> **关键性质**：
> - 最好情况 $O(n)$（数组已排序）
> - 稳定排序
> - $O(1)$ 空间
> - 小数组上常数极小，实际比快排更快

**循环不变式**：
- `[0, i)` 区间始终有序
- `[i, n)` 区间尚未处理

**2. 示例代码**
```c
void insertion_sort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];          // 当前待插入元素
        int j = i - 1;
        // 将大于 key 的元素整体右移一位
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        // 找到插入位置
        arr[j + 1] = key;
    }
}

/*
 * 优化版本：使用二分查找定位插入位置（减少比较次数）
 * 但移动次数不变，仍为 O(n²)
 */
void binary_insertion_sort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0, right = i - 1;
        // 二分查找第一个 > key 的位置
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= key) left = mid + 1;
            else right = mid - 1;
        }
        // 将 [left, i) 元素右移
        for (int j = i; j > left; j--) {
            arr[j] = arr[j - 1];
        }
        arr[left] = key;
    }
}
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| 小数组（< 50 元素） | 常数极小，比复杂排序算法更快 |
| 几乎有序的数据 | 接近 $O(n)$ |
| Timsort / Introsort 的兜底 | 递归到小规模子问题时切换为插入排序 |
| 在线算法 | 新元素到来时可直接插入已有有序序列 |


#### (6) 计数排序

**1. 算法说明**
**本质：非比较排序，用下标映射值**

- 统计每个值出现的次数
- 计算前缀和，确定每个值的结束位置
- 从后往前填充结果数组（保证稳定性）

> **关键性质**：
> - 时间 $O(n + k)$，$k$ 为值域大小
> - 稳定排序（从后往前填充时）
> - 值域过大时不适用（空间爆炸）

**前缀和的作用**：
- `cnt[x]` 表示值 `x` 在结果数组中的最后一个位置 + 1
- 从后往前遍历原数组，每放置一个 `x`，`cnt[x]--`

**2. 示例代码**
```c
// 支持负数的计数排序
void counting_sort(int* arr, int n) {
    if (n <= 1) return;
    
    int mn = arr[0], mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < mn) mn = arr[i];
        if (arr[i] > mx) mx = arr[i];
    }
    
    int range = mx - mn + 1;
    int* cnt = calloc(range, sizeof(int));
    int* output = malloc(sizeof(int) * n);
    
    // 统计频次
    for (int i = 0; i < n; i++) {
        cnt[arr[i] - mn]++;
    }
    
    // 计算前缀和：cnt[x] 表示 x 的最后一个位置 + 1
    for (int i = 1; i < range; i++) {
        cnt[i] += cnt[i - 1];
    }
    
    // 从后往前填充：保证稳定性
    for (int i = n - 1; i >= 0; i--) {
        int idx = arr[i] - mn;
        output[cnt[idx] - 1] = arr[i];
        cnt[idx]--;
    }
    
    // 拷回原数组
    for (int i = 0; i < n; i++) arr[i] = output[i];
    
    free(cnt);
    free(output);
}
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| 年龄、成绩、分数排序 | 值域小且已知（如 0~100） |
| ASCII 字符排序 | 值域固定 0~127 或 0~255 |
| 作为基数排序的子过程 | 按某一位进行计数排序 |
| 值域 $k \le 10^5$ | 空间可接受，速度远超比较排序 |


#### (7) 桶排序

**1. 算法说明**
**本质：分桶 + 桶内独立排序**

- 将数据均匀分配到若干个桶中
- 对每个桶内部进行排序（可用任意排序算法）
- 按桶的顺序依次输出

> **关键性质**：
> - 期望时间 $O(n)$，当数据均匀分布时
> - 最坏 $O(n^2)$，当所有元素落入同一个桶
> - 桶大小的选择至关重要，没有万能参数

**均匀分布的保证**：
- 若数据服从均匀分布 $U[a, b]$，则每个桶的期望元素数为 $O(1)$

**2. 示例代码**
```c
typedef struct Bucket {
    int* arr;
    int size;
    int capacity;
} Bucket;

Bucket* create_bucket(int cap) {
    Bucket* b = malloc(sizeof(Bucket));
    b->arr = malloc(sizeof(int) * cap);
    b->size = 0;
    b->capacity = cap;
    return b;
}

void bucket_add(Bucket* b, int val) {
    if (b->size == b->capacity) {
        b->capacity *= 2;
        b->arr = realloc(b->arr, sizeof(int) * b->capacity);
    }
    b->arr[b->size++] = val;
}

// 桶内用插入排序（适合小数组）
void bucket_insertion_sort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucket_sort(int* arr, int n, int bucket_size) {
    if (n <= 1) return;
    
    int mn = arr[0], mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < mn) mn = arr[i];
        if (arr[i] > mx) mx = arr[i];
    }
    
    int bucket_count = (mx - mn) / bucket_size + 1;
    Bucket** buckets = malloc(sizeof(Bucket*) * bucket_count);
    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = create_bucket(16);
    }
    
    // 分配元素到桶
    for (int i = 0; i < n; i++) {
        int idx = (arr[i] - mn) / bucket_size;
        bucket_add(buckets[idx], arr[i]);
    }
    
    // 桶内排序并收集
    int pos = 0;
    for (int i = 0; i < bucket_count; i++) {
        if (buckets[i]->size > 0) {
            bucket_insertion_sort(buckets[i]->arr, buckets[i]->size);
            for (int j = 0; j < buckets[i]->size; j++) {
                arr[pos++] = buckets[i]->arr[j];
            }
        }
        free(buckets[i]->arr);
        free(buckets[i]);
    }
    free(buckets);
}
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| 均匀分布数据（如 0~1 浮点数） | 每个桶期望大小为 $O(1)$ |
| LeetCode 164（最大间距） | 桶的思想用于去重和分组 |
| 外部排序的中间阶段 | 先分桶再各自处理 |
| 已知数据分布特征 | 可根据分布定制桶边界 |


#### (8) 基数排序

**1. 算法说明**
**本质：按位排序，高位优先或低位优先**

- 从最低位到最高位（LSD），依次对每一位做稳定排序
- 通常使用计数排序作为子过程
- 不比较元素大小，只比较"位"

> **关键性质**：
> - 时间 $O(d \cdot n)$，$d$ 为最大位数
> - 稳定排序
> - 适合定长整数或字符串

**正确性依据**：
- 稳定排序保证：先排低位，再排高位时，高位相同的元素仍保持低位的顺序

**2. 示例代码**
```c
// 获取数字的第 exp 位（个位 exp=1，十位 exp=10...）
int get_digit(int x, int exp) {
    return (x / exp) % 10;
}

// 对某一位进行计数排序
void counting_sort_by_digit(int* arr, int n, int exp) {
    int output[n];
    int cnt[10] = {0};
    
    // 统计该位上各数字的出现次数
    for (int i = 0; i < n; i++) {
        cnt[get_digit(arr[i], exp)]++;
    }
    
    // 前缀和
    for (int i = 1; i < 10; i++) {
        cnt[i] += cnt[i - 1];
    }
    
    // 从后往前填充，保证稳定性
    for (int i = n - 1; i >= 0; i--) {
        int digit = get_digit(arr[i], exp);
        output[cnt[digit] - 1] = arr[i];
        cnt[digit]--;
    }
    
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

// LSD 基数排序：从低位到高位
void radix_sort(int* arr, int n) {
    if (n <= 1) return;
    
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) mx = arr[i];
    }
    
    // 对每一位进行计数排序
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        counting_sort_by_digit(arr, n, exp);
    }
}

/*
 * 字符串基数排序（LSD）：
 * - 从最后一个字符开始向前排
 * - 不足长度的字符串视为 '\0'（最小字符）
 */
```

**3. 适用场景**
| 场景 | 原因 |
|------|------|
| 定长整数（手机号、身份证后几位） | 位数固定且较少 |
| IP 地址排序 | 每段 0~255，可分 4 次计数排序 |
| 字符串字典序排序 | LSD 从末位开始，或 MSD 从高到低递归 |
| 值域大但位数少 | 相比比较排序有优势 |