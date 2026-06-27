## 索引表
[TOC]

### 一、理论
#### (1) 示例代码实现
```c
/* 示例 1 */
/* 索引项定义 */
typedef struct IndexItem {
    KeyType key;          /* 索引键 */
    DataAddr addr;        /* 数据区地址 / 块号 */
} IndexItem;

/* 索引表定义 */
typedef struct IndexTable {
    IndexItem *items;     /* 索引项数组 */
    size_t size;          /* 当前索引项数 */
    size_t capacity;      /* 最大容量 */
    int (*cmp)(const KeyType *, const KeyType *); /* 比较函数 */
} IndexTable;

/* 核心操作接口 */
void index_init(IndexTable *t, size_t cap, int (*cmp)(const KeyType*, const KeyType*));
IndexItem* index_find(IndexTable *t, KeyType key);
int index_insert(IndexTable *t, IndexItem item);
void index_delete(IndexTable *t, KeyType key);
```

```c
/* 示例 2 */
/* B树节点定义 */
typedef struct BTreeNode {
    KeyType *keys;              /* 关键字数组 */
    DataAddr *addrs;            /* 数据地址数组 */
    struct BTreeNode **children;/* 子节点指针数组 */
    int keyNum;                 /* 当前关键字数量 */
    bool isLeaf;                /* 是否为叶子节点 */
} BTreeNode;

/* B树定义 */
typedef struct BTree {
    BTreeNode *root;            									/* 根节点 */
    int t;                      									/* 最小度数（t>=2）*/
    int (*cmp)(const KeyType *, const KeyType *); /* 比较函数 */
} BTree;

/* 核心操作接口 */
void btree_init(BTree *tree, int degree, int (*cmp)(const KeyType*, const KeyType*));
BTreeNode* btree_search(BTreeNode *node, KeyType key);
void btree_insert(BTree *tree, KeyType key, DataAddr addr);
void btree_delete(BTree *tree, KeyType key);
static void btree_split_child(BTreeNode *parent, int index);
static void btree_insert_nonfull(BTreeNode *node, KeyType key, DataAddr addr);
```

#### (2) 数据结构
**1. 索引表的实现方案：静态与动态**
- **逻辑概念**：索引表（Index Table）是一个逻辑概念，指独立于主数据之外、存储 `key -> address` 映射以加速查找的结构
- **物理实现**：根据数据变动特性，索引表主要有两种物理实现方案：
  - **静态索引（基于有序数组）**：即本节代码**示例 1**。适用于数据量小、查询密集、更新极少的场景（如内存配置表）。索引项始终保持逻辑有序，插入时需移动后续元素，时间复杂度为 $O(n)$，但查找利用二分法可达 $O(\log n)$
  - **动态索引（基于B树/B+树）**：即本节代码**示例 2**。适用于数据量大、更新频繁的场景（如数据库、文件系统）。通过多路平衡树结构，将插入、删除的数据搬移限制在单个节点内，解决了有序数组更新成本高昂的问题，同时保持 $O(\log n)$ 的稳定性能
    - **B树特性**：多路平衡查找树，通过增加分支因子降低树高，减少磁盘 I/O 次数
    - **B+树优化**：数据库常用 B+树，将数据全部存储在叶子节点，形成有序链表，极大优化了范围查询效率

**2. 稀疏索引与稠密索引**
根据索引项覆盖数据记录的粒度，索引可分为以下两类：
- **稠密索引**：数据文件中**每条记录**对应一个索引项。由于索引项与主记录一一对应，查找时通过索引即可直接定位，无需额外扫描，速度最快，但因存储了大量指针，空间开销较大
- **稀疏索引**：仅为数据文件的**每个数据块**建立索引项。每个索引项指向一个连续的数据块，进入块后需配合块内顺序查找。虽然单次查找可能需要额外扫描块内数据，但大幅减少了索引表的体积，降低了内存占用，常用于外存存储系统

| 对比维度 | 稠密索引 | 稀疏索引 |
| :--- | :--- | :--- |
| 索引项数量 | 与数据记录**1:1** | 按块建立，索引少很多 |
| 索引数组大小 | 大 | 小，节省空间 |
| 查询速度 | 快（仅二分索引） | 稍慢（定块+块内遍历） |
| 插入删除开销 | 大（需维护索引数组有序） | 小（仅改块内链表） |
| 依赖数据 | 全局严格有序 | 全局有序+按块划分 |
| 适用规模 | 小数据量 | 海量磁盘/文件大数据 |

#### (3) 与哈希表对比
| 维度 | 索引表（Index） | 哈希表（Hash） |
| :--- | :--- | :--- |
| **逻辑本质** | 映射表 + 顺序性 | 映射表 |
| **底层结构** | 有序数组 / B树 | 桶数组 + 链表 |
| **查找方式** | 比较（二分 / 树遍历） | 计算（哈希函数） |
| **有序性** | 天然有序 | 无序 |
| **插入开销** | $O(n)$（数组）/ $O(\log n)$（B树） | $O(1)$（平均） |
| **适用场景** | 范围查询、排序输出、稳定性能 | 精准单点查询、极高吞吐 |

---

### 二、设计技巧
- 物理实现
  - 若数据为**静态**，首选**有序数组**（代码简单、缓存友好）
  - 若数据为**动态**，首选**B+树**（平衡增删改查成本，适合外存）
